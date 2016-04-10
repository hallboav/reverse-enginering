#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/uio.h>

typedef struct iovec iovec_t;

// man process_vm_readv
// These system calls were added in Linux 3.2.
// Support is provided in glibc since version 2.15.

ssize_t remote_read_bytes(pid_t pid, void *local_addr, void *remote_addr, size_t len)
{
  iovec_t local_iov  = {local_addr,  len};
  iovec_t remote_iov = {remote_addr, len};
  return process_vm_readv(pid, &local_iov, 1, &remote_iov, 1, 0);
}

ssize_t remote_write_bytes(pid_t pid, void *local_addr, void *remote_addr, size_t len)
{
  iovec_t local_iov  = {local_addr,  len};
  iovec_t remote_iov = {remote_addr, len};
  return process_vm_writev(pid, &local_iov, 1, &remote_iov, 1, 0);
}

ssize_t remote_read32(pid_t pid, void *local_addr, void *remote_addr)
{
  return remote_read_bytes(pid, local_addr, remote_addr, 4);
}

ssize_t remote_write32(pid_t pid, void *local_addr, void *remote_addr)
{
  return remote_write_bytes(pid, local_addr, remote_addr, 4);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage:\nreadv-writev %%u <pid>\n");
    return 1;
  }

  return 0;
}
