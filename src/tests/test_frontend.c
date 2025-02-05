#include <ncurses.h>  // Добавляем для определения WINDOW

#include "../inc//frontend.h"
#include "../inc/backend.h"
#include "../tetris.h"
#include "test.h"

START_TEST(test_create_field_large) {
  int** field = create_field(100, 100);
  ck_assert_ptr_nonnull(field);
  for (int i = 0; i < 100; i++) {
    ck_assert_ptr_nonnull(field[i]);
    for (int j = 0; j < 100; j++) {
      ck_assert_int_eq(field[i][j], 0);
    }
  }
  delete_field(field);
}

START_TEST(test_draw_info) {
  WinBlocks winGame;
  CreateBoards(0, 0, &winGame);

  GameInfo_t gameInfo;
  gameInfo.score = 123;
  gameInfo.record = 456;
  gameInfo.level = 2;

  draw_info(gameInfo, winGame);

  // Используем функции проверки содержимого окна
  // Например: Проверить текст на окне winInfo
  // Для реального теста, возможно, потребуется использовать инструменты
  // проверки содержимого окна
}

START_TEST(test_game_over) {
  WINDOW* win = newwin(10, 30, 0, 0);
  game_over(win);

  // Проверьте, что сообщение "GAME OVER!" отображается в правильной позиции
  // Проверка позиции в реальном тесте может потребовать захвата содержимого
  // окна
  delwin(win);
}

START_TEST(test_create_boards) {
  WinBlocks winGame;
  CreateBoards(0, 0, &winGame);

  // Проверяем, что окна были созданы
  ck_assert_ptr_nonnull(winGame.winBoard);
  ck_assert_ptr_nonnull(winGame.winNext);
  ck_assert_ptr_nonnull(winGame.winInfo);
  ck_assert_ptr_nonnull(winGame.winRules);

  delwin(winGame.winBoard);
  delwin(winGame.winNext);
  delwin(winGame.winInfo);
  delwin(winGame.winRules);
}


START_TEST(test_draw_next) {
  WinBlocks winGame;
  GameInfo_t gameInfo;

  // Инициализируем окна и игровую информацию
  CreateBoards(0, 0, &winGame);

  // Здесь мы создаем поле с одним цветным блоком для простоты теста
  gameInfo.field = (int**)malloc(MATRIX_HEIGHT * sizeof(int*));
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    gameInfo.field[i] = (int*)calloc(MATRIX_WIDTH, sizeof(int));
  }
  gameInfo.field[0][0] = 1;  // Устанавливаем один блок с цветом 1 (например)

  // Вызываем функцию, которую тестируем
  draw_next(gameInfo, winGame);

  // Простая проверка - убедиться, что в окно что-то записано
  // Мы не можем проверить точное содержимое без специальных инструментов для
  // ncurses но можем проверить, что окно не пустое
  int ch;
  int count = 0;
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      ch = mvwinch(winGame.winBoard, y, x);
      if (ch != ' ') {  // Если символ не пробел, значит что-то нарисовано
        count++;
        break;  // достаточно найти один символ, чтобы считать тест успешным
      }
    }
    if (count > 0) break;
  }
  ck_assert_int_gt(count, 0);  // Проверяем, что хотя бы один символ был записан

  // Освобождаем память
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);

  delwin(winGame.winBoard);
  delwin(winGame.winNext);
  delwin(winGame.winInfo);
  delwin(winGame.winRules);
}

START_TEST(test_draw_board) {
  WinBlocks winGame;
  GameInfo_t gameInfo;

  // Инициализируем окна и игровую информацию
  CreateBoards(0, 0, &winGame);

  // Здесь мы создаем поле с одним цветным блоком для простоты теста
  gameInfo.field = (int**)malloc(MATRIX_HEIGHT * sizeof(int*));
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    gameInfo.field[i] = (int*)calloc(MATRIX_WIDTH, sizeof(int));
  }
  gameInfo.field[0][0] = 1;  // Устанавливаем один блок с цветом 1 (например)

  // Вызываем функцию, которую тестируем
  draw_board(gameInfo, winGame);

  // Простая проверка - убедиться, что в окно что-то записано
  // Мы не можем проверить точное содержимое без специальных инструментов для
  // ncurses но можем проверить, что окно не пустое
  int ch;
  int count = 0;
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      ch = mvwinch(winGame.winBoard, y, x);
      if (ch != ' ') {  // Если символ не пробел, значит что-то нарисовано
        count++;
        break;  // достаточно найти один символ, чтобы считать тест успешным
      }
    }
    if (count > 0) break;
  }
  ck_assert_int_gt(count, 0);  // Проверяем, что хотя бы один символ был записан

  // Освобождаем память
  for (int i = 0; i < MATRIX_HEIGHT; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);

  delwin(winGame.winBoard);
  delwin(winGame.winNext);
  delwin(winGame.winInfo);
  delwin(winGame.winRules);
}

Suite* test_frontend(void) {
  Suite* s;
  TCase* tc;

  s = suite_create("Frontend");
  tc = tcase_create("Frontend");

  if (s != NULL && tc != NULL) {
    // tcase_add_test(tc, test_create_field_small);
    tcase_add_test(tc, test_create_field_large);
    tcase_add_test(tc, test_draw_info);
    tcase_add_test(tc, test_game_over);
    tcase_add_test(tc, test__over);

    suite_add_tcase(s, tc);
  }

  return (s);
}