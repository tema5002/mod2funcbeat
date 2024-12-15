#pragma once

#include <stdlib.h>
#include "error.h"

void* safe_malloc(const size_t bytes) {
    void* result = malloc(bytes);
    if (result == NULL) error("Failed to allocate memory.\n");
    return result;
}

void* safe_realloc(void* ptr, size_t size) {
    void* result = realloc(ptr, size);
    if (result == NULL) error("Failed to allocate memory.\n");
    return result;
}

FILE* safe_fopen(const char* filename, const char* mode) {
    FILE* stream = fopen(filename, mode);
    if (stream == NULL) {
        error("Could not open file %s in '%s' mode.\n", filename, mode);
    }
    return stream;
}
