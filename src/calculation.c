#include "smart_calc.h"

int get_number(char **src, stack_t *stack);
int arithmetic_calculate(stack_t *stack, int operator);
int function_calculate(stack_t *stack, int operator);

int calculation(char *src, double *result) {
  errnum error_code = SUCCESS;
  // Position status = START_POS;
  Lex result_tmp = {0};
  stack_t operands_stack;
  create_stack(&operands_stack);

  for (; *src && error_code == SUCCESS; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    if (*src == '\0' && error_code == SUCCESS) {
      error_code = SUCCESS;
    } else if (IS_DIGIT(*src) || *src == 'u') {
      error_code = get_number(&src, &operands_stack);
    } else if (IS_OPERATOR(*src)) {
      error_code = arithmetic_calculate(&operands_stack, *src);
    } else if (IS_FUNCTION(*src)) {
      error_code = function_calculate(&operands_stack, *src);
    }
  }
  if (error_code == SUCCESS) {
    if (pop(&operands_stack, &result_tmp) == SUCCESS)
      *result = result_tmp.val;
    else
      error_code = FAILURE;
  }

  return error_code;
}

int get_number(char **src, stack_t *stack) {
  errnum error_code = SUCCESS;
  char *endptr = NULL;
  int unary = 1;
  if (**src == 'u') {
    unary = -1;
    *src += 1;
  }
  double number = strtod(*src, &endptr);
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

int arithmetic_calculate(stack_t *stack, int operator) {
  errnum error_code = SUCCESS;
  // double A = 0, B = 0;
  Lex A = {0}, B = {0}, result = {0};

  if (pop(stack, &A) == SUCCESS && pop(stack, &B) == SUCCESS) {
    error_code = SUCCESS;
  } else {
    error_code = CALC_ERROR;
    return error_code;  ///////////////////////////////////////////////////// !
  }

  switch (operator) {
    case '+':
      result.val = A.val + B.val;
      break;
    case '-':
      result.val = B.val - A.val;
      break;
    case '*':
      result.val = A.val * B.val;
      break;
    case '/':
      if (B.val == 0) {
        error_code = CALC_ERROR;
      } else {
        result.val = A.val / B.val;
      }
      break;
    case '^':
      result.val = pow(B.val, A.val);
      break;
  }

  if (error_code == SUCCESS) {
    error_code = push(stack, &result);
  }

  return error_code;
}

int function_calculate(stack_t *stack, int operator) {
  errnum error_code = FAILURE;
  operator= operator;
  stack->top = stack->top;
  printf(
      "Функцию для обработки тригонметрии пока не завезли =(\nПопробуйте "
      "позже\n");
  return error_code;
}