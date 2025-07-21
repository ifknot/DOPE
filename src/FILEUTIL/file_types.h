#ifndef FILE_TYPES_H
#define FILE_TYPES_H

#include <stddef.h>

#include "file_constants.h"

typedef char line_t[FILE_MAX_LINE_SIZE];

typedef struct {
    line_t* lines[FILE_MAX_PAGE_SIZE];
    size_t line_count;
} page_t;

#endif
