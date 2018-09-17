#include "game.h"

int main() {

  Game *game = create_game();

  while(game->state != GAME_OVER) {
    take_turn(game);
  }

  destroy_game(game);
  return 0;
}
