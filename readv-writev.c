#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/uio.h>

#define MANA_ADDR 0x601044

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

  // Entrada do usuário não é verificada
  pid_t pid = strtol(argv[1], 0, 10);

  unsigned int current_mana;
  ssize_t bytes_read = remote_read32(pid, &current_mana, (void *) MANA_ADDR);
  if (bytes_read != sizeof current_mana) {
    fprintf(stderr, "%s\n", strerror(errno));
    return 2;
  }

  current_mana += 301;
  ssize_t bytes_written = remote_write32(pid, &current_mana, (void *) MANA_ADDR);
  if (bytes_written != sizeof current_mana) {
    fprintf(stderr, "%s\n", strerror(errno));
    return 3;
  }

  printf("Done!\n");
  return 0;
}
