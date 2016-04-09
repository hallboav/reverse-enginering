#include <stdio.h>

#define MANA_ADDR 0x601044

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("usage:\nptrace %%u <pid>\n");
    return 1;
  }

  return 0;
}
