#include "file_io.h"
#include "../CONTRACT/contract.h"
#include "../STRUTIL/str_utils.h"

line_t* file_read_line(mem_arena_t* arena, FILE* input) {
    require_address(arena, "NULL memory arena!");
    require_fd(input, "NULL input stream handle!");

    line_t* line = mem_arena_alloc(arena, sizeof(line_t));

    require_mem(line, "NULL line - arena alloc fail!");

    if (!fgets(*line, FILE_MAX_LINE_SIZE, input)) {
        require_not_canceled(!ferror(input), "READ error occurred!");
        return NULL;  // EOF/error
    }

    // Check for Ctrl+Z (DOS EOF) in stdin
    if (input == stdin && (*line)[0] == CTRL_Z) {
        return NULL;
    }

    str_trim_line_endings((char*)line);
    return line;
}

page_t file_read_page(mem_arena_t* arena, FILE* input) {
    require_address(arena, "NULL memory arena!");
    require_fd(input, "NULL input stream handle!");

    page_t page = {0};

    while (page.line_count < FILE_MAX_PAGE_SIZE) {
        line_t* line = file_read_line(arena, input);
        if (!line) {
            break;
        }
        page.lines[page.line_count++] = line;
    }

    require_io_success(page.line_count > 0, "EMPTY file!");

    return page;
}
