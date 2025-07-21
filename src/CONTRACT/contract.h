/**
 * @file contract.h
 * @brief POSIX_Exhaustive Design-by-Contract with ALL POSIX errno values
 * @note Compile with `-D_POSIX_C_SOURCE=200809L` for full POSIX compliance.
 */
#ifndef CONTRACT_H
#define CONTRACT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "posix_errno.h"

// =============================================================================
// Implementation Stub
// =============================================================================
static inline void _contract_fail(
    const char *cond,
    const char *msg,
    const char *file,
    int line
) {
    time_t now = time(NULL);
    struct tm *tm_info;
    char tstr[9]; // HH:MM:SS\0
    char shortfile[13]; // 8.3+1 (\0) - DOS 8.3 filename format

    /* Watcom-compatible time handling */
    tm_info = localtime(&now);  // Note: not thread-safe, but fine for DOS

    /* Format time as HH:MM:SS */
    strftime(tstr, sizeof(tstr), "%H:%M:%S", tm_info);

    /* DOS-style filename extraction (8.3 format) */
    const char *base = strrchr(file, '\\');  // DOS uses backslashes
    if (!base) base = strrchr(file, '/');    // Fallback to forward slash
    base = base ? base + 1 : file;

    /* Truncate to 8.3 format */
    size_t len = strlen(base);
    if (len <= 12) {
        strcpy(shortfile, base);
    } else {
        /* DOS 8.3 format: 8 chars for name, then extension */
        strncpy(shortfile, base, 8);
        const char *dot = strchr(base, '.');
        if (dot && (dot - base) <= 8) {
            strncpy(shortfile + 8, dot, 4);  // Copy .ext (max 3 chars + dot)
        }
        shortfile[12] = '\0';
    }

    /* Watcom's stderr output - using DOS-compatible formatting */
    fprintf(stderr, "[%s] %s:%d|%s|%d(%s)|%s\n",
            tstr, shortfile, line, cond, errno,
            strerror(errno), msg);
    abort();
}

// =============================================================================
// Core Macro (Private)
// =============================================================================
#define _CONTRACT_ENFORCE(cond, msg, err) \
    do { \
        if (!(cond)) { \
            errno = (err); \
            _contract_fail(#cond, msg, __FILE__, __LINE__); \
        } \
    } while (0)

// =============================================================================
// Default Contract
// =============================================================================
#define require(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)

// =============================================================================
// Process/System Contracts
// =============================================================================
#define require_arg_list(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_E2BIG)
#define require_buf_space(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_ENOBUFS)
#define require_id_valid(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_EIDRM)
#define require_msg_type(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_ENOMSG)
#define require_process(cond, msg)        _CONTRACT_ENFORCE(cond, msg, POSIX_ESRCH)
#define require_no_deadlock(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_EDEADLK)
#define require_not_canceled(cond, msg)   _CONTRACT_ENFORCE(cond, msg, POSIX_ECANCELED)

// =============================================================================
// Filesystem Contracts
// =============================================================================
#define require_fd(cond, msg)             _CONTRACT_ENFORCE(cond, msg, POSIX_EBADF)
#define require_exists(cond, msg)         _CONTRACT_ENFORCE(cond, msg, POSIX_ENOENT)
#define require_not_dir(cond, msg)        _CONTRACT_ENFORCE(cond, msg, POSIX_EISDIR)
#define require_is_dir(cond, msg)         _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTDIR)
#define require_no_loops(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_ELOOP)
#define require_writable(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_EROFS)
#define require_empty_dir(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTEMPTY)
#define require_regular_file(cond, msg)   _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)
#define require_not_fifo(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_ENXIO)
#define require_permission(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_EPERM)
#define require_io_success(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_EIO)
#define require_device(cond, msg)         _CONTRACT_ENFORCE(cond, msg, POSIX_ENODEV)
#define require_not_busy(cond, msg)       _CONTRACT_ENFORCE(cond, msg, POSIX_ETXTBSY)
#define require_disk_space(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENOSPC)
#define require_file_size(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_EFBIG)
#define require_name_length(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_ENAMETOOLONG)
#define require_same_device(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_EXDEV)
#define require_fresh_handle(cond, msg)   _CONTRACT_ENFORCE(cond, msg, POSIX_ESTALE)
#define require_quota(cond, msg)          _CONTRACT_ENFORCE(cond, msg, POSIX_EDQUOT)
#define require_block_device(cond, msg)   _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTBLK)
#define require_not_remote(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_EREMOTE)
#define require_pipe_ready(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_EPIPE)
#define require_valid_encoding(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EILSEQ)
#define require_supported(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTSUP)
#define require_recoverable(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTRECOVERABLE)
#define require_owner_alive(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_EOWNERDEAD)

// =============================================================================
// Memory/Address Contracts
// =============================================================================
#define require_address(cond, msg)        _CONTRACT_ENFORCE(cond, msg, POSIX_EFAULT)
#define require_mem(cond, msg)            _CONTRACT_ENFORCE(cond, msg, POSIX_ENOMEM)
#define require_aligned(cond, msg)        _CONTRACT_ENFORCE(cond, msg, POSIX_EINVAL)

// =============================================================================
// Math/Domain Contracts
// =============================================================================
#define require_domain(cond, msg)         _CONTRACT_ENFORCE(cond, msg, POSIX_EDOM)
#define require_range(cond, msg)          _CONTRACT_ENFORCE(cond, msg, POSIX_ERANGE)

// =============================================================================
// Network Contracts
// =============================================================================
#define require_connected(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_ENOTCONN)
#define require_addr_free(cond, msg)      _CONTRACT_ENFORCE(cond, msg, POSIX_EADDRINUSE)
#define require_not_already_connecting(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EALREADY)
#define require_host_reachable(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EHOSTUNREACH)
#define require_network_up(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENETDOWN)
#define require_no_timeout(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ETIMEDOUT)
#define require_proto_available(cond, msg) _CONTRACT_ENFORCE(cond, msg, POSIX_EPROTONOSUPPORT)
#define require_no_multihop(cond, msg)    _CONTRACT_ENFORCE(cond, msg, POSIX_EMULTIHOP)

// =============================================================================
// STREAMS Contracts (Obscure POSIX)
// =============================================================================
#define require_stream_dev(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENOSTR)
#define require_stream_buf(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENOSR)
#define require_stream_alive(cond, msg)   _CONTRACT_ENFORCE(cond, msg, POSIX_ENODEV)

#endif // CONTRACT_H
