#include "tetris.h"
 
 
 int** create_field(int y, int x) {
  int **matrix = (int **)calloc(y, sizeof(int *));
  for (int i = 0; i < y; i++) {
    matrix[i] = (int *)calloc(x, sizeof(int));
  }
  return matrix;
}

void clear_field(GameInfo_t *gameInfo) { //переделать
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    for (int j = 0; j < MATRIX_WIDTH; j++) {
        if (gameInfo->field[i][j] != 8) {
            gameInfo->field[i][j] = 0;
        }
    }
  }
}

void delete_field(int** matrix) {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

Figure baseFigure() {
    Figure figure;
    for(int i = 0; i < FIGURE_SIZE; i++) {
        figure.x[i] = -1;
        figure.y[i] = -1;
    }

    figure.center_x = -1;
    figure.center_y = -1;
    figure.id = 0;
    return figure;
}

void Constructor(GameInfo_t *gameInfo) {
    gameInfo->field = create_field(MATRIX_HEIGHT, MATRIX_WIDTH);
    gameInfo->next = create_field(NEXT_HEIGHT, NEXT_WIDTH);
    gameInfo->score = 0;
    gameInfo->high_score = 0;
    gameInfo->level = 1;
    gameInfo->speed = 0;
    gameInfo->pause = 0;
    gameInfo->cur_figure = baseFigure();
    gameInfo->next_figure = baseFigure();
}


void createNextFigure(GameInfo_t *gameInfo) {
    int centerX = MATRIX_WIDTH / 2; // координата центра х
    int ID;
    for (int i = 0; i < 8; i++) {  
        ID = rand() % 7; 
    }
    
    // int ID = random() % 7; 
    // printf("%d\n", ID);
     //создание блоков по id
    switch (ID) {
    case 0:
        //##
        //##
        gameInfo->next_figure.x[0] = centerX;
        gameInfo->next_figure.x[1] = centerX;
        gameInfo->next_figure.x[2] = centerX + 1;
        gameInfo->next_figure.x[3] = centerX + 1;
        gameInfo->next_figure.y[0] = -2;
        gameInfo->next_figure.y[1] = -1;
        gameInfo->next_figure.y[2] = -2;
        gameInfo->next_figure.y[3] = -1;
        gameInfo->next_figure.center_x = 0;
        gameInfo->next_figure.center_y = 0;
        gameInfo->next_figure.id = 1;
        break;
    case 1:
        //####
        gameInfo->next_figure.x[0] = centerX - 1;
        gameInfo->next_figure.x[1] = centerX;
        gameInfo->next_figure.x[2] = centerX + 1;
        gameInfo->next_figure.x[3] = centerX + 2;
        gameInfo->next_figure.y[0] = -1;
        gameInfo->next_figure.y[1] = -1;
        gameInfo->next_figure.y[2] = -1;
        gameInfo->next_figure.y[3] = -1;
        gameInfo->next_figure.center_x = centerX;
        gameInfo->next_figure.center_y = -1;
        gameInfo->next_figure.id = 2;
        break;
    case 2:
        //##
        // ##
        gameInfo->next_figure.x[0] = centerX - 1;
        gameInfo->next_figure.x[1] = centerX;
        gameInfo->next_figure.x[2] = centerX;
        gameInfo->next_figure.x[3] = centerX + 1;
        gameInfo->next_figure.y[0] = -2;
        gameInfo->next_figure.y[1] = -2;
        gameInfo->next_figure.y[2] = -1;
        gameInfo->next_figure.y[3] = -1;
        gameInfo->next_figure.center_x = centerX;
        gameInfo->next_figure.center_y = -2;
        gameInfo->next_figure.id = 3;
        break;
    case 3:
        // ##
        //##
        gameInfo->next_figure.x[0] = centerX;
        gameInfo->next_figure.x[1] = centerX + 1;
        gameInfo->next_figure.x[2] = centerX - 1;
        gameInfo->next_figure.x[3] = centerX;
        gameInfo->next_figure.y[0] = -2;
        gameInfo->next_figure.y[1] = -2;
        gameInfo->next_figure.y[2] = -1;
        gameInfo->next_figure.y[3] = -1;
        gameInfo->next_figure.center_x = centerX;
        gameInfo->next_figure.center_y = -2;
        gameInfo->next_figure.id = 4;
        break;
    case 4:
        //#
        //###
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
        //###
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
        //###
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

void FigureOnBoard(GameInfo_t *gameInfo) {
   
    for (int i = 0; i < FIGURE_SIZE; i++) {
        if(gameInfo->next_figure.y[i] >= 0) {
            gameInfo->field[gameInfo->next_figure.y[i]][gameInfo->next_figure.x[i]] = gameInfo->next_figure.id;
        }
    }
}

void FigureOnNextBoard(GameInfo_t *gameInfo) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
            gameInfo->field[gameInfo->next_figure.y[i]][gameInfo->next_figure.x[i]] = gameInfo->next_figure.id;
    }
}

int Move(GameInfo_t *gameInfo, int dx, int dy) {
    
    int MAXX = MATRIX_WIDTH;
    int MAXY = MATRIX_HEIGHT;
    
    int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

    // Рассчитайте новые координаты
    for (int i = 0; i < FIGURE_SIZE; i++) {
        newX[i] = gameInfo->next_figure.x[i] + dx;
        newY[i] = gameInfo->next_figure.y[i] + dy;
        
        // Проверьте новые координаты
        if (newX[i] < 0 || newX[i] >= MAXX) {
            return 100;  // false
        }

        if (newY[i] > 0 && newY[i] < MAXY ) {
            if (gameInfo->field[newX[i]][newY[i]] != 0) {
                return 200;  // false
            }
        } else if (newY[i] >= MAXY) {
            return 300;  // false
        }
    }

    // Назначаем новые координаты
    for (int i = 0; i < FIGURE_SIZE; i++) {
        gameInfo->next_figure.x[i] = newX[i];
        gameInfo->next_figure.y[i] = newY[i];
    }

    gameInfo->next_figure.center_x += dx;
    gameInfo->next_figure.center_y += dy;

    return 1;  // true
}


void MoveFigure(GameInfo_t *gameInfo) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
        gameInfo->next_figure.y[i] += 5;
    }
    
}

// Реализация функции
int isRotatable(GameInfo_t *gameInfo) {

    int MAXX = MATRIX_WIDTH;
    int MAXY = MATRIX_HEIGHT;

    int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

    // Рассчитайте новые координаты после поворота
    for (int i = 0; i < FIGURE_SIZE; i++) {
        int nx = gameInfo->next_figure.x[i] - gameInfo->next_figure.center_x;
        int ny = gameInfo->next_figure.y[i] - gameInfo->next_figure.center_y;

        // Поворот на 90 градусов против часовой стрелки
        newX[i] = nx * 0 + ny * (-1) + gameInfo->next_figure.center_x;
        newY[i] = nx * 1 + ny * 0 + gameInfo->next_figure.center_y;

        // Проверьте новые координаты
        if (newX[i] < 0 || newX[i] >= MAXX) {
            return 01;
        }

        if (newY[i] >= 0 && newY[i] < MAXY) {
            if (gameInfo->field[newX[i]][newY[i]] == 1) {
                return 02;
            }
        } else if (newY[i] >= MAXY) {
            return 03;
        }
    }

     // Назначаем новые координаты
    for (int i = 0; i < FIGURE_SIZE; i++) {
        gameInfo->next_figure.x[i] = newX[i];
        gameInfo->next_figure.y[i] = newY[i];
    }

    

    return 55;
}
