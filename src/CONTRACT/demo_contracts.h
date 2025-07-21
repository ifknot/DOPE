#ifndef DEMO_CONTRACTS_H
#define DEMO_CONTRACTS_H

#include <stdio.h>
#include "contract.h"

void demo_contracts() {
    printf("All contracts will now fail in sequence...\n");
    printf("Process/System Contracts\n");
    // =============================================================================
    require_arg_list(0,"POSIX_E2BIG");
    require_id_valid(0,"POSIX_EIDRM");
    require_process(0,"POSIX_ESRCH");
    require_no_deadlock(0,"POSIX_EDEADLK");
    require_not_canceled(0, "POSIX_ECANCELED");

    getchar();
    printf("Filesystem Contracts\n");
    // =============================================================================
     require_fd( 0, "POSIX_EBADF");
     require_exists(0, "POSIX_ENOENT");
     require_not_dir(0, "POSIX_EISDIR");
     require_is_dir(0, "POSIX_ENOTDIR");
     require_no_loops(0, "POSIX_ELOOP");
     require_writable(0, "POSIX_EROFS");
     require_empty_dir(0, "POSIX_ENOTEMPTY");
     require_regular_file(0, "POSIX_EINVAL");
     require_not_fifo(0, "POSIX_ENXIO");
     require_permission(0, "POSIX_EPERM");
     require_io_success(0, "POSIX_EIO");
     require_device(0, "POSIX_ENODEV");
     require_not_busy(0, "POSIX_ETXTBSY");
     require_file_size(0, "POSIX_EFBIG");
     require_name_length(0, "POSIX_ENAMETOOLONG");
     require_same_device(0, "POSIX_EXDEV");
     require_fresh_handle(0, "POSIX_ESTALE");
     require_pipe_ready(0, "POSIX_EPIPE");
     require_valid_encoding(0, "POSIX_EILSEQ");
     require_supported(0, "POSIX_ENOTSUP");
     require_recoverable(0, "POSIX_ENOTRECOVERABLE");
     require_owner_alive(0, "POSIX_EOWNERDEAD");

     getchar();
     printf("Memory/Address Contracts\n");
     // =============================================================================
     require_address(0, "POSIX_EFAULT");
     require_mem(0, "POSIX_ENOMEM");
     require_aligned(0, "POSIX_EINVAL");

     getchar();
     printf("Math/Domain Contracts\n");
     // =============================================================================
     require_domain(0, "POSIX_EDOM");
     require_range(0, "POSIX_ERANGE");

     getchar();
     printf("Network Contracts\n");
     // =============================================================================
     //require_connected(0, "POSIX_ENOTCONN");
     //require_addr_free(0, "POSIX_EADDRINUSE");
     require_not_already_connecting(0,"POSIX_EALREADY");
     require_host_reachable(0,"POSIX_EHOSTUNREACH");
     require_network_up(0, "POSIX_ENETDOWN");
     require_no_timeout(0, "POSIX_ETIMEDOUT");
     require_proto_available(0, "POSIX_EPROTONOSUPPORT");
     //require_no_multihop(0, "POSIX_EMULTIHOP");

     getchar();
     printf("STREAMS Contracts (Obscure POSIX)\n");
     // =============================================================================
     //require_stream_dev(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENOSTR)
     //require_stream_buf(cond, msg)     _CONTRACT_ENFORCE(cond, msg, POSIX_ENOSR)
     require_stream_alive(0,"POSIX_ENODEV");

     printf("\nDone now uncomment //abort \n");
}

#endif
