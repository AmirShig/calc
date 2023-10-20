#include "smart_calc.h"

// Вход: общая сумма кредита, срок, процентная ставка, тип (аннуитетный,
// дифференцированный)
// Выход: ежемесячный платеж, переплата по кредиту, общая выплата

// @param loan_amount Сумма кредита
// @param loan_term Срок кредита
// @param interest_rate Годовая процентная ставка в %
// @param loan_type Тип платежей по кредиту
// @return Структуру, содержащую ежемесячный платеж, переплата по кредиту, общую
// выплату
cred_info credit(double loan_amount, int loan_term, double interest_rate,
                 char loan_type) {
  cred_info args = {0};
  if (loan_type == 'A') {
    annuity(loan_amount, loan_term, interest_rate, &args);
  } else if (loan_type == 'D') {
    differentiated(loan_amount, loan_term, interest_rate, &args);
  }
  return args;
}

void annuity(double loan_amount, int loan_term, double interest_rate,
             cred_info *args) {
  // месячная процентная ставка
  double month_interest_rate = interest_rate / 12.0 / 100.0;

  // рассчет ежемесячного аннуитентного платежа
  args->monthly_payment = (loan_amount * month_interest_rate) /
                          (1 - pow((1 + month_interest_rate), -loan_term));

  // Расчет переплаты по кредиту
  args->total_interest_paid = (args->monthly_payment * loan_term) - loan_amount;

  // Рассчет общей выплаты
  args->total_payment = args->monthly_payment * loan_term;
}

void differentiated(double loan_amount, int loan_term, double interest_rate,
                    cred_info *args) {
  double *diff_month_payments = (double *)calloc(loan_term, sizeof(double));
  if (diff_month_payments != NULL) {
    // Обязательный платеж по кредиту
    double principal_debt_payment = loan_amount / loan_term;
    double debt_remaining = loan_amount;  // Остаток по кредиту
    for (int i = 0; i < loan_term; i++) {
      // Расчет ежемесячного дифференцированного платежа
      diff_month_payments[i] =
          principal_debt_payment +
          (debt_remaining * (interest_rate / 100) * (365.0 / 12.0)) / 365;
      // Расчет общей выплаты
      args->total_payment += diff_month_payments[i];
      debt_remaining -= principal_debt_payment;
    }
    // Получаем платеж за первый и последний месяц
    args->monthly_payment = diff_month_payments[0];
    args->last_monthly_payment = diff_month_payments[loan_term - 1];
    // Расчет переплаты по кредиту
    args->total_interest_paid = (args->total_payment - loan_amount);
    free(diff_month_payments);
  }
}