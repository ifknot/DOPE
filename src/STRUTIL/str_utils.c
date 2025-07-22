#include "str_utils.h"
#include "../CONTRACT/contract.h"

// Trims line endings in-place for any line length
void str_trim_line_endings(char* line) {
    require_address(line, "NULL line!");

    size_t i;
    for (i = 0; i < STR_MAX_TERMINAL_INPUT && line[i] != '\0'; i++) {
        if (line[i] == '\r' || line[i] == '\n') {
            line[i] = '\0';
            break;
        }
    }
    require(i > 0, "ZERO line length!"); // Reject empty strings
    // Force null-termination if hit limit with no \r or \n or \0
    if (i == STR_MAX_TERMINAL_INPUT) {
        line[STR_MAX_TERMINAL_INPUT - 1] = '\0';  // Safe truncation
    }
}
