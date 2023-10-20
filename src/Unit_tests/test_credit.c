#include "test.h"

START_TEST(Credit_0) {
  cred_info result = {0};
  cred_info exp = {34604493.39, 6541959.74, 1782197197.67, 2571653320.67};
  double loan_amount = 789456123;
  int loan_term = 125;
  double interest_rate = 43;
  char loan_type = 'D';
  result = credit(loan_amount, loan_term, interest_rate, loan_type);
  ck_assert_double_eq_tol(result.monthly_payment, exp.monthly_payment, 1e-2);
  ck_assert_double_eq_tol(result.last_monthly_payment, exp.last_monthly_payment,
                          1e-2);
  ck_assert_double_eq_tol(result.total_interest_paid, exp.total_interest_paid,
                          1e-2);
  ck_assert_double_eq_tol(result.total_payment, exp.total_payment, 1e-2);
}
END_TEST

START_TEST(Credit_1) {
  cred_info result = {0};
  cred_info exp = {12506333.81, 1341105.67, 3344004561.01, 4133460684.01};
  double loan_amount = 789456123;
  int loan_term = 597;
  double interest_rate = 17;
  char loan_type = 'D';
  result = credit(loan_amount, loan_term, interest_rate, loan_type);
  ck_assert_double_eq_tol(result.monthly_payment, exp.monthly_payment, 1e-2);
  ck_assert_double_eq_tol(result.last_monthly_payment, exp.last_monthly_payment,
                          1e-2);
  ck_assert_double_eq_tol(result.total_interest_paid, exp.total_interest_paid,
                          1e-2);
  ck_assert_double_eq_tol(result.total_payment, exp.total_payment, 1e-2);
}
END_TEST

START_TEST(Credit_2) {
  cred_info result = {0};
  cred_info exp = {28640194.96, 0.00, 2790568247.00, 3580024370.00};
  double loan_amount = 789456123;
  int loan_term = 125;
  double interest_rate = 43;
  char loan_type = 'A';
  result = credit(loan_amount, loan_term, interest_rate, loan_type);
  ck_assert_double_eq_tol(result.monthly_payment, exp.monthly_payment, 1e1);
  ck_assert_double_eq_tol(result.total_interest_paid, exp.total_interest_paid,
                          1e1);
  ck_assert_double_eq_tol(result.total_payment, exp.total_payment, 1e1);
}
END_TEST

START_TEST(Credit_3) {
  cred_info result = {0};
  cred_info exp = {11186481.87, 0.00, 5888873553.39, 6678329676.39};
  double loan_amount = 789456123;
  int loan_term = 597;
  double interest_rate = 17;
  char loan_type = 'A';
  result = credit(loan_amount, loan_term, interest_rate, loan_type);
  ck_assert_double_eq_tol(result.monthly_payment, exp.monthly_payment, 1e1);
  ck_assert_double_eq_tol(result.total_interest_paid, exp.total_interest_paid,
                          1e1);
  ck_assert_double_eq_tol(result.total_payment, exp.total_payment, 1e1);
}
END_TEST

Suite *Credit(void) {
  Suite *s = suite_create("\033[45m-=CREDIT_CALC=-\033[0m");
  TCase *tc1_1 = tcase_create("SmartCalc validation: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, Credit_0);
  tcase_add_test(tc1_1, Credit_1);
  tcase_add_test(tc1_1, Credit_2);
  tcase_add_test(tc1_1, Credit_3);

  return s;
}