#include "smart_calc.h"

errnum entrance(char *input, double *result, double x_value) {
  errnum error_code = SUCCESS;
  char result_rpn[N_MAX * 2] = {0};
  double result_tmp = 0.0;

  error_code = validation(input);
  if (error_code == SUCCESS) {
    error_code = parser_to_rpn(input, result_rpn);
  }
  if (error_code == SUCCESS) {
    error_code = calculation(result_rpn, &result_tmp, x_value);
  }
  *result = result_tmp;
  return error_code;
}
