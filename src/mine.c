#include <ncurses.h>

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

typedef struct WinBlocks{
    WINDOW *winBoard;
    WINDOW *winNext;
    WINDOW *winInfo;
    WINDOW *winRules;
} WinBlocks;

#define RATIO 2
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int main() {
    int y = 0;
    int x = 0;
    int cols, rows;

    initscr();
    keypad(stdscr, 1); //allow arrow keys
    noecho(); //don't display input
    curs_set(0); //hide cursor
    getmaxyx(stdscr, rows, cols);
    
    WinBlocks winGame;
    winGame.winBoard = newwin(BOARD_HEIGHT, BOARD_WIDTH * RATIO, y, x);
    winGame.winNext = newwin(7, 5 * RATIO, y, x + (BOARD_WIDTH * RATIO));
    winGame.winInfo = newwin(20, 10 * RATIO, y, x);
    winGame.winRules = newwin(7, 5 * RATIO, y, x+21);

    refresh();
    box(winGame.winBoard, 0, 0);
    box(winGame.winNext, 0, 0);
    wrefresh(winGame.winBoard);
    wrefresh(winGame.winNext);
    getch();

    endwin();

    return 0;
}