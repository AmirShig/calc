#include "test.h"

START_TEST(GENERAL_TEST_0) {
  errnum error = 0;
  double result = 0, exp_result = -36.0200007, x_value = 0;
  char string[N_MAX] =
      "13.01 - 1.09 - 6.0 - ((0.0000001 * 7) + 6 * (9 - 2.01))";

  error = entrance(string, &result, x_value);

  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_1) {
  errnum error = 0;
  double exp_result = -4.99621328606, result = 0, x_value = 0;

  char string[N_MAX] =
      "(-((0.0000001 * 7) + 6 * (9 - 2.01) / 8.4 + (0.32 ^ 5)))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_2) {
  errnum error = 0;
  double exp_result = -744.5, result = 0, x_value = 0;

  char string[N_MAX] = "77 mod 4 - ((3 * (3 ^ 6)) - 700) / 24 * 12 - 2";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_3) {
  errnum error = 0;
  double exp_result = -52917.0091791, result = 0, x_value = 0;

  char string[N_MAX] = "(-569.0000987) * (99 - 6)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_4) {
  errnum error = 0;
  double exp_result = 63.52687747, result = 0, x_value = 0;

  char string[N_MAX] = "88 + (2 ^ 2) * (-569.0000987) / (99 - 6)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_5) {
  errnum error = 0;
  double exp_result = -7.0370370, result = 0, x_value = 0;

  char string[N_MAX] = "(-7.0) + (-3 ^ (-3))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_6) {
  errnum error = 0;
  double exp_result = -3.8376598, result = 0, x_value = 0;

  char string[N_MAX] =
      "(-cos(3)) - (-cos(1)) + 4 / 2 - (sin(1))  * 6.09 / (-tan(2) / acos(-1))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_7) {
  errnum error = 0;
  double exp_result = -6794.53374717, result = 0, x_value = 0;

  char string[N_MAX] =
      "(-6696.0009867) + 1 / 4 / 2 / 1.3 * 5.0009 + (-56) + (-sqrt(9.9)) - 99 "
      "+ 1.4 ^ (-6) - 5 + 8 ^ 2";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_8) {
  errnum error = 0;
  double exp_result = 3.5759962, result = 0, x_value = 0;

  char string[N_MAX] =
      "(-cos(3)) - (-cos(1)) + 4 / 2 - (sin(1)) + 1 ^ 2.0000007 * 6.09 / "
      "(-tan(2)) / acos(-1)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_9) {
  errnum error = 0;
  double exp_result = -4.9, result = 0, x_value = 0;

  char string[N_MAX] = "(-1) + (-1) + (-1) - 1.9 - (-1) - 1";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_10) {
  errnum error = 0;
  double exp_result = 0.6663667, result = 0, x_value = 0;

  char string[N_MAX] = "cos(sin(1))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_11) {
  errnum error = 0;
  double exp_result = 4096, result = 0, x_value = 0;

  char string[N_MAX] = "8 ^ 2 ^ 2";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_12) {
  errnum error = 0;
  double exp_result = 8, result = 0, x_value = 0;

  char string[N_MAX] = "(+8-(-9))-(+9)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_13) {
  errnum error = 0;
  double exp_result = -1, result = 0, x_value = 0;

  char string[N_MAX] = "(+8-9)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_14) {
  errnum error = 0;
  double exp_result = -13.0700007, result = 0, x_value = 0;

  char string[N_MAX] =
      "3 * (8.0987 / 8.0987) - 65.02 + 13.01 - 6.0 - (0.0000001 * 7) + 6 * (9 "
      "- 2.01)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_15) {
  errnum error = 0;
  double exp_result = 4, result = 0, x_value = 0;

  char string[N_MAX] = "(-2)^2";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_16) {
  errnum error = 0;
  double exp_result = -4, result = 0, x_value = 0;

  char string[N_MAX] = "(-2)-2";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_17) {  // asin
  errnum error = 0;
  double exp_result = (asin(0.5) * atan(0.75)), result = 0, x_value = 0;

  char string[N_MAX] = "(asin(0.5) * atan(0.75))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_18) {  // asin + log
  errnum error = 0;
  double exp_result = (-log10(45) + asin(0.5)), result = 0, x_value = 0;

  char string[N_MAX] = "(-log(45) + asin(0.5))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_19) {  // asin + ln
  errnum error = 0;
  double exp_result = (-log(15) + asin(0.5)), result = 0, x_value = 0;

  char string[N_MAX] = "(-ln(15) + asin(0.5))";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

START_TEST(GENERAL_TEST_20) {  // asin + ln
  errnum error = 0;
  double exp_result =
             (9132165498651321654984621321654984651321684984351.21654 / 2),
         result = 0, x_value = 0;

  char string[N_MAX] =
      "(9132165498651321654984621321654984651321684984351.21654 / 2)";

  error = entrance(string, &result, x_value);
  ck_assert_int_eq(SUCCESS, error);
  ck_assert_double_eq_tol(result, exp_result, 1e-7);
}
END_TEST

Suite *General_test(void) {
  Suite *s = suite_create("\033[45m-=GENERAL TEST=-\033[0m");
  TCase *tc1_1 = tcase_create("Gengeral test: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, GENERAL_TEST_0);
  tcase_add_test(tc1_1, GENERAL_TEST_1);
  tcase_add_test(tc1_1, GENERAL_TEST_2);
  tcase_add_test(tc1_1, GENERAL_TEST_3);
  tcase_add_test(tc1_1, GENERAL_TEST_4);
  tcase_add_test(tc1_1, GENERAL_TEST_5);
  tcase_add_test(tc1_1, GENERAL_TEST_6);
  tcase_add_test(tc1_1, GENERAL_TEST_7);
  tcase_add_test(tc1_1, GENERAL_TEST_8);
  tcase_add_test(tc1_1, GENERAL_TEST_9);
  tcase_add_test(tc1_1, GENERAL_TEST_10);
  tcase_add_test(tc1_1, GENERAL_TEST_11);
  tcase_add_test(tc1_1, GENERAL_TEST_12);
  tcase_add_test(tc1_1, GENERAL_TEST_13);
  tcase_add_test(tc1_1, GENERAL_TEST_14);
  tcase_add_test(tc1_1, GENERAL_TEST_15);
  tcase_add_test(tc1_1, GENERAL_TEST_16);
  tcase_add_test(tc1_1, GENERAL_TEST_17);
  tcase_add_test(tc1_1, GENERAL_TEST_18);
  tcase_add_test(tc1_1, GENERAL_TEST_19);
  tcase_add_test(tc1_1, GENERAL_TEST_20);

  return s;
}
