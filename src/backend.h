#ifndef BACKEND_H
#define BACKEND_H

#include "tetris.h"
#include <ncurses.h>
Figure baseFigure();
void Constructor(GameInfo_t *gameInfo);

void createNextFigure(GameInfo_t *gameInfo);
void FigureOnBoard(GameInfo_t *gameInfo);
void MoveFigure(GameInfo_t *gameInfo);

#endif