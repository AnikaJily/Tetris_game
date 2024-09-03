#include <sys/time.h>
#include <time.h>

#include "backend.h"
#include "frontend.h"
#include "tetris.h"

typedef enum { START, SPAWN, MOVING, SHIFTING, ATTACHING, GAME_OVER } STATE;

int main() {
  int c = 0;
  WinBlocks winGame;
  SetUp(&winGame);
  GameInfo_t gameInfo;
  Constructor(&gameInfo);
  struct timeval last_fall_time, current_time;
  gettimeofday(&last_fall_time, NULL);
  srand((unsigned)time(NULL));

  STATE currectState = START;
  do {
    mvprintw(50, 0, "STATE: %d", currectState);
    clear_field(&gameInfo);



    switch (currectState) {
      case START:

        if (c == ' ') {
          currectState = SPAWN;
          createNextFigure(&gameInfo);
        }
        break;
      case SPAWN:
        createFigure(&gameInfo);
        currectState = MOVING;
        break;
      case MOVING:
        if (c == KEY_UP) Rotate(&gameInfo);
        if (c == KEY_LEFT) MoveLeft(&gameInfo);
        if (c == KEY_RIGHT) MoveRight(&gameInfo);
        if (c == KEY_DOWN) MoveDown(&gameInfo);

        gettimeofday(&current_time, NULL);
        double dt = (current_time.tv_sec - last_fall_time.tv_sec) +
                    (current_time.tv_usec - last_fall_time.tv_usec) / 1000000.0;

        if (dt >= TIME_FOR_SHIFT) {
          currectState = SHIFTING;
          last_fall_time = current_time;
        }

        break;
      case SHIFTING:
        if (MoveDown(&gameInfo) == 0) {
          currectState = ATTACHING;
        } else {
          currectState = MOVING;
        }
        break;
      case ATTACHING:
        // killines
        
        if (0 /*isEnd*/) {
          currectState = GAME_OVER;
        } else {
          currectState = SPAWN;
        }

        break;
      case GAME_OVER:
        /* code */
        break;

      default:
        break;
    }

    FigureOnBoard(&gameInfo);
    printCurFigureInfo(&gameInfo);
    werase(winGame.winBoard);
    draw_game(gameInfo, winGame);
    box(winGame.winBoard, 0, 0);

    wrefresh(winGame.winBoard);
    c = getch();
    if (c == 27) break;  // Выход при нажатии ESC

  } while (currectState != GAME_OVER);  // 27 - ASCII code for ESC

  endwin();

  return 0;
}
// #include "backend.h"
// #include "frontend.h"
// #include "tetris.h"

// int main() {
//   int c;
//   WinBlocks winGame;
//   SetUp(&winGame);

//   GameInfo_t gameInfo;
//   Constructor(&gameInfo);
//   srand((unsigned)time(NULL));
//   createNextFigure(&gameInfo);
//   createFigure(&gameInfo);
//   Move(&gameInfo, 0, 5);
//   printCurFigureInfo(&gameInfo);

//   do {
//     clear_field(&gameInfo);

//     if (c == KEY_UP)
//       Move(&gameInfo, 0, -1);
//     else if (c == KEY_DOWN)
//       Move(&gameInfo, 0, 1);
//     else if (c == KEY_LEFT)
//       Move(&gameInfo, -1, 0);
//     else if (c == KEY_RIGHT)
//       Move(&gameInfo, 1, 0);
//     FigureOnBoard(&gameInfo);
//     printCurFigureInfo(&gameInfo);
//     werase(winGame.winBoard);
//     draw_game(gameInfo, winGame);
//     box(winGame.winBoard, 0, 0);
//     wrefresh(winGame.winBoard);
//   } while ((c = getch()) != 27);  // 27 - ASCII code for ESC

//   getch();

//   endwin();

//   return 0;
// }