#include "smart_calc.h"

int main() {
  char c = '^';

  if (IS_OPERATOR(c))
    printf("c - is an operator\n");
  else
    printf("c - is not an operator");
  return 0;
}

// int main() {  // ТЕСТ ПАРСИНГА СТРОКИ
//   int error_code = SUCCESS;

//   char input[N_MAX] = "512 - 128 * (125 - (17 + 12 ^ 2))";  // 5120
//   char result_rpn[N_MAX * 2] = {0};

//   error_code = parser_to_rpn(input, result_rpn);

//   if (error_code == SUCCESS) {
//     printf("\ninput: %s\n\n", input);
//     printf("WORK SUCCESS!\n");
//     printf("\nexpression in RPN: %s\n", result_rpn);
//   } else {
//     printf("WORK FAILED\n");
//   }
//   return 0;
// }

// int main() {  // ТЕСТ ВАЛИДАТОРА
//   int error_code = SUCCESS;

//   char input[N_MAX] = "(sin(cos(+10)*5))";
//   printf("\ninput: %s\n\n", input);
//   error_code = validation(input);

//   if (error_code == SUCCESS) {
//     printf("SUCCESS!\n");
//   } else {
//     printf("FAILED!\n");
//   }
//   return 0;
// }