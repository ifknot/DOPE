#include "file_utils.h"
#include "file_constants.h"
#include <string.h>
#include <stdio.h>


const char* file_get_extension(const char* file_path) {
    if (!file_path) {
        return NULL;
    }
    const char* last_dot = strrchr(file_path, FILE_EXTENSION_DELIM);
    if (!last_dot || last_dot == file_path || !strcmp(last_dot, ".")) {
        return NULL;
    }
    else {
        return ++last_dot;
    }
}

long file_get_size(FILE* file) {
    if (!file) return 0;

    long original_pos = ftell(file);
    if (original_pos == -1L) return 0;

    if (fseek(file, 0, SEEK_END) != 0) return 0;

    long size = ftell(file);
    if (size == -1L) return 0;

    if (fseek(file, original_pos, SEEK_SET) != 0) return 0;
    return (long)size;
}

bool file_position_indicator_is_eof(FILE* file) {
    if (!file) return true;

    long current_pos = ftell(file);
    if (current_pos == -1L) return true;

    if (fseek(file, 0, SEEK_END) != 0) return true;

    long end_pos = ftell(file);
    if (end_pos == -1L) return true;

    if (fseek(file, current_pos, SEEK_SET) != 0) return true;

    return current_pos == end_pos;
}

long file_position_indicator_reset(FILE* file) {
    if (!file) return -1;
    long prev_pos = ftell(file);
    if (prev_pos == -1L) return -1;
    if (fseek(file, 0, SEEK_SET) != 0) return -1;
    return prev_pos;
}

long file_position_indicator_move(FILE* file, long offset, int origin) {
    assert(file != NULL);
    assert(origin == SEEK_SET || origin == SEEK_CUR || origin == SEEK_END);

    long prev_pos = ftell(file);
    if (prev_pos == -1L) return -1;
    if (fseek(file, offset, origin) != 0) return -1;
    return prev_pos;
}
