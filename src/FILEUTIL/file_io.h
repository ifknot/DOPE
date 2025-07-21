#ifndef FILE_IO_H
#define FILE_IO_H

#include "file_constants.h"
#include "file_types.h"
#include "../MEM/mem_arena.h"

line_t* file_read_line(mem_arena_t* arena, FILE* input); // checks for stdin if so uses ctrl-Z terminate

page_t file_read_page(mem_arena_t* arena, FILE* input);



#endif
