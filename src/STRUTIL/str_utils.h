#ifndef STR_UTILS_H
#define STR_UTILS_H

//Historical context: Traditional terminals used 80 chars, but modern systems handle much longer lines.
// Common standards: Linux kernel → 1024 chars for terminal input.
#define STR_MAX_TERMINAL_INPUT  80

void str_trim_line_endings(char* line);

#endif
