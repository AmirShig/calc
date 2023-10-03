#include "smart_calc.h"

int entrance() {
  int error_code = SUCCESS;
  char input[N_MAX + 1];
  Node input_stack = {0};
  Node reverse = {0};
  Node RPN = {0};
  Node operators_stack = {0};

  // Считывание  строки и проверка на корректность ввода
  if (fgets(input, N_MAX, stdin)) {
    error_code = validation(input);
  } else {
    error_code = FAILURE;
  }

  // Записываем в стек "как есть" строку
  if (error_code == SUCCESS) {
    parcer_to_stack(input, &input_stack);
  }

  return error_code;
}

int main() {
  int error_code = SUCCESS;
  error_code = entrance();
  if (error_code == SUCCESS)
    printf("SUCCES! The expression is correct!\n");
  else
    printf("FAIL! The epression is INCORRECT!\n");
  return 0;
}