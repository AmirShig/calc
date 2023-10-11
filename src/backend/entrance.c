#include "smart_calc.h"

int entrance(char *input, double *result, double x_value) {
  errnum error_code = SUCCESS;
  char result_rpn[N_MAX * 2] = {0};
  double result_tmp = 0.0;

  error_code = validation(input);
  if (error_code == SUCCESS) {
    printf("Строка введена корректно!\n");
  } else {
    printf("Не корректный ввод!\n");
  }

  // Перводим выражение из инфиксной записи в обратную польскую запись
  if (error_code == SUCCESS) {
    error_code = parser_to_rpn(input, result_rpn);
    if (error_code == SUCCESS) {
      printf("RPN: %s\n", result_rpn);
    } else {
      printf("RPN calculate is FAILED!\n");
    }
  }

  // Находим решение получившегося выражения
  if (error_code == SUCCESS) {
    error_code = calculation(result_rpn, &result_tmp, x_value);
  }
  *result = result_tmp;

  // error_code = validation(input);
  // if (error_code == SUCCESS) {
  //   error_code = parser_to_rpn(input, result_rpn);
  // }
  // if (error_code == SUCCESS) {
  //   error_code = calculation(result_rpn, &result_tmp);
  // }

  return error_code;
}

int main() {
  errnum error_code = SUCCESS;
  // if (fgets(input, N_MAX, stdin)) {}
  char input[N_MAX + 1] = "x + 5";
  // char input[N_MAX + 1] = "-512 - 128 * (125 - (17 + 12 ^ 2))";  // 4096
  // char input[N_MAX + 1] = "105 * ln(15) - 19^3 / 11"; // -339.20018343
  // char input[N_MAX + 1] = "asin(0.5) + cos(60)";  // ошибка?
  // char input[N_MAX + 1] = "ln(2.718)";  // 0.99989631572
  // char input[N_MAX + 1] = "sqrt(sin(30) + cos(45)) * (3^2 + ln(2)) / (-2)";
  // // char input[N_MAX + 1] = "sin(30)";  // -0.98803162409 char input[N_MAX +
  // 1] =
  //     "ln(2.718) * (sin(30) * cos(60) - tan(45)) + (8 - 3) / 5";  //
  //     0.32130933014
  // printf("input: %s\n", input);

  // char input[N_MAX + 1] =
  //     "(-((0.0000001 * 7) + 6 * (9 - 2.01) / 8.4 + (0.32 ^ 5)))";

  // char input[N_MAX + 1] = "-(1)";  //
  // (-cos(3)) - (-cos(1)) + 4 / 2 - (sin(1)) * 6.09 / (-tan(2) / acos(-1))
  double result = 0.0, result_exp = 105 + 5;
  double x_value = 105.0;
  // double result_exp = -4.996213;

  // char input[N_MAX + 1] = {0};

  printf("INPUT: %s\n", input);

  error_code = entrance(input, &result, x_value);

  if (error_code == SUCCESS) {
    if (result - result_exp < 1e-6) {
      printf("SUCCESS!!!\nResult: %lf\n", result);
    } else {
      printf("FAILED!!!\nResult: %lf\n", result);
    }
    printf("exp result = %lf\n", result_exp);
  }
  printf("\nWork: %d\n", error_code);
  return 0;
}