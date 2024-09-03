#include "tetris.h"

int **create_field(int y, int x) {
  int **matrix = (int **)calloc(y, sizeof(int *));
  for (int i = 0; i < y; i++) {
    matrix[i] = (int *)calloc(x, sizeof(int));
  }
  return matrix;
}

void clear_field(GameInfo_t *gameInfo) {  // переделать
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    for (int j = 0; j < MATRIX_WIDTH; j++) {
      if (gameInfo->field[i][j] != 8) {
        gameInfo->field[i][j] = 0;
      }
    }
  }
}
void clear_next(GameInfo_t *gameInfo) {
  for (int i = 0; i < NEXT_HEIGHT; i++) {
    for (int j = 0; j < NEXT_WIDTH; j++) {
      if (gameInfo->next[i][j] != 8) {
        gameInfo->next[i][j] = 0;
      }
    }
  }
}
void delete_field(int **matrix) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void FigureOnNext(GameInfo_t *gameInfo) {
  clear_next(gameInfo);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    gameInfo->next[gameInfo->next_figure.y[i] - gameInfo->next_figure.center_y +
                   3][gameInfo->next_figure.x[i] -
                      gameInfo->next_figure.center_x + 3] =
        gameInfo->next_figure.id;
  }
}

Figure baseFigure() {
  Figure figure;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.x[i] = -1;
    figure.y[i] = -1;
  }

  figure.center_x = -1;
  figure.center_y = -1;
  figure.id = 0;
  return figure;
}

void createNextFigure(GameInfo_t *gameInfo) {
  int centerX = MATRIX_WIDTH / 2;  // координата центра х
  int ID;
  for (int i = 0; i < 8; i++) {
    ID = rand() % 7;
  }

  switch (ID) {
    case 0:
      // ##
      // ##
      gameInfo->next_figure.x[0] = centerX;
      gameInfo->next_figure.x[1] = centerX;
      gameInfo->next_figure.x[2] = centerX + 1;
      gameInfo->next_figure.x[3] = centerX + 1;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -1;
      gameInfo->next_figure.y[2] = -2;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX + 1;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 1;
      break;
    case 1:
      // ####
      gameInfo->next_figure.x[0] = centerX - 1;
      gameInfo->next_figure.x[1] = centerX;
      gameInfo->next_figure.x[2] = centerX + 1;
      gameInfo->next_figure.x[3] = centerX + 2;
      gameInfo->next_figure.y[0] = -1;
      gameInfo->next_figure.y[1] = -1;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX + 1;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 2;
      break;
    case 2:
      // ##
      //  ##
      gameInfo->next_figure.x[0] = centerX - 1;
      gameInfo->next_figure.x[1] = centerX;
      gameInfo->next_figure.x[2] = centerX;
      gameInfo->next_figure.x[3] = centerX + 1;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -2;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 3;
      break;
    case 3:
      // ##
      // ###
      gameInfo->next_figure.x[0] = centerX;
      gameInfo->next_figure.x[1] = centerX + 1;
      gameInfo->next_figure.x[2] = centerX - 1;
      gameInfo->next_figure.x[3] = centerX;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -2;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 4;
      break;
    case 4:
      // #
      // ###
      gameInfo->next_figure.x[0] = centerX - 1;
      gameInfo->next_figure.x[1] = centerX - 1;
      gameInfo->next_figure.x[2] = centerX;
      gameInfo->next_figure.x[3] = centerX + 1;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -1;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 5;
      break;
    case 5:
      //  #
      // ###
      gameInfo->next_figure.x[0] = centerX + 1;
      gameInfo->next_figure.x[1] = centerX - 1;
      gameInfo->next_figure.x[2] = centerX;
      gameInfo->next_figure.x[3] = centerX + 1;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -1;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 6;
      break;
    case 6:
      // #
      // ###
      gameInfo->next_figure.x[0] = centerX;
      gameInfo->next_figure.x[1] = centerX - 1;
      gameInfo->next_figure.x[2] = centerX;
      gameInfo->next_figure.x[3] = centerX + 1;
      gameInfo->next_figure.y[0] = -2;
      gameInfo->next_figure.y[1] = -1;
      gameInfo->next_figure.y[2] = -1;
      gameInfo->next_figure.y[3] = -1;
      gameInfo->next_figure.center_x = centerX;
      gameInfo->next_figure.center_y = -1;
      gameInfo->next_figure.id = 7;
      break;
    default:
      break;
  }
}

