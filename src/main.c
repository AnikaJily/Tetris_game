#include <sys/time.h>
#include <time.h>

#include "backend.h"
#include "frontend.h"
#include "tetris.h"

typedef enum {
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAME_OVER,
  PAUSE
} STATE;

int main() {
  int c = 0;
  int lines_cleared = 0;
  WinBlocks winGame;
  SetUp(&winGame);
  GameInfo_t gameInfo;
  Constructor(&gameInfo);
  struct timeval last_fall_time, current_time;
  gettimeofday(&last_fall_time, NULL);
  srand((unsigned)time(NULL));

  STATE currectState = START;
  do {
    // mvprintw(50, 0, "STATE: %d", currectState);
    clear_field(&gameInfo);

    switch (currectState) {
      case START:

        if (c == ' ') {
          currectState = SPAWN;
        }
        break;
      case SPAWN:
        FixOnBoard(&gameInfo);
        createFigure(&gameInfo);
        currectState = MOVING;
        break;
      case MOVING:
        if (c == KEY_UP) Rotate(&gameInfo);
        if (c == KEY_LEFT) MoveLeft(&gameInfo);
        if (c == KEY_RIGHT) MoveRight(&gameInfo);
        if (c == KEY_DOWN) MoveDown(&gameInfo);
        if (c == 'q') currectState = GAME_OVER;
        if (c == 'p') currectState = PAUSE;

        gettimeofday(&current_time, NULL);
        double dt = (current_time.tv_sec - last_fall_time.tv_sec) +
                    (current_time.tv_usec - last_fall_time.tv_usec) / 1000000.0;

        if (dt >= TIME_FOR_SHIFT / (double)gameInfo.speed) {
          last_fall_time = current_time;
          currectState = SHIFTING;
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
        FixOnBoard(&gameInfo);
        lines_cleared = killLines(&gameInfo);

        if (lines_cleared > 0) {
          if (gameInfo.score / 600 > 10)
            gameInfo.level = 10;
          else
            gameInfo.level = gameInfo.score / 600 + 1;

          gameInfo.speed = gameInfo.level;
        }

        if (IsUp(&gameInfo)) {
          currectState = GAME_OVER;
        } else {
          currectState = SPAWN;
        }

        break;
      case GAME_OVER:
        game_over(winGame.winBoard);
        if (gameInfo.score > gameInfo.record) {
          gameInfo.record = gameInfo.score;
          save_record("record.txt",
                      gameInfo.record);  // Сохранение рекорда в файл
        }
        break;
      case PAUSE:
        if (c == 'p') {
          currectState = MOVING;
        }
        break;

      default:
        break;
    }

    FigureOnBoard(&gameInfo);
    // printCurFigureInfo(&gameInfo);
    werase(winGame.winBoard);
    draw_game(gameInfo, winGame);
    box(winGame.winBoard, 0, 0);

    wrefresh(winGame.winBoard);
    c = getch();
    if (c == 'q') break;  // Выход при нажатии ESC

  } while (1);  // 27 - ASCII code for ESC

  Destructor(&gameInfo);

  endwin();

  return 0;
}
