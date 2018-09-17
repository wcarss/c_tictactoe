#include "game.h"

//define GAME_UNSET 0
//define GAME_RUNNING 1
//define GAME_OVER 2

//define NO_RESULT 0
//define O_WINS 1
//define X_WINS 2
//define TIE_GAME 3

//define STARTING_PLAYER 0
//define PLAYER_X_INDEX 0
//define PLAYER_O_INDEX 1
//define PLAYER_X_CHAR 'X'
//define PLAYER_O_CHAR 'O'
//define UNSET_CHECK_PIECE = 'Z'
//define BLANK_SPACE ' '

//define BOARD_SIZE 3
//define MAX_MOVES 3*3


//typedef struct {
//  int state;
//  int player_index;
//  int move_count;
//  char[BOARD_SIZE][BOARD_SIZE] board;
//  char[2] players;
//} Game;


Game *create_game() {
  int i = 0, j = 0;

  Game *game = malloc(sizeof(Game));
  game->state = GAME_RUNNING;
  game->move_count = 0;
  game->player_index = STARTING_PLAYER;
  game->players[PLAYER_X_INDEX] = PLAYER_X_CHAR;
  game->players[PLAYER_O_INDEX] = PLAYER_O_CHAR;
  game->board = malloc(sizeof(char *)*BOARD_SIZE);

  for (i = 0; i < BOARD_SIZE; i++) {
    game->board[i] = malloc(sizeof(char)*BOARD_SIZE);
    for (j = 0; j < BOARD_SIZE; j++) {
      game->board[i][j] = BLANK_SPACE;
    }
  }

  return game;
}

void destroy_game(Game *game) {
  int i = 0;
  for (i = 0; i < BOARD_SIZE; i++) {
    free(game->board[i]);
  }
  free(game->board);
  free(game);
}

void take_turn(Game *game) {
  int state = NO_RESULT;

  print_board(game->board);
  get_and_process_input(game);
  flip_player(game);
  state = check_victory(game);

  if (state ) {
    printf("\n\nGAME OVER!!! ");
    switch (state) {
      case X_WINS:
        printf("Congratulations X, you win! ");
      break;
      case O_WINS:
        printf("Congratulations O, you win! ");
      break;
      case TIE_GAME:
        printf("Oh no, cat's game! ");
      break;
    }
    printf("Here's the final state:\n\n");
    print_board(game->board);
    game->state = GAME_OVER;
  }
}

void get_and_process_input(Game *game) {
  int valid_move = 0;
  char row, col, input[10];
  char row_offset = 'A';
  char col_offset = '1';

  print_player(game);
  while (!valid_move) {
    scanf("%s", &input);
    if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
      printf("Okay, exiting now!\n\n");
      game->state = GAME_OVER;
      break;
    } else if (strlen(input) > 2) {
      printf("Your input wasn't formatted like A1, B2, C3, etc -- it was too long. Give a new full move: ");
      continue;
    }

    row = input[0];
    col = input[1];

    if (row >= 'A' && row <= 'C') {
      row_offset = 'A';
    } else if (row >= 'a' && row <= 'c') {
      row_offset = 'a';
    } else {
      printf("Your row input, '%c', wasn't valid. Give a new full move (e.g. A1, B3, C2): ", row);
      continue;
    }

    if (col < '1' || col > '3') {
      printf("Your col input, '%c', wasn't valid. Give a new full move (e.g. A1, B3, C2): ", col);
      continue;
    }

    row -= row_offset; // convert from letter to numerical index
    col -= col_offset; // convert from 1-index to 0-index

    if (game->board[row][col] != BLANK_SPACE) {
      printf("Your row+col input, '%c%c', was already taken. Give a new full move (e.g. A1, B3, C2): ", row+row_offset, col+col_offset);
    } else {
      valid_move = 1;
      game->board[row][col] = game->players[game->player_index];
    }
  }
}

void print_player(Game *game) {
  printf("It is %c's turn. Make your move: (e.g. A1, B1, C3) ", game->players[game->player_index]);
}

void print_board(char **board) {
  int i = 0, j = 0;

  printf("\n");
  printf("  1   2   3\n");
  printf("A %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
  printf(" ---|---|---\n");
  printf("B %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
  printf(" ---|---|---\n");
  printf("C %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
  printf("\n");
}

int check_victory(Game *game) {
  char check_piece = UNSET_CHECK_PIECE;
  char **b = (char **)game->board;

  int r1 = b[0][0] != BLANK_SPACE && b[0][0] == b[0][1] && b[0][0] == b[0][2];
  int r2 = b[1][0] != BLANK_SPACE && b[1][0] == b[1][1] && b[1][0] == b[1][2];
  int r3 = b[2][0] != BLANK_SPACE && b[2][0] == b[2][1] && b[2][0] == b[2][2];
  int c1 = b[0][0] != BLANK_SPACE && b[0][0] == b[1][0] && b[0][0] == b[2][0];
  int c2 = b[0][1] != BLANK_SPACE && b[0][1] == b[1][1] && b[0][1] == b[2][1];
  int c3 = b[0][2] != BLANK_SPACE && b[0][2] == b[1][2] && b[0][2] == b[2][2];
  int d1 = b[0][0] != BLANK_SPACE && b[0][0] == b[1][1] && b[0][0] == b[2][2];
  int d2 = b[0][2] != BLANK_SPACE && b[0][2] == b[1][1] && b[0][2] == b[2][0];

  if (r1 || c1 || d1) {
    check_piece = b[0][0];
  } else if (r2 || c2 || d2) {
    check_piece = b[1][1];
  } else if (r3 || c3) {
    check_piece = b[2][2];
  }

  if (check_piece == PLAYER_X_CHAR) {
    return X_WINS;
  } else if (check_piece == PLAYER_O_CHAR) {
    return O_WINS;
  } else if (game->move_count >= MAX_MOVES) {
    return TIE_GAME;
  } else {
    return NO_RESULT;
  }
}

void flip_player(Game *game) {
  game->player_index += 1;
  game->player_index %= 2;
  game->move_count += 1;
}
