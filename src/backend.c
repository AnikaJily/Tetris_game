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
        gameInfo->field[i][j] = 0;
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
        gameInfo->next_figure.center_y = 0;
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
            // mvprintw(20,20,"newX: %d\n", newX[i]);
        //      printw("newX: %d\n", newX[i]);
        //  printw("newY: %d\n", newY[i]);
            return 100;  // false
        }

        if (newY[i] > 0 && newY[i] < MAXY ) {
            if (gameInfo->field[newX[i]][newY[i]] != 0) {
        //         printw("gameInfo->field[newX[i]][newY[i]]: %d\n", gameInfo->field[newX[i]][newY[i]]);
        //          printw("newX: %d\n", newX[i]);
        //  printw("newY: %d\n", newY[i]);
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
bool isRotatable(GameInfo_t *gameInfo) {

    int MAXX = MATRIX_WIDTH;
    int MAXY = MATRIX_HEIGHT;

    int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

    // Рассчитайте новые координаты после поворота
    for (int i = 0; i < FIGURE_SIZE; i++) {
        int nx = gameInfo->cur_figure.x[i] - gameInfo->next_figure.center_x;
        int ny = gameInfo->next_figure.y[i] - gameInfo->next_figure.center_y;

        // Поворот на 90 градусов против часовой стрелки
        newX[i] = nx * 0 + ny * (-1) + gameInfo->next_figure.center_x;
        newY[i] = nx * 1 + ny * 0 + gameInfo->next_figure.center_y;

        // Проверьте новые координаты
        if (newX[i] < 0 || newX[i] >= MAXX) {
            return false;
        }

        if (newY[i] >= 0 && newY[i] < MAXY) {
            if (gameInfo->field[newX[i]][newY[i]] == 1) {
                return false;
            }
        } else if (newY[i] >= MAXY) {
            return false;
        }
    }

    return true;
}
/*!
Перемещение фигуры


\param dx Перемещение по х
\param dy Перемещение по у


*/
// bool Tetris::move(int dx, int dy) {

//     int newX[COUNT], newY[COUNT];

//     for (int i = 0; i < COUNT; i++) {
//         newX[i] = block.x[i] + dx;
//         newY[i] = block.y[i] + dy;

//         //проверим новые координаты

//         if(newX[i] < 0 || newX[i] >= MAXX) {
//             return false;
//         }

//         if(newY[i] >= 0 && newY[i] < MAXY) {
//             if(box[newX[i]][newY[i]] == 1) {
//                 return false;
//             }
//         }
//         else if(newY[i] >= MAXY) {
//             return false;
//         }


// // int main() {

// //     int c;
// //     int y = 11;
// //     int x = 5;
// //     int cols, rows;

// //     initscr();
// //     keypad(stdscr, 1); //allow arrow keys
// //     noecho(); //don't display input
// //     curs_set(0); //hide cursor
// //     getmaxyx(stdscr, rows, cols);
// //     char map[rows][cols];

// //     do
// //     {
// //         for (int yy = 0; yy <= rows; yy++) {
// //             for (int xx = 0; xx <= cols; xx++) {
// //                 map[yy][xx] = '#';
// //                 mvaddch(yy, xx, '#');
// //             }
// //         }

// //         for (int yy = 5; yy <= rows / 2; yy++) {
// //             for (int xx = 5; xx <= cols / 2; xx++) {
// //                 map[yy][xx] = ' ';
// //                 mvaddch(yy, xx, ' ');
// //             }
// //         }

// //         //printw("rows - %d, cols - %d", rows, cols);
// //         if (c == KEY_UP && mvinch(y-1, x) != '#' ) y--;
// //         else if (c == KEY_DOWN && mvinch(y+1, x) != '#') y++;
// //         else if (c == KEY_LEFT && mvinch(y, x-1) != '#') x--;
// //         else if (c == KEY_RIGHT && mvinch(y, x+1) != '#') x++;
// //         mvaddch(y, x, '@'); //print cursor
// //     } while ((c = getch()) != 27); //27 - ASCII code for ESC
    

    
// //     getch();

// //     endwin();

// //     return 0;
// // }

// #include "frontend.h"

// int main() {

//     int c;
//     int y = 11;
//     int x = 5;
//     int cols, rows;

//     initscr();
//     keypad(stdscr, 1); //allow arrow keys
//     noecho(); //don't display input
//     curs_set(0); //hide cursor
//     getmaxyx(stdscr, rows, cols);
//     char map[rows][cols];


//     mvwprintw(winGame->winBoard, 1, 1, "Hello, world!");

//     do
//     {
//         for (int yy = 0; yy <= rows; yy++) {
//             for (int xx = 0; xx <= cols; xx++) {
//                 map[yy][xx] = '#';
//                 mvaddch(yy, xx, '#');
//             }
//         }

//         for (int yy = 5; yy <= rows / 2; yy++) {
//             for (int xx = 5; xx <= cols / 2; xx++) {
//                 map[yy][xx] = ' ';
//                 mvaddch(yy, xx, ' ');
//             }
//         }

//         //printw("rows - %d, cols - %d", rows, cols);
//         if (c == KEY_UP && mvinch(y-1, x) != '#' ) y--;
//         else if (c == KEY_DOWN && mvinch(y+1, x) != '#') y++;
//         else if (c == KEY_LEFT && mvinch(y, x-1) != '#') x--;
//         else if (c == KEY_RIGHT && mvinch(y, x+1) != '#') x++;
//         mvaddch(y, x, '@'); //print cursor
//     } while ((c = getch()) != 27); //27 - ASCII code for ESC
    

    
//     getch();

//     endwin();

//     return 0;
// }