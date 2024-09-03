#ifndef BACKEND_H
#define BACKEND_H

#include <ncurses.h>

#include "tetris.h"
Figure baseFigure();
int **create_field(int y, int x);
void Constructor(GameInfo_t *gameInfo);
void Destructor(GameInfo_t *gameInfo);
int isRotatable(GameInfo_t *gameInfo);
void printCurFigureInfo(GameInfo_t *gameInfo);
void delete_field(int **matrix);

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
void Drop(GameInfo_t *gameInfo);

int killLines(GameInfo_t *gameInfo);
int isEnd(GameInfo_t *gameInfo);
void FixOnBoard(GameInfo_t *gameInfo);
int IsUp(GameInfo_t *gameInfo);
int load_record(const char *filename);
void save_record(const char *filename, int newRecord);
void update_record(GameInfo_t *gameInfo, const char *filename);
#endif