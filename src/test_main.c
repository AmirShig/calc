#include "smart_calc.h"

int main() {
  int error_code = SUCCESS;

  stack_t A = {0};
  Lex value = {0};

  value.priority = 1;
  value.val = 1000.0;
  value.val_type = DIGIT;

  for (int i = 0; i < 5 && error_code == SUCCESS; i++) {
    error_code = push(&A, value);
    value.priority += 1;
    value.val += 20.5;
  }

  for (int i = 0; i < 6 && error_code == SUCCESS; i++) {
    Lex result = {0};
    error_code = pop(&A, &result);
  }

  printf("%d\n", error_code);
  return 0;
}