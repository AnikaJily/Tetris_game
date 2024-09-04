#include <ncurses.h>  // Добавляем для определения WINDOW

#include "../backend.h"
#include "../frontend.h"
#include "../tetris.h"
#include "test.h"

// START_TEST(test_create_field_small) {
//   int** field = create_field(1, 1);
//   ck_assert_ptr_nonnull(field);
//   // ck_assert_ptr_nonnull(field[0]);
//   // ck_assert_int_eq(field[0][0], 0);
//   delete_field(field);
// }

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

// START_TEST(test_draw_board) {
//   WinBlocks winGame;
//   CreateBoards(0, 0, &winGame);

//   GameInfo_t gameInfo;
//   gameInfo.field = create_field(MATRIX_HEIGHT, MATRIX_WIDTH);

//   // Заполнение поля тестовыми значениями
//   for (int i = 0; i < MATRIX_HEIGHT; i++) {
//     for (int j = 0; j < MATRIX_WIDTH; j++) {
//       gameInfo.field[i][j] = (i + j) % 8 + 1;  // Примерный цвет
//     }
//   }

//   draw_board(gameInfo, winGame);

//   // Проверка содержимого окна может потребовать дополнительного подхода
//   delete_field(gameInfo.field);
// }

// START_TEST(test_draw_next) {
//   WinBlocks winGame;
//   CreateBoards(0, 0, &winGame);

//   GameInfo_t gameInfo;
//   gameInfo.next = create_field(MATRIX_NEXT_HEIGHT, MATRIX_NEXT_WIDTH);

//   // Заполнение следующего блока тестовыми значениями
//   for (int i = 0; i < MATRIX_NEXT_HEIGHT; i++) {
//     for (int j = 0; j < MATRIX_NEXT_WIDTH; j++) {
//       gameInfo.next[i][j] = (i + j) % 8 + 1;  // Примерный цвет
//     }
//   }

//   ck_assert_ptr_nonnull(gameInfo.next);

//   draw_next(gameInfo, winGame);

//   // Проверка содержимого окна может потребовать дополнительного подхода
//   delete_field(gameInfo.next);
// }

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

    suite_add_tcase(s, tc);
  }

  return (s);
}