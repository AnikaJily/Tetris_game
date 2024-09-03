#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "tetris.h"

// Прототип функции DrawBoards
void CreateBoards(int y, int x, WinBlocks *winGame);
void SetUp(WinBlocks *winGame);
void draw_board(GameInfo_t gameInfo, WinBlocks winGame);
void draw_game(GameInfo_t gameInfo, WinBlocks winGame);
void draw_next(GameInfo_t gameInfo, WinBlocks winGame);
void game_over(WINDOW *win);
void draw_info(GameInfo_t gameInfo, WinBlocks winGame);
#endif