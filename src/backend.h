#ifndef BACKEND_H
#define BACKEND_H

#include <ncurses.h>

#include "tetris.h"
Figure baseFigure();
void Constructor(GameInfo_t *gameInfo);
int isRotatable(GameInfo_t *gameInfo);
void printCurFigureInfo(GameInfo_t *gameInfo);

void createNextFigure(GameInfo_t *gameInfo);
void createFigure(GameInfo_t *gameInfo);
void FigureOnBoard(GameInfo_t *gameInfo);
void FigureOnNext(GameInfo_t *gameInfo);
int Move(GameInfo_t *gameInfo, int dx, int dy);
void MoveFigure(GameInfo_t *gameInfo);

void clear_field(GameInfo_t *gameInfo);
void clear_next(GameInfo_t *gameInfo);

int MoveLeft(GameInfo_t *gameInfo);
int MoveRight(GameInfo_t *gameInfo);
int MoveDown(GameInfo_t *gameInfo);
int Rotate(GameInfo_t *gameInfo);

#endif