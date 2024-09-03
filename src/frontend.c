#include "frontend.h"

#include "tetris.h"

void CreateBoards(int y, int x, WinBlocks *winGame) {
  winGame->winBoard = newwin(BOARD_HEIGHT, BOARD_WIDTH, y, x);
  winGame->winNext = newwin(NEXT_HEIGHT, NEXT_WIDTH, y, x + BOARD_WIDTH + 1);
  winGame->winInfo =
      newwin(INFO_HEIGHT, INFO_WIDTH, y + NEXT_HEIGHT, x + BOARD_WIDTH + 1);
  winGame->winRules = newwin(RULES_HEIGHT, 37, y + BOARD_HEIGHT, x);

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
}

void draw_info(GameInfo_t gameInfo, WinBlocks winGame) {
  mvwprintw(winGame.winInfo, 1, 2, "SCORE: ");
  mvwprintw(winGame.winInfo, 3, 2, "%d", gameInfo.score);

  mvwprintw(winGame.winInfo, 5, 2, "RECORD: ");
  mvwprintw(winGame.winInfo, 7, 2, "%d", gameInfo.record);

  mvwprintw(winGame.winInfo, 9, 2, "LEVEL: ");
  mvwprintw(winGame.winInfo, 11, 2, "%d", gameInfo.level);
  wrefresh(winGame.winInfo);
}

void SetUp(WinBlocks *winGame) {
  int y = 0;
  int x = 0;
  int cols, rows;
  initscr();
  start_color();
  init_color(COLOR_BLACK, 100, 100, 100);
  init_color(COLOR_ORANGE, 200, 250, 100);
  init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_ORANGE);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);
  init_pair(7, COLOR_BLACK, COLOR_CYAN);
  init_pair(8, COLOR_BLACK, COLOR_RED);
  keypad(stdscr, TRUE);  // Включаем обработку функциональных клавиш

  noecho();     // don't display input
  curs_set(0);  // hide cursor
  timeout(15);
  getmaxyx(stdscr, rows, cols);

  CreateBoards(x, y, winGame);
}

void game_over(WINDOW *win) {
  mvwprintw(win, BOARD_HEIGHT / 2 - 1, (BOARD_WIDTH / 2) - 5, "GAME OVER!");
  wrefresh(win);
  napms(3000);  // Добавьте задержку на 3 секунды, чтобы сообщение
                // оставалось видимым
}

void draw_game(GameInfo_t gameInfo, WinBlocks winGame) {
  draw_board(gameInfo, winGame);
  draw_next(gameInfo, winGame);
  draw_info(gameInfo, winGame);
}

void draw_board(GameInfo_t gameInfo, WinBlocks winGame) {
  // Определите отступы для центрирования

  int vertical_offset = (22 - MATRIX_HEIGHT) / 2;
  int horizontal_offset = (22 - MATRIX_WIDTH * 2) / 2;

  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    for (int j = 0; j < MATRIX_WIDTH; j++) {
      // Получаем цвет из матрицы
      int color = gameInfo.field[i][j] % 100;

      // Устанавливаем цвет
      wattron(winGame.winBoard, COLOR_PAIR(color));

      // Отрисовываем блок
      mvwprintw(winGame.winBoard, vertical_offset + i,
                horizontal_offset + j * 2, "  ");

      // Отключаем цвет
      wattroff(winGame.winBoard, COLOR_PAIR(color));
    }
    wprintw(winGame.winBoard, "\n");
  }

  // Обновляем окно
  wrefresh(winGame.winBoard);
}

void draw_next(GameInfo_t gameInfo, WinBlocks winGame) {
  werase(winGame.winNext);
  box(winGame.winNext, 0, 0);

  for (int i = 0; i < MATRIX_NEXT_HEIGHT; i++) {
    for (int j = 0; j < MATRIX_NEXT_WIDTH; j++) {
      int color = gameInfo.next[i][j];
      if (color != 0) {
        wattron(winGame.winNext, COLOR_PAIR(color));
        mvwprintw(winGame.winNext, i + 1, j * 2 + 1, "  ");
        wattroff(winGame.winNext, COLOR_PAIR(color));
      }
    }
  }
  wrefresh(winGame.winNext);
}