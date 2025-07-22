/**
 * @file file_tools.c
 * @brief File path and handle utilities
 * @defgroup file_tools File Handling Extras
 * @{
 */
#ifndef FILE_EXTENSION_H
#define	FILE_EXTENSION_H

#include "file_types.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Extracts file extension from path
 * @param file_path Null-terminated path string
 * @return Pointer to extension or empty string if none exists
 *
 * @retval file_get_extension("archive.zip") → "zip"
 * file_get_extension("README")     → ""
 * file_get_extension(".bashrc")   → ""
 * file_get_extension("backup.")   → ""
 */
const char* file_get_extension(const char* file_path);

/**
 * @brief Gets file size without modifying position
 * @param fhandle Valid DOS file handle
 * @return File size in bytes or 0
 *
 * @details
 * - Uses seek-to-end method
 * - Restores original file position
 * - Maximum 2GB file size in standard DOS
 */
long file_get_size(FILE* fhandle);

/**
 * @brief Checks if file pointer is at EOF
 * @param fhandle Valid DOS file handle
 * @return True if at end of file, false otherwise
 *
 * @note More reliable than feof() for DOS handles
 * @warning Temporarily modifies file position
 */
bool file_position_indicator_is_eof(FILE* fhandle);

/**
 * @brief Resets file position indicator to start of file
 * @param file Valid FILE pointer
 * @return Previous file position
 *
 * @retval >=0 Previous file position
 */
long file_position_indicator_reset(FILE* file);

/**
 * @brief Moves file position indicator
 * @param file Valid FILE pointer
 * @param offset Byte offset to move
 * @param origin Starting position (SEEK_SET/SEEK_CUR/SEEK_END)
 * @return Previous file position or -1 on error
 *
 * @retval >=0 Previous file position
 * @retval -1 Error (invalid file pointer/offset)
 */
long file_position_indicator_move(FILE* file, long offset, int origin);

#endif

/** @} */ // end of file_tools group
