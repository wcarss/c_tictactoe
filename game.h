#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#define GAME_UNSET 0
#define GAME_RUNNING 1
#define GAME_OVER 2

#define NO_RESULT 0
#define O_WINS 1
#define X_WINS 2
#define TIE_GAME 3

#define STARTING_PLAYER 0
#define PLAYER_X_INDEX 0
#define PLAYER_O_INDEX 1
#define PLAYER_X_CHAR 'X'
#define PLAYER_O_CHAR 'O'
#define UNSET_CHECK_PIECE 'Z'
#define BLANK_SPACE ' '

#define BOARD_SIZE 3
#define MAX_MOVES 9


typedef struct Game {
  int state;
  int player_index;
  int move_count;
  char **board;
  char players[2];
} Game;


Game *create_game();
void destroy_game(Game *game);
void take_turn(Game *game);
void get_and_process_input(Game *game);
void print_player(Game *game);
void print_board(char **board);
int check_victory(Game *game);
void flip_player(Game *game);
