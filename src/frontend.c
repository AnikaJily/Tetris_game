

// typedef struct Figure_t {
//   int **blocks;
//   int x;
//   int y;
//   int color;
//   bool rotatble;
// } Figure_t;

// // figure size
// #define FIGURE_X (BOARD_WIDTH / 2 - 2)
// #define FIGURE_S 5

// void print_figure(Figure_t *figure, WINDOW *win) {
//   for (int row = 0; row < FIGURE_S; row++) {
//     for (int col = 0; col < FIGURE_S; col++) {
//       int y_pos = figure->y + row;
//       int x_pos = figure->x + col;

//       if (figure->blocks[row][col] != 0 && y_pos >= 0) {
//         wbkgdset(win, COLOR_PAIR(figure->color));
//         mvwprintw(win, y_pos + 1, 2 * x_pos + 1, "%c", ' ');
//         mvwprintw(win, y_pos + 1, 2 * x_pos + 2, "%c", ' ');
//       }
//     }
//   }
// }

// typedef enum {
//     Start,
//     Pause,
//     Terminate,
//     Left,
//     Right,
//     Up,
//     Down,
//     Action
// } UserAction_t;

// typedef struct {
//     int **field;
//     int **next;
//     int score;
//     int high_score;
//     int level;
//     int speed;
//     int pause;
// } GameInfo_t;

// void userInput(UserAction_t action, bool hold);

// GameInfo_t updateCurrentState();

// Figure_t *create_figure() {
//   Figure_t *figure = (Figure_t *)malloc(sizeof(Figure_t));
//   figure->blocks = (int **)calloc(FIGURE_S, sizeof(int *));
//   for (int row = 0; row < FIGURE_S; row++) {
//     figure->blocks[row] = (int *)calloc(FIGURE_S, sizeof(int));
//   }
//   figure->y = 0;
//   return figure;
// }

// Figure_t *get_figure() {
//   Figure_t *figure = create_figure();

//   int my_brick[7][FIGURE_S][FIGURE_S] = {

//       {{0, 0, 0, 0, 0},
//        {0, 0, 1, 0, 0},
//        {0, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 0, 0, 0},
//        {0, 1, 1, 0, 0},
//        {0, 0, 1, 1, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 0, 0, 0},
//        {0, 0, 1, 1, 0},
//        {0, 1, 1, 0, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 0, 0, 0},
//        {0, 1, 0, 0, 0},
//        {0, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 0, 0, 0},
//        {0, 0, 0, 1, 0},
//        {0, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 1, 0, 0},
//        {0, 0, 1, 0, 0},
//        {0, 0, 1, 0, 0},
//        {0, 0, 1, 0, 0},
//        {0, 0, 0, 0, 0}},

//       {{0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0},
//        {0, 0, 1, 1, 0},
//        {0, 0, 1, 1, 0},
//        {0, 0, 0, 0, 0}}

//   };

//   int random_brick = rand() % 7;
//   if (random_brick == 6) {
//     figure->rotatble = false;
//   } else {
//     figure->rotatble = true;
//   }
//   for (int i = 0; i < FIGURE_S; i++) {
//     for (int j = 0; j < FIGURE_S; j++) {
//       figure->blocks[i][j] = my_brick[random_brick][i][j];
//     }
//   }

//   figure->color = random_brick + 2;

//   return figure;
// }

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


void SetUp(WinBlocks *winGame) {
    int y = 0;
    int x = 0;
    int cols, rows;
    initscr();
    start_color();
    init_color(COLOR_BLACK, 100, 100, 100);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_CYAN);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
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
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 1; j < BOARD_WIDTH; j+=2) {
                wattron(winGame.winBoard, COLOR_PAIR(gameInfo.field[i][j] % 100 + 1));
                mvwprintw(winGame.winBoard, i, j, "  ");
                wattroff(winGame.winBoard,COLOR_PAIR(gameInfo.field[i][j] % 100 + 1));
        }
    }
    wrefresh(winGame.winBoard);
}

