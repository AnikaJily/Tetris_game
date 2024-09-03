#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdlib.h>  // Для rand() и srand()
#include <time.h>    // Для time()

#define TIME_FOR_SHIFT 0.3

#define RATIO 2

#define MATRIX_HEIGHT 20
#define MATRIX_WIDTH 10

#define MATRIX_NEXT_HEIGHT 6
#define MATRIX_NEXT_WIDTH 6

// game board
#define BOARD_HEIGHT (MATRIX_HEIGHT + 2)
#define BOARD_WIDTH (MATRIX_WIDTH * 2 + 2)

// next board
#define NEXT_WIDTH MATRIX_NEXT_WIDTH *RATIO + 2
#define NEXT_HEIGHT MATRIX_NEXT_HEIGHT + 2

// info board
#define INFO_WIDTH 7 * RATIO
#define INFO_HEIGHT 14

// rules board
#define RULES_WIDTH 17 * RATIO + 1
#define RULES_HEIGHT 5

#define FIGURE_SIZE 4

#define COLOR_ORANGE 8

typedef struct Figure {
  int id;
  int x[FIGURE_SIZE];
  int y[FIGURE_SIZE];
  int center_x;
  int center_y;

} Figure;

typedef struct {
  int **field;
  int **next;
  int score;
  int record;
  int level;
  int speed;
  int pause;
  Figure cur_figure;
  Figure next_figure;
} GameInfo_t;

typedef struct WinBlocks {
  WINDOW *winBoard;
  WINDOW *winNext;
  WINDOW *winInfo;
  WINDOW *winRules;
} WinBlocks;

#endif