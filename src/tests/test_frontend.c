#include "../backend.h"
#include "../frontend.h"
#include "../tetris.h"
#include "test.h"

START_TEST(test_s21_from_decimal_to_big) {}

Suite* test_frontend(void) {
  Suite* s;
  TCase* tc;

  s = suite_create("Frontend");
  tc = tcase_create("Frontend");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_s21_from_decimal_to_big);

    suite_add_tcase(s, tc);
  }

  return (s);
}