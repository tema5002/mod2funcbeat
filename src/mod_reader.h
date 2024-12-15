#pragma once

#include "file_buffer.h"
#include "mod_types.h"

mod_sample read_sample(file_buffer buf) {
    mod_sample sample = safe_malloc(sizeof(struct mod_sample));
    sample->name == read_string(buf, 22);
    sample->size = read_uint16(buf);
    const uint8_t c = read_uint8(buf);
    if (c >= sizeof(finetune_table) / sizeof(int8_t)) error("Invalid sample finetune: %p", c);
    sample->finetune = finetune_table[c];
    sample->volume = read_uint8(buf);
    if (sample->volume > 64) error("Invalid sample volume: %p", sample->volume);
    // ...
    return sample;
}

mod_module read_mod(file_buffer buf) {
    mod_module mod = safe_malloc(sizeof(struct mod_module));
    mod->name = read_string(buf, 20);
    return mod;
}

mod_module destroy_mod_module(mod_module mod) {
    free(mod->name);
    free(mod); // mod: IM FREE!!!!!!!! IM FREEEEE!!!!!!!!!!!!!!!!!11!!!
}
// i have no fucking idea what is going on