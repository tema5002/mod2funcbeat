#pragma once

#include <stdint.h>
#include "memory.h"

typedef struct file_buffer {
    char* begin;
    size_t idx;
    size_t size;
}* file_buffer;

struct file_buffer* create_file_buffer(const size_t size) {
    struct file_buffer* const buf = safe_malloc(sizeof(struct file_buffer));
    buf->begin = safe_malloc(size);
    buf->idx = 0;
    buf->size = size;
    return buf;
}

void destroy_file_buffer(file_buffer buffer) {
    free(buffer->begin);
    free(buffer);
}

file_buffer read_all_bytes(const char* filename) {
    FILE* file = safe_fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    const size_t file_size = ftell(file);
    rewind(file);
    file_buffer buffer = create_file_buffer(file_size);
    if (fread(buffer->begin, 1, file_size, file) != file_size) error("Reading file failed.");
    fclose(file);
    return buffer;
}

int8_t read_int8(file_buffer buf) {
    if (buf->idx < buf->size) return buf->begin[buf->idx];
    error("Error: reached end of file\nEither your file is invalid or we messed up\n");
}

uint8_t read_uint8(file_buffer buf) {
    return read_int8(buf);
}

uint16_t read_uint16(file_buffer buf) {
    return read_uint8(buf) +
           (read_uint8(buf) << 8);
}

int16_t read_int16(file_buffer buf) {
    return read_uint16(buf);
}

uint32_t read_uint32(file_buffer buf) {
    return read_uint8(buf) +
           (read_uint8(buf) << 8) +
           (read_uint8(buf) << 16) +
           (read_uint8(buf) << 24);
}

char* read_string(file_buffer buf, const size_t b) {
    char* s = safe_malloc(b + 1);
    s[b] = '\0';
    for (size_t i = 0; i < b; i++) {
        s[i] = read_int8(buf);
    }
    return s;
}

void skip_bytes(file_buffer buf, const size_t b) {
    buf->idx += b;
    if (buf->idx >= buf->size) {
        error("Error: reached end of file\nEither your file is invalid or we messed up\n");
    }
}
