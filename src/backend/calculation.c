#include "smart_calc.h"

int get_number(char **src, stack_tt *stack);
int arithmetic_calculate(stack_tt *stack, int operator);
int function_calculate(stack_tt *stack, int operator, char ** src);

int calculation(char *src, double *result) {
  errnum error_code = SUCCESS;
  Lex result_tmp = {0};
  stack_tt operands_stack;
  create_stack(&operands_stack);

  for (; *src && error_code == SUCCESS; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    if (*src == '\0' && error_code == SUCCESS) {
      error_code = SUCCESS;
    } else if (IS_DIGIT(*src) || (*src == 'u' && IS_DIGIT(*(src + 2)))) {
      error_code = get_number(&src, &operands_stack);
    } else if (IS_OPERATOR(*src)) {
      error_code = arithmetic_calculate(&operands_stack, *src);
    } else if (IS_FUNCTION(*src) || (*src == 'u' && IS_FUNCTION(*(src + 2)))) {
      error_code = function_calculate(&operands_stack, *src, &src);
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

int get_number(char **src, stack_tt *stack) {
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

int arithmetic_calculate(stack_tt *stack, int operator) {
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
      if (A.val == 0) {
        error_code = CALC_ERROR;
      } else {
        result.val = B.val / A.val;
      }
      break;
    case 'M':
      if (A.val == 0) {
        error_code = CALC_ERROR;
      } else {
        result.val = B.val - (A.val * floor(B.val / A.val));
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

int function_calculate(stack_tt *stack, int operator, char ** src) {
  errnum error_code = SUCCESS;
  Lex A = {0}, result = {0};
  int unary = 1;
  if (**src == 'u') {
    unary = -1;
    *src += 1;
    while (IS_SPACE(**src)) *src += 1;
    operator=(int) * *src;
  }
  if (pop(stack, &A) == SUCCESS) {
    error_code = SUCCESS;
  } else {
    error_code = CALC_ERROR;
    return error_code;  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
  switch (operator) {
    case 's':  // sin
      result.val = sin(A.val);
      break;
    case 'S':  // asin
      result.val = asin(A.val);
      break;
    case 'c':  // cos
      result.val = cos(A.val);
      break;
    case 'C':  // acos
      result.val = acos(A.val);
      break;
    case 't':  // tan
      result.val = tan(A.val);
      break;
    case 'T':  // atan
      result.val = atan(A.val);
      break;
    case 'Q':  // sqrt
      result.val = sqrt(A.val);
      break;
    case 'l':  // ln
      result.val = log(A.val);
      break;
    case 'L':  // log
      result.val = log10(A.val);
      break;
    default:
      break;
  }
  if (error_code == SUCCESS) {
    result.val *= unary;
    error_code = push(stack, &result);
  }
  return error_code;
}