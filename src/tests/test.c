#include "test.h"

static int run_test_suite(Suite *test_suite) {
  SRunner *sr = srunner_create(test_suite);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? SUCCESS : FAILURE;
}

int main(void) {
  int failed = 0;

  Suite *suite_array[] = {test_frontend(), test_backend()};

  for (int i = 0; i < (int)(sizeof(suite_array) / sizeof(suite_array[0])); i++)

  {
    failed += run_test_suite(suite_array[i]);
  }

  return (failed == 0) ? SUCCESS : FAILURE;
}