#include "test.h"
#include "../tetris.h"
#include "../backend.h"
#include "../frontend.h"

START_TEST(test_create_field) {
    int **field = create_field(BOARD_HEIGHT, BOARD_HEIGHT);
    ck_assert_ptr_nonnull(field);  // Проверяем, что поле не равно NULL

    // Проверяем каждую строку и элемент
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        ck_assert_ptr_nonnull(field[i]);
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            ck_assert_int_eq(field[i][j], 0); // Проверяем, что все элементы инициализированы в 0
        }
    }

    // Освобождаем память
    delete_field(field);
}
END_TEST


Suite* test_backend(void) {
  Suite* s;
  TCase* tc;

  s = suite_create("Backend");
  tc = tcase_create("Backend");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_create_field);

    suite_add_tcase(s, tc);
  }

  return (s);
}