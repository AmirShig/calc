#include "smart_calc.h"

int main() {
  int error_code = SUCCESS;
  char input[N_MAX + 1];

  if (fgets(input, N_MAX, stdin)) {
    printf("in\n");
    error_code = validation(input);
    printf("Expression: %s\n", input);
    if (error_code == SUCCESS)
      printf("The expression is correct!\n");
    else
      printf("The epression is incorrect!\n");
  }

  return 0;
}