

#include "tetris.h"
#include "frontend.h"

void CreateBoards(int y, int x, WinBlocks *winGame) {
    winGame->winBoard = newwin(BOARD_HEIGHT, BOARD_WIDTH, y, x);
    winGame->winNext = newwin(NEXT_HEIGHT, NEXT_WIDTH, y, x + BOARD_WIDTH + 1);
    winGame->winInfo = newwin(INFO_HEIGHT, INFO_WIDTH, y + NEXT_HEIGHT, x + BOARD_WIDTH + 1);
    winGame->winRules = newwin(RULES_HEIGHT, RULES_WIDTH, y + BOARD_HEIGHT, x );

    refresh();
    box(winGame->winBoard, 0, 0);
    box(winGame->winNext, 0, 0);
    box(winGame->winInfo, 0, 0);
    box(winGame->winRules, 0, 0);

    wrefresh(winGame->winBoard);
    wrefresh(winGame->winNext);
    wrefresh(winGame->winInfo);
    wrefresh(winGame->winRules);

    mvwprintw(winGame->winRules, 1, 2, "CONTROLS:");
    mvwprintw(winGame->winRules, 1, 18, "<, >, v - move");
    mvwprintw(winGame->winRules, 3, 18, "UP - rotate");
    wrefresh(winGame->winRules);

    mvwprintw(winGame->winInfo, 1, 2, "SCORE:");
    mvwprintw(winGame->winInfo, 4, 2, "RECORD:");
    mvwprintw(winGame->winInfo, 7, 2, "LEVEL:");
    wrefresh(winGame->winInfo);

}

#define COLOR_ORANGE 8 
void SetUp(WinBlocks *winGame) {
    int y = 0;
    int x = 0;
    int cols, rows;
    initscr();
    start_color();
    init_color(COLOR_BLACK, 100, 100, 100);
    init_color(COLOR_ORANGE, 254, 103, 0);
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_ORANGE);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    init_pair(7, COLOR_BLACK, COLOR_CYAN);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    keypad(stdscr, 1); //allow arrow keys
    noecho(); //don't display input
    curs_set(0); //hide cursor
    getmaxyx(stdscr, rows, cols);

    CreateBoards(x, y, winGame);

}


void draw_game(GameInfo_t gameInfo,WinBlocks winGame) {
    draw_board(gameInfo, winGame);

}

void draw_board(GameInfo_t gameInfo, WinBlocks winGame) {
    // Определите отступы для центрирования

    int vertical_offset = (22 - MATRIX_HEIGHT) / 2;
    int horizontal_offset = (22 - MATRIX_WIDTH * 2) / 2;

    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        
        for ( int j = 0; j < MATRIX_WIDTH; j++) {
            // Получаем цвет из матрицы
            int color = gameInfo.field[i][j] % 100;
            
            // Устанавливаем цвет
            wattron(winGame.winBoard, COLOR_PAIR(color));
            
            // Отрисовываем блок
            mvwprintw(winGame.winBoard, vertical_offset + i, horizontal_offset + j * 2, "%d", gameInfo.field[i][j] % 100);
            
            // Отключаем цвет
            wattroff(winGame.winBoard, COLOR_PAIR(color));
        }
        wprintw(winGame.winBoard,  "\n" );
    }

    // Обновляем окно
    wrefresh(winGame.winBoard);
}


// int Move(GameInfo_t *gameInfo, int dx, int dy) {
    
//     int MAXX = MATRIX_WIDTH;
//     int MAXY = MATRIX_HEIGHT;
    
//     int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

//     // Рассчитайте новые координаты
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         newX[i] = gameInfo->next_figure.x[i] + dx;
//         newY[i] = gameInfo->next_figure.y[i] + dy;
        
//         // Проверьте новые координаты
//         if (newX[i] < 0 || newX[i] >= MAXX) {
//             // mvprintw(20,20,"newX: %d\n", newX[i]);
//         //      printw("newX: %d\n", newX[i]);
//         //  printw("newY: %d\n", newY[i]);
//             return 100;  // false
//         }

//         if (newY[i] > 0 && newY[i] < MAXY ) {
//             if (gameInfo->field[newX[i]][newY[i]] != 0) {
//         //         printw("gameInfo->field[newX[i]][newY[i]]: %d\n", gameInfo->field[newX[i]][newY[i]]);
//         //          printw("newX: %d\n", newX[i]);
//         //  printw("newY: %d\n", newY[i]);
//                 return 200;  // false
//             }
//         } else if (newY[i] >= MAXY) {
//             return 300;  // false
//         }
//     }

//     // Назначаем новые координаты
//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         gameInfo->next_figure.x[i] = newX[i];
//         gameInfo->next_figure.y[i] = newY[i];
//     }

//     gameInfo->next_figure.center_x += dx;
//     gameInfo->next_figure.center_y += dy;

//     return 1;  // true
// }






// int Move(GameInfo_t *gameInfo, int dx, int dy) {
//     int MAXX = MATRIX_WIDTH;
//     int MAXY = MATRIX_HEIGHT;

//     int newX[FIGURE_SIZE], newY[FIGURE_SIZE];

//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         newX[i] = gameInfo->next_figure.x[i] + dx;
//         newY[i] = gameInfo->next_figure.y[i] + dy;

//         if (newX[i] < 0 || newX[i] >= MAXX) {
//             return 100;  // false
//         }

//         if (newY[i] >= 0 && gameInfo->field[newY[i]][newX[i]] != 0 ) {
            
//             return 200;  // false
//         }
//         if (newY[i] >= MAXY) {
//             return 300;  // false
//         }

//     }

//     for (int i = 0; i < FIGURE_SIZE; i++) {
//         gameInfo->next_figure.x[i] = newX[i];
//         gameInfo->next_figure.y[i] = newY[i];
//     }

//     gameInfo->next_figure.center_x += dx;
//     gameInfo->next_figure.center_y += dy;

//     if (dy > 0) {
//         for (int i = 0; i < FIGURE_SIZE; i++) {
//             if (gameInfo->next_figure.y[i] == MAXY - 1 || gameInfo->field[gameInfo->next_figure.y[i] + 1][gameInfo->next_figure.x[i]] == 8) {
//                 for (int j = 0; j < FIGURE_SIZE; j++) {
//                     gameInfo->field[gameInfo->next_figure.y[j]][gameInfo->next_figure.x[j]] = 8;
//                 }
//                 return 300;  // false
//             }
//         }
//     }

//     return 1;  // true
// }
