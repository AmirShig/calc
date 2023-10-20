#include "smart_calc.h"

int calculation(char *src, double *result, double x_value) {
  errnum error_code = SUCCESS;
  Lex result_tmp = {0};
  stack_tt operands_stack;
  create_stack(&operands_stack);

  for (; *src && error_code == SUCCESS; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    if (*src == '\0' && error_code == SUCCESS) {
      error_code = SUCCESS;
    } else if (IS_DIGIT(*src) || *src == 'x' ||
               (*src == 'u' && *(src + 1) == 'x') ||
               (*src == 'u' && IS_DIGIT(*(src + 1)))) {
      error_code = get_number(&src, &operands_stack, x_value);
    } else if (IS_OPERATOR(*src)) {
      error_code = arithmetic_calculate(&operands_stack, *src);
    } else if (IS_FUNCTION(*src) || (*src == 'u' && IS_FUNCTION(*(src + 1)))) {
      error_code = function_calculate(&operands_stack, *src, &src);
    }
  }
  if (error_code == SUCCESS) {
    if (pop(&operands_stack, &result_tmp) == SUCCESS) {
      *result = result_tmp.val;
    } else {
      error_code = FAILURE;
    }
  }
  return error_code;
}

int get_number(char **src, stack_tt *stack, double x_value) {
  errnum error_code = SUCCESS;
  double number = 0.0;
  char *endptr = NULL;
  int unary = 1;
  if (**src == 'u') {
    unary = -1;
    *src += 1;
  }
  if (**src == 'x') {
    number = x_value;
  } else {
    number = strtod(*src, &endptr);
    if (endptr == *src) {  // число не обнаружено
      error_code = INCORRECT_INPUT;
    } else {
      *src = endptr;
    }
  }
  if (error_code == SUCCESS) {
    Lex lex_tmp = {0};
    lex_tmp.val = number * unary;
    error_code = push(stack, &lex_tmp);
  }
  return error_code;
}

int arithmetic_calculate(stack_tt *stack, int oper) {
  errnum error_code = SUCCESS;
  Lex A = {0}, B = {0}, result = {0};

  if (pop(stack, &A) == SUCCESS && pop(stack, &B) == SUCCESS) {
    if (oper == '+') {
      result.val = A.val + B.val;
    } else if (oper == '-') {
      result.val = B.val - A.val;
    } else if (oper == '*') {
      result.val = A.val * B.val;
    } else if (oper == '/') {
      if (A.val == 0) {
        error_code = CALC_ERROR;
      } else {
        result.val = B.val / A.val;
      }
    } else if (oper == 'M') {
      if (A.val == 0) {
        error_code = CALC_ERROR;
      } else {
        result.val = B.val - (A.val * floor(B.val / A.val));
      }
    } else if (oper == '^') {
      result.val = pow(B.val, A.val);
    }
  } else {
    error_code = CALC_ERROR;
  }

  if (error_code == SUCCESS) {
    error_code = push(stack, &result);
  }

  return error_code;
}

int function_calculate(stack_tt *stack, int oper, char **src) {
  errnum error_code = SUCCESS;
  Lex A = {0}, result = {0};
  int unary = 1;
  if (**src == 'u') {
    unary = -1;
    *src += 1;
    while (IS_SPACE(**src)) *src += 1;
    oper = (int)**src;
  }
  if (pop(stack, &A) == SUCCESS) {
    error_code = SUCCESS;
    if (oper == 's') {
      result.val = sin(A.val);
    } else if (oper == 'S') {
      result.val = asin(A.val);
    } else if (oper == 'c') {
      result.val = cos(A.val);
    } else if (oper == 'C') {
      result.val = acos(A.val);
    } else if (oper == 't') {
      result.val = tan(A.val);
    } else if (oper == 'T') {
      result.val = atan(A.val);
    } else if (oper == 'Q') {
      if (A.val < 0)
        error_code = CALC_ERROR;
      else
        result.val = sqrt(A.val);
    } else if (oper == 'l') {
      result.val = log(A.val);
    } else if (oper == 'L') {
      result.val = log10(A.val);
    }
  } else {
    error_code = CALC_ERROR;
  }

  if (error_code == SUCCESS) {
    result.val *= unary;
    error_code = push(stack, &result);
  }
  return error_code;
}