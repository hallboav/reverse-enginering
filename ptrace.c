#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ptrace.h>

#define MANA_ADDR 0x601044

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage:\nptrace %%u <pid>\n");
    return 1;
  }

  // Entrada do usuário não verificada
  pid_t pid = strtol(argv[1], 0, 10);

  if (ptrace(PTRACE_ATTACH, pid, 0, 0) == -1) {
    fprintf(stderr, "%s\n", strerror(errno));
    return 2;
  }

  // Esperando tracee parar
  wait(0);

  if (ptrace(PTRACE_DETACH, pid, 0, 0) == -1) {
    fprintf(stderr, "%s\n", strerror(errno));
    return 3;
  }

  return 0;
}
