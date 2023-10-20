#include "test.h"

START_TEST(WHOLE_VALID_0) {
  errnum error = 0;
  char mass[N_MAX] = "11-";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_1) {
  errnum error = 0;
  char mass[N_MAX] = "(--1+1)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_2) {
  errnum error = 0;
  char mass[N_MAX] = "1-1+9*((-1)+(-cos(1-0.5)))";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_3) {
  errnum error = 0;
  char mass[N_MAX] = "1--1";
  error = validation(mass);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(WHOLE_VALID_4) {
  errnum error = 0;
  char mass[N_MAX] = "1-1-";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_5) {
  errnum error = 0;
  char mass[N_MAX] = "(-11)-+";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_6) {
  errnum error = 0;
  char mass[N_MAX] = "(11)/(cos(7+))";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_7) {
  errnum error = 0;
  char mass[N_MAX] = "11^2-";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_8) {
  errnum error = 0;
  char mass[N_MAX] = "11^^2";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_9) {
  errnum error = 0;
  char mass[N_MAX] = "11^(^2)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_10) {
  errnum error = 0;
  char mass[N_MAX] = "11^(-^2)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_11) {
  errnum error = 0;
  char mass[N_MAX] = "11^(2mod)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_12) {
  errnum error = 0;
  char mass[N_MAX] = "1mod-1";
  error = validation(mass);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(WHOLE_VALID_13) {
  errnum error = 0;
  char mass[N_MAX] = "cos(1)cos(1)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_14) {
  errnum error = 0;
  char mass[N_MAX] = "1mod2mod";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_15) {
  errnum error = 0;
  char mass[N_MAX] = "cos(1)+cos(1)modtan(1)-acos(-1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_16) {
  errnum error = 0;
  char mass[N_MAX] = "1-1+9(-1+(-cos(1-)))";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_17) {
  errnum error = 0;
  char mass[N_MAX] = "1^-1";
  error = validation(mass);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(WHOLE_VALID_18) {
  errnum error = 0;
  char mass[N_MAX] = "1-mod2mod";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_19) {
  errnum error = 0;
  char mass[N_MAX] = "-(-1)+tan(1)";
  error = validation(mass);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(WHOLE_VALID_20) {
  errnum error = 0;
  char mass[N_MAX] = "5000.0000-(-1)+tan(1)^2/(-2)*1+398mod3mod2";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_21) {
  errnum error = 0;
  char mass[N_MAX] = "cos(1)^sqrt(1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_22) {
  errnum error = 0;
  char mass[N_MAX] = "acos(1)ln(1)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_23) {
  errnum error = 0;
  char mass[N_MAX] = "acos(1)modln(1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_24) {
  errnum error = 0;
  char mass[N_MAX] = "398mod3mod2mod";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_25) {
  errnum error = 0;
  char mass[N_MAX] = "mod";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_26) {
  errnum error = 0;
  char mass[N_MAX] = "cos(1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_27) {
  errnum error = 0;
  char mass[N_MAX] = "cos(3)mod1";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_28) {
  errnum error = 0;
  char mass[N_MAX] = "";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_29) {
  errnum error = 0;
  char mass[N_MAX] = "cos(3)mod(-1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

// validation ALL

START_TEST(WHOLE_VALID_30) {
  errnum error = 0;
  char mass[N_MAX] = "sin(1)-(-2*x)/x-(-1)mod(x^(-2))";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_31) {
  errnum error = 0;
  char mass[N_MAX] = "x";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_32) {
  errnum error = 0;
  char mass[N_MAX] = "x+x";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_33) {
  errnum error = 0;
  char mass[N_MAX] = "x^(-1)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_34) {
  errnum error = 0;
  char mass[N_MAX] = "(-3.00009mod2modx)^xmodacos(x)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_35) {
  errnum error = 0;
  char mass[N_MAX] = "9*x";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_36) {
  errnum error = 0;
  char mass[N_MAX] = "x^x";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_37) {
  errnum error = 0;
  char mass[N_MAX] = "x^xmodx*(-2)modx";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_38) {
  errnum error = 0;
  char mass[N_MAX] = "asin(1)^xmodx*(-2)modx";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_39) {
  errnum error = 0;
  char mass[N_MAX] = "atan(1)^log(2)modx-ln(10)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_40) {
  errnum error = 0;
  char mass[N_MAX] = "sin(cos(tan(x)))";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_41) {
  errnum error = 0;
  char mass[N_MAX] = "4(4)-(5)";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

START_TEST(WHOLE_VALID_42) {
  errnum error = 0;
  char mass[N_MAX] = "(x^2)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_43) {
  errnum error = 0;
  char mass[N_MAX] = "(x)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(WHOLE_VALID_44) {
  errnum error = 0;
  char mass[N_MAX] = "(-x^2)";
  error = validation(mass);
  ck_assert_int_eq(0, error);
}
END_TEST

// 256 symbos
START_TEST(WHOLE_VALID_45) {
  errnum error = 0;
  char mass[N_MAX * 2] =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1111111111111111111111111111111111111111";
  error = validation(mass);
  ck_assert_int_eq(INCORRECT_INPUT, error);
}
END_TEST

Suite *Whole_validation(void) {
  Suite *s = suite_create("\033[45m-=WHOLE VALIDATION=-\033[0m");
  TCase *tc1_1 = tcase_create("WHOLE VALIDATION: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, WHOLE_VALID_0);
  tcase_add_test(tc1_1, WHOLE_VALID_1);
  tcase_add_test(tc1_1, WHOLE_VALID_2);
  tcase_add_test(tc1_1, WHOLE_VALID_3);
  tcase_add_test(tc1_1, WHOLE_VALID_4);
  tcase_add_test(tc1_1, WHOLE_VALID_5);
  tcase_add_test(tc1_1, WHOLE_VALID_6);
  tcase_add_test(tc1_1, WHOLE_VALID_7);
  tcase_add_test(tc1_1, WHOLE_VALID_8);
  tcase_add_test(tc1_1, WHOLE_VALID_9);
  tcase_add_test(tc1_1, WHOLE_VALID_10);
  tcase_add_test(tc1_1, WHOLE_VALID_11);
  tcase_add_test(tc1_1, WHOLE_VALID_12);
  tcase_add_test(tc1_1, WHOLE_VALID_13);
  tcase_add_test(tc1_1, WHOLE_VALID_14);
  tcase_add_test(tc1_1, WHOLE_VALID_15);
  tcase_add_test(tc1_1, WHOLE_VALID_16);
  tcase_add_test(tc1_1, WHOLE_VALID_17);
  tcase_add_test(tc1_1, WHOLE_VALID_18);
  tcase_add_test(tc1_1, WHOLE_VALID_19);
  tcase_add_test(tc1_1, WHOLE_VALID_20);
  tcase_add_test(tc1_1, WHOLE_VALID_21);
  tcase_add_test(tc1_1, WHOLE_VALID_22);
  tcase_add_test(tc1_1, WHOLE_VALID_23);
  tcase_add_test(tc1_1, WHOLE_VALID_24);
  tcase_add_test(tc1_1, WHOLE_VALID_25);
  tcase_add_test(tc1_1, WHOLE_VALID_26);
  tcase_add_test(tc1_1, WHOLE_VALID_27);
  tcase_add_test(tc1_1, WHOLE_VALID_28);
  tcase_add_test(tc1_1, WHOLE_VALID_29);
  tcase_add_test(tc1_1, WHOLE_VALID_30);
  tcase_add_test(tc1_1, WHOLE_VALID_31);
  tcase_add_test(tc1_1, WHOLE_VALID_32);
  tcase_add_test(tc1_1, WHOLE_VALID_33);
  tcase_add_test(tc1_1, WHOLE_VALID_34);
  tcase_add_test(tc1_1, WHOLE_VALID_35);
  tcase_add_test(tc1_1, WHOLE_VALID_36);
  tcase_add_test(tc1_1, WHOLE_VALID_37);
  tcase_add_test(tc1_1, WHOLE_VALID_38);
  tcase_add_test(tc1_1, WHOLE_VALID_39);
  tcase_add_test(tc1_1, WHOLE_VALID_40);
  tcase_add_test(tc1_1, WHOLE_VALID_41);
  tcase_add_test(tc1_1, WHOLE_VALID_42);
  tcase_add_test(tc1_1, WHOLE_VALID_43);
  tcase_add_test(tc1_1, WHOLE_VALID_44);
  tcase_add_test(tc1_1, WHOLE_VALID_45);

  return s;
}