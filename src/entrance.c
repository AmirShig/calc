#include "smart_calc.h"

int main() {
  int error_code = SUCCESS;
  char input[N_MAX + 1];
  list input_stack = {0};
  list reverse = {0};
  list RPN = {0};

  // Считывание  строки и проверка на корректность ввода
  if (fgets(input, N_MAX, stdin)) {
    error_code = validation(input);

    if (error_code == SUCCESS)
      printf("SUCCES! The expression is correct!\n");
    else
      printf("FAIL! The epression is INCORRECT!\n");
  } else {
    error_code = FAILURE;
  }

  // Записываем в стек "как есть" строку
  if (error_code == SUCCESS) {
        parcer_to_stack(input, &input_stack);
  }

  return 0;
}