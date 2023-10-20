#include "test.h"

START_TEST(DOT_VALID_0) {
  errnum error = 0;
  char mass[N_MAX] = "1.1 -. 1.1";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_1) {
  errnum error = 0;
  char mass[N_MAX] = "1.1 - 1.1";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(DOT_VALID_2) {
  errnum error = 0;
  char mass[N_MAX] = "11.- 1.1";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_3) {
  errnum error = 0;
  char mass[N_MAX] = "11 - 1.1";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(DOT_VALID_4) {
  errnum error = 0;
  char mass[N_MAX] = "11-.11";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_5) {
  errnum error = 0;
  char mass[N_MAX] = "1.1-11.";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_6) {
  errnum error = 0;
  char mass[N_MAX] = "1.1-11";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(DOT_VALID_7) {
  errnum error = 0;
  char mass[N_MAX] = "1..1-11";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_8) {
  errnum error = 0;
  char mass[N_MAX] = "1.1.-1.1";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_9) {
  errnum error = 0;
  char mass[N_MAX] = "11.-1.1";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_10) {
  errnum error = 0;
  char mass[N_MAX] = ".11-11";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_11) {
  errnum error = 0;
  char mass[N_MAX] = ".cos(1)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_12) {
  errnum error = 0;
  char mass[N_MAX] = "acos(1.)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_13) {
  errnum error = 0;
  char mass[N_MAX] = "acos(1.1.)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_14) {
  errnum error = 0;
  char mass[N_MAX] = "acos(1.1-3.3-.)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(DOT_VALID_15) {
  errnum error = 0;
  char mass[N_MAX] = "";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

Suite *Dot_validation(void) {
  Suite *s = suite_create("\033[45m-=DOT VALIDATION=-\033[0m");
  TCase *tc1_1 = tcase_create("SmartCalc validation: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, DOT_VALID_0);
  tcase_add_test(tc1_1, DOT_VALID_1);
  tcase_add_test(tc1_1, DOT_VALID_2);
  tcase_add_test(tc1_1, DOT_VALID_3);
  tcase_add_test(tc1_1, DOT_VALID_4);
  tcase_add_test(tc1_1, DOT_VALID_5);
  tcase_add_test(tc1_1, DOT_VALID_6);
  tcase_add_test(tc1_1, DOT_VALID_7);
  tcase_add_test(tc1_1, DOT_VALID_8);
  tcase_add_test(tc1_1, DOT_VALID_9);
  tcase_add_test(tc1_1, DOT_VALID_10);
  tcase_add_test(tc1_1, DOT_VALID_11);
  tcase_add_test(tc1_1, DOT_VALID_12);
  tcase_add_test(tc1_1, DOT_VALID_13);
  tcase_add_test(tc1_1, DOT_VALID_14);
  tcase_add_test(tc1_1, DOT_VALID_15);

  return s;
}