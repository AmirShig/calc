#include "smart_calc.h"

int get_number(char **src, stack_t *stack);

int calculation(char *src, double *result) {
  errnum error_code = SUCCESS;
  Position status = START_POS;
  stack_t operands_stack;
  create_stack(&operands_stack);

  for (; *src && error_code == SUCCESS; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    if (IS_DIGIT(*src) || *src == 'u') {
      error_code = get_number(&src, &operands_stack);
    } else {
      switch (*src) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          arithmetic_calculate();
          break;

        default:
          break;
      }
    }
  }

  return error_code;
}

int get_number(char **src, stack_t *stack) {
  errnum error_code = SUCCESS;
  char *endptr = NULL;
  int unary = 1;
  if (**src == 'u') {
    unary = -1;
    *src++;
  }
  double number = strtod(*src, endptr);
  if (endptr == *src) {  // число не обнаружено
    printf("Error of read the number\n");
    error_code = INCORRECT_INPUT;
  } else {
    *src = endptr;
    Lex lex_tmp = {0};
    lex_tmp.val = number * unary;
    error_code = push(stack, &lex_tmp);
  }
  return error_code;
}

int arithmetic_calculate(stack_t *stack, int operator, double * result) {
  errnum error_code = SUCCESS;

  return error_code;
}

int function_calculate(double A, int function, double *result) {
  errnum error_code = SUCCESS;

  return error_code;
}