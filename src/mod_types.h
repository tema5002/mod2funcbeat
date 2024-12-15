#pragma once

#include <stdint.h>

int8_t finetune_table[16] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    -8, -7, -6, -5,
    -4, -3, -2, -1,
};

typedef struct mod_sample {
    char* name;
    uint16_t size;
    int8_t finetune;
    uint8_t volume; // number in range 0x00 - 0x40 (0 - 64)
}* mod_sample;

typedef struct mod_module {
    char* name;
}* mod_module;