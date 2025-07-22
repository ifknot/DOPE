#include "file_utils.h"
#include "file_constants.h"
#include "../CONTRACT/contract.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>


const char* file_get_extension(const char* file_path) {
    require_address(file_path, "NULL file path");

    const char* last_dot = strrchr(file_path, FILE_EXTENSION_DELIM);

    // Cases where return empty string:
    // 1. No dot found
    // 2. Dot is at start (hidden file without extension)
    // 3. Dot is last character ("file.")
    if (!last_dot || last_dot == file_path || *(last_dot + 1) == '\0') {
        return "";
    }

    return last_dot + 1;  // Skip the dot
}

long file_get_size(FILE* file) {
    require_fd(file, "NULL file handle!");

    long original_pos = ftell(file);
    require_io_success(original_pos != -1L, "FAILED to get current position");

    require_io_success(fseek(file, 0, SEEK_END) == 0, "FAILED seek to end!");

    long size = ftell(file);
    require_io_success(size != -1L, "FAILED to get file size!");

    require_io_success(fseek(file, original_pos, SEEK_SET) == 0, "FAILED to restore file position!");
    return (long)size;
}

bool file_position_indicator_is_eof(FILE* file) {
    require_fd(file, "NULL file handle!");

    long current_pos = ftell(file);
    require_io_success(current_pos != -1L, "FAILED to get current position");

    require_io_success(fseek(file, 0, SEEK_END) == 0, "FAILED seek to end!");

    long end_pos = ftell(file);
    require_io_success(end_pos != -1L, "FAILED to get end position");

    require_io_success(fseek(file, current_pos, SEEK_SET) == 0, "FAILED to restore file position!");

    return current_pos == end_pos;
}

long file_position_indicator_reset(FILE* file) {
    require_fd(file, "NULL file handle!");

    long prev_pos = ftell(file);
    require_io_success(prev_pos != -1L, strerror(errno));

    require_io_success(fseek(file, 0, SEEK_SET) == 0, strerror(errno));

    return prev_pos;
}

long file_position_indicator_move(FILE* file, long offset, int origin) {
    require_fd(file, "NULL file handle!");
    require_arg_list(origin == SEEK_SET || origin == SEEK_CUR || origin == SEEK_END, "INVALID origin!");

    long prev_pos = ftell(file);
    require_io_success(prev_pos != -1L, strerror(errno));

    require_io_success(fseek(file, offset, origin) == 0, strerror(errno));

    return prev_pos;
}
