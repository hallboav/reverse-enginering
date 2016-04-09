#include <stdio.h>
#include <unistd.h>

typedef struct {
  unsigned int mana;
} player_t;

// 0x601044
player_t player;

void main() {
  player.mana = 104;

  while(1) {
    printf("Current player mana is %u\n", player.mana);
    usleep(2000000);
  }
}
