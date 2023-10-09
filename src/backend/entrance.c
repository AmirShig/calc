#include "smart_calc.h"

int entrance() {
  errnum error_code = SUCCESS;

  // char input[N_MAX + 1] = "-512 - 128 * (125 - (17 + 12 ^ 2))";  // 5120
  // char input[N_MAX + 1] = "105 * ln(15) - 19^3 / 11";
  // char input[N_MAX + 1] = "asin(0.5) + cos(60)"; // ошибка?
  char input[N_MAX + 1] =
      "ln(2.718) * (sin(30) * cos(60) - tan(45)) + (8 - 3) / 5";
  // printf("input: %s\n", input);

  // char input[N_MAX + 1] = {0};
  char result_rpn[N_MAX * 2] = {0};
  double result = 0.0;

  // Считывание  строки и проверка на корректность ввода
  // printf("Введите математическое выражение:\n");
  // if (fgets(input, N_MAX, stdin)) {
  printf("Строка считана успешно!\n");
  printf("INPUT: %s\n", input);

  error_code = validation(input);
  if (error_code == SUCCESS) {
    printf("Строка введена корректно!\n");
  } else {
    printf("Не корректный ввод!\n");
  }
  // } else {
  //   printf("Ошибка считывания строки!\n");
  //   error_code = FAILURE;
  // }

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
    error_code = calculation(result_rpn, &result);
    if (error_code == SUCCESS) {
      printf("SUCCESS!!!\nResult: %lf\n", result);
    } else {
      printf("Calculation FAILED!\nError code: %d\n", error_code);
    }
  }

  return error_code;
}

int main() {
  errnum error_code = SUCCESS;
  error_code = entrance();
  printf("\nWork: %d\n", error_code);
  return 0;
}