void Constructor(GameInfo_t *gameInfo) {
  gameInfo->field = create_field(MATRIX_HEIGHT, MATRIX_WIDTH);
  gameInfo->next = create_field(NEXT_HEIGHT, NEXT_WIDTH);
  gameInfo->score = 0;
  gameInfo->record = 0;
  gameInfo->level = 1;
  gameInfo->speed = 0;
  gameInfo->pause = 0;
  gameInfo->cur_figure = baseFigure();
  gameInfo->next_figure = baseFigure();
  createNextFigure(gameInfo);
  FigureOnNext(gameInfo);
}

void createFigure(GameInfo_t *gameInfo) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    gameInfo->cur_figure.y[i] = gameInfo->next_figure.y[i];
    gameInfo->cur_figure.x[i] = gameInfo->next_figure.x[i];
  }
  gameInfo->cur_figure.center_x = gameInfo->next_figure.center_x;
  gameInfo->cur_figure.center_y = gameInfo->next_figure.center_y;
  gameInfo->cur_figure.id = gameInfo->next_figure.id;

  createNextFigure(gameInfo);
  FigureOnNext(gameInfo);
}

void FigureOnBoard(GameInfo_t *gameInfo) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if (gameInfo->cur_figure.y[i] >= 0) {
      gameInfo->field[gameInfo->cur_figure.y[i]][gameInfo->cur_figure.x[i]] =
          gameInfo->cur_figure.id;
    }
  }
}

void printCurFigureInfo(GameInfo_t *gameInfo) {
  mvprintw(30, 0, "CURRENT FIGURE");
  mvprintw(31, 0, "ID: %d", gameInfo->cur_figure.id);
  mvprintw(32, 0, "Center: (%d, %d)", gameInfo->cur_figure.center_x,
           gameInfo->cur_figure.center_y);
  mvprintw(33, 0, "Coordinates:");
  for (int i = 0; i < FIGURE_SIZE; i++) {
    mvprintw(34 + i, 0, "(%d, %d)", gameInfo->cur_figure.x[i],
             gameInfo->cur_figure.y[i]);
  }
  refresh();
}

void FixOnBoard(GameInfo_t *gameInfo) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if (gameInfo->cur_figure.y[i] >= 0) {
      gameInfo->field[gameInfo->cur_figure.y[i]][gameInfo->cur_figure.x[i]] = 8;
    }
  }
}

// Реализация функции
int isRotatable(GameInfo_t *gameInfo) {
  if (gameInfo->cur_figure.id == 1) return 0;

  int MAXX = MATRIX_WIDTH;
  int MAXY = MATRIX_HEIGHT;

  int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

  // Рассчитайте новые координаты после поворота
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int nx = gameInfo->cur_figure.x[i] - gameInfo->cur_figure.center_x;
    int ny = gameInfo->cur_figure.y[i] - gameInfo->cur_figure.center_y;

    // Поворот на 90 градусов против часовой стрелки
    newX[i] = nx * 0 + ny * (-1) + gameInfo->cur_figure.center_x;
    newY[i] = nx * 1 + ny * 0 + gameInfo->cur_figure.center_y;

    if (newX[i] < 0 || newX[i] >= MAXX || newY[i] >= MAXY) {
      //   printw("100");
      return 0;  // false
    }

    if (newY[i] >= 0 && gameInfo->field[newY[i]][newX[i]] != 0) {
      //   printw("200");
      return 0;  // false
    }
  }

  // Назначаем новые координаты
  for (int i = 0; i < FIGURE_SIZE; i++) {
    gameInfo->cur_figure.x[i] = newX[i];
    gameInfo->cur_figure.y[i] = newY[i];
  }

  return 1;
}

int Move(GameInfo_t *gameInfo, int dx, int dy) {
  int MAXX = MATRIX_WIDTH;
  int MAXY = MATRIX_HEIGHT;

  int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

  for (int i = 0; i < FIGURE_SIZE; i++) {
    newX[i] = gameInfo->cur_figure.x[i] + dx;
    newY[i] = gameInfo->cur_figure.y[i] + dy;

    if (newX[i] < 0 || newX[i] >= MAXX || newY[i] >= MAXY) {
      //   printw("100");
      return 0;  // false
    }

    if (newY[i] >= 0 && gameInfo->field[newY[i]][newX[i]] != 0) {
      //   printw("200");
      return 0;  // false
    }
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    gameInfo->cur_figure.x[i] = newX[i];
    gameInfo->cur_figure.y[i] = newY[i];
  }

  gameInfo->cur_figure.center_x += dx;
  gameInfo->cur_figure.center_y += dy;

  //   if (dy > 0 || dx > 0 || dx < 0) {
  //     for (int i = 0; i < FIGURE_SIZE; i++) {
  //       if (gameInfo->cur_figure.y[i] == MAXY - 1 ||
  //           gameInfo->field[gameInfo->cur_figure.y[i] + 1]
  //                          [gameInfo->cur_figure.x[i]] == 8) {
  //         for (int j = 0; j < FIGURE_SIZE; j++) {
  //           gameInfo
  //               ->field[gameInfo->cur_figure.y[j]][gameInfo->cur_figure.x[j]]
  //               = 8;
  //         }
  //         printw("300");
  //         return 300;  // false
  //       }
  //     }
  //   }
  //   printw("1");
  return 1;  // true
}

int MoveLeft(GameInfo_t *gameInfo) {
  if (Move(gameInfo, -1, 0))
    return 1;
  else
    return 0;
}

int MoveRight(GameInfo_t *gameInfo) {
  if (Move(gameInfo, 1, 0))
    return 1;
  else
    return 0;
}

int Rotate(GameInfo_t *gameInfo) {
  if (isRotatable(gameInfo))
    return 1;
  else
    return 0;
}

int MoveDown(GameInfo_t *gameInfo) {
  if (Move(gameInfo, 0, 1))
    return 1;
  else {
    // isend killines

    return 0;
  }
}

int killLines(GameInfo_t *gameInfo) {
  int lines_cleared = 0;
  int y, x, full_line;
  int diff = 200;

  for (y = MATRIX_HEIGHT - 1; y >= 0; y--) {
    full_line = 1;
    for (x = 0; x < MATRIX_WIDTH; x++) {
      if (gameInfo->field[y][x] == 0) {
        full_line = 0;
        break;
      }
    }

    if (full_line) {
      lines_cleared++;
      // Сдвигаем все линии выше текущей вниз
      for (int i = y; i > 0; i--) {
        for (x = 0; x < MATRIX_WIDTH; x++) {
          gameInfo->field[i][x] = gameInfo->field[i - 1][x];
        }
      }
      // Очищаем верхнюю линию
      for (x = 0; x < MATRIX_WIDTH; x++) {
        gameInfo->field[0][x] = 0;
      }
      y++;  // Проверяем эту же линию снова, так как мы сдвинули все вниз
    }
  }

  // Обновляем счет
  if (lines_cleared > 0) {
    int points = 0;
    switch (lines_cleared) {
      case 1:
        points = 100;
        break;
      case 2:
        points = 300;
        break;
      case 3:
        points = 700;
        break;
      case 4:
        points = 1500;
        break;
      default:
        points = 1500 * (lines_cleared - 3) + 700;
        break;
    }
    gameInfo->score += points;
    // Можно добавить логику повышения уровня здесь
  }

  return lines_cleared;
}

int IsUp(GameInfo_t *gameInfo) {
  // если в верхней строке есть 1, то игра заканчивается
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    if (gameInfo->field[0][i] == 8) {
      return 1;  // если за гранью
    }
  }
  return 0;  // норм
}
