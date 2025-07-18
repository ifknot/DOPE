#ifndef DOPE_TYPES_H
#define DOPE_TYPES_H

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include "dope_constants.h"

typedef char line_t[DOPE_LINE_SIZE];

typedef struct {
    line_t* lines[DOPE_MAX_LINES];
    size_t line_count;
} page_t;

#endif
