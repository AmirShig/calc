#include "smart_calc.h"

int parcer_to_stack(const char *src, stack_t stack) {
  errnum error_code = SUCCESS;
  for (; *src && error_code == SUCCESS; src++) {
    if (IS_DIGIT(src)) {
    }
    switch (*src) {
      case '(':
        /* code */
        break;

      default:
        break;
    }
  }
  return error_code;
}

int get_number(char *src, stack_t *stack) {
  errnum error_code = SUCCESS;
  char *endptr = NULL;
  double tmp = strtod(src, endptr);
  if (endptr == src) {
    error_code = INCORRECT_INPUT;
  } else {
    Lex lex_tmp = {0};
    lex_tmp.val = tmp;
    lex_tmp.priority = 1;
    lex_tmp.val_type = DIGIT;
    error_code = push(stack, lex_tmp);
  }
}