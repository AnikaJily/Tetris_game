#include "../backend.h"
#include "../frontend.h"
#include "../tetris.h"
#include "test.h"

START_TEST(test_create_field) {
  int** field = create_field(BOARD_HEIGHT, BOARD_HEIGHT);
  ck_assert_ptr_nonnull(field);  // Проверяем, что поле не равно NULL

  // Проверяем каждую строку и элемент
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    ck_assert_ptr_nonnull(field[i]);
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      ck_assert_int_eq(field[i][j],
                       0);  // Проверяем, что все элементы инициализированы в 0
    }
  }

  // Освобождаем память
  delete_field(field);
}
END_TEST

START_TEST(test_clear_field) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);

  // Устанавливаем несколько значений в поле
  gameInfo.field[0][0] = 1;
  gameInfo.field[0][1] = 2;
  gameInfo.field[1][0] = 3;
  gameInfo.field[1][1] = 4;

  // Устанавливаем значения, которые должны остаться нетронутыми
  gameInfo.field[0][2] = 8;
  gameInfo.field[1][2] = 8;

  clear_field(&gameInfo);

  // Проверяем, что все значения, кроме тех, что равны 8, установлены в 0
  ck_assert_int_eq(gameInfo.field[0][0], 0);
  ck_assert_int_eq(gameInfo.field[0][1], 0);
  ck_assert_int_eq(gameInfo.field[1][0], 0);
  ck_assert_int_eq(gameInfo.field[1][1], 0);

  ck_assert_int_eq(gameInfo.field[0][2], 8);
  ck_assert_int_eq(gameInfo.field[1][2], 8);

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_create_next_figure) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);

  createNextFigure(&gameInfo);

  // Проверяем, что фигура создана (id не должен быть 0)
  ck_assert_int_ne(gameInfo.next_figure.id, 0);

  // Также можно проверить конкретные фигуры, если знать их ожидаемую
  // конфигурацию Пример: Проверка для фигуры с id == 1
  if (gameInfo.next_figure.id == 1) {
    ck_assert_int_eq(gameInfo.next_figure.x[0], MATRIX_WIDTH / 2);
    ck_assert_int_eq(gameInfo.next_figure.x[1], MATRIX_WIDTH / 2);
    ck_assert_int_eq(gameInfo.next_figure.y[0], -2);
    ck_assert_int_eq(gameInfo.next_figure.y[1], -1);
  }

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_move_left) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);
  createFigure(&gameInfo);

  int initialX[FIGURE_SIZE];
  for (int i = 0; i < FIGURE_SIZE; i++) {
    initialX[i] = gameInfo.cur_figure.x[i];
  }

  MoveLeft(&gameInfo);

  // Проверяем, что фигура переместилась влево
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(gameInfo.cur_figure.x[i], initialX[i] - 1);
  }

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_move_right) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);
  createFigure(&gameInfo);

  int initialX[FIGURE_SIZE];
  for (int i = 0; i < FIGURE_SIZE; i++) {
    initialX[i] = gameInfo.cur_figure.x[i];
  }

  MoveRight(&gameInfo);

  // Проверяем, что фигура переместилась вправо
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(gameInfo.cur_figure.x[i], initialX[i] + 1);
  }

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_is_rotatable) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);

  // Устанавливаем фигуру, которую можно повернуть
  gameInfo.cur_figure.id = 2;  // Пример: Идем к фигуре с ID 2
  gameInfo.cur_figure.x[0] = 1;
  gameInfo.cur_figure.x[1] = 2;
  gameInfo.cur_figure.x[2] = 3;
  gameInfo.cur_figure.x[3] = 4;
  gameInfo.cur_figure.y[0] = 1;
  gameInfo.cur_figure.y[1] = 1;
  gameInfo.cur_figure.y[2] = 1;
  gameInfo.cur_figure.y[3] = 1;
  gameInfo.cur_figure.center_x = 2;
  gameInfo.cur_figure.center_y = 1;

  ck_assert_int_eq(isRotatable(&gameInfo), 1);  // Ожидаем, что поворот возможен

  // Устанавливаем фигуру, которую нельзя повернуть
  gameInfo.cur_figure.id =
      1;  // Пример: Идем к фигуре с ID 1 (если она не может быть повернута)
  ck_assert_int_eq(isRotatable(&gameInfo),
                   0);  // Ожидаем, что поворот невозможен

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_move_down) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);
  createFigure(&gameInfo);

  // Устанавливаем начальные координаты
  int initialY[FIGURE_SIZE];
  for (int i = 0; i < FIGURE_SIZE; i++) {
    initialY[i] = gameInfo.cur_figure.y[i];
  }

  MoveDown(&gameInfo);

  // Проверяем, что фигура переместилась вниз
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(gameInfo.cur_figure.y[i], initialY[i] + 1);
  }

  Destructor(&gameInfo);
}
END_TEST

START_TEST(test_kill_lines) {
  GameInfo_t gameInfo;
  Constructor(&gameInfo);

  // Заполняем поле так, чтобы одна из линий была полной
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    gameInfo.field[MATRIX_HEIGHT - 1][x] = 1;
  }

  int lines_cleared = killLines(&gameInfo);

  // Проверяем, что одна линия была очищена
  ck_assert_int_eq(lines_cleared, 1);

  // Проверяем, что все элементы в очищенной линии теперь равны 0
  for (int x = 0; x < MATRIX_WIDTH; x++) {
    ck_assert_int_eq(gameInfo.field[MATRIX_HEIGHT - 1][x], 0);
  }

  // Проверяем, что линии выше опустились
  for (int y = MATRIX_HEIGHT - 2; y >= 0; y--) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      ck_assert_int_eq(gameInfo.field[y + 1][x], gameInfo.field[y][x]);
    }
  }

  Destructor(&gameInfo);
}
END_TEST

Suite* test_backend(void) {
  Suite* s;
  TCase* tc;

  s = suite_create("Backend");
  tc = tcase_create("Backend");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_create_field);
    tcase_add_test(tc, test_clear_field);
    tcase_add_test(tc, test_create_next_figure);
    tcase_add_test(tc, test_move_left);
    tcase_add_test(tc, test_move_right);

    tcase_add_test(tc, test_is_rotatable);
    tcase_add_test(tc, test_move_down);
    tcase_add_test(tc, test_kill_lines);

    suite_add_tcase(s, tc);
  }

  return (s);
}