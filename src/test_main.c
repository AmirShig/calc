#include "smart_calc.h"

int main() {
  int error_code = SUCCESS;

  char input[N_MAX] = "1/3*(5+1)/2";
  char result_rpn[N_MAX] = {0};

  error_code = parser_to_rpn(input, result_rpn);

  if (error_code == SUCCESS) {
    printf("\ninput: %s\n\n", input);
    printf("WORK SUCCESS!\n");
    printf("\nexpression in RPN: %s\n", result_rpn);
  } else {
    printf("WORK FAILED\n");
  }
  return 0;
}