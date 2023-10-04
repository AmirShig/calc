#include "smart_calc.h"

int parcer_to_stack(char *src, stack_t *RPN_stack, stack_t *operators_stack) {
  errnum error_code = SUCCESS;
  for (; *src && error_code == SUCCESS; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    switch (*src) {
      case '(':  // Если символ - открывающая скобка '(', добавьте ее в стек
                 // операторов.

        break;
      case ')':
        // Если символ - закрывающая скобка ')', выполните следующие шаги:

        // * Пока верхний элемент в стеке операторов не является открывающей
        // скобкой, выньте оператор из стека операторов и добавьте его в стек
        // вывода.

        // * Удалите открывающую скобку из стека операторов (но не
        // добавляйте ее в стек вывода).

        break;
      case '+':
      case '-':

        break;
      case '*':
      case '/':
      case '^':

        break;
      default:
        // Если символ - операнд (например, число), добавьте его в стек вывода.
        if (IS_DIGIT(*src)) {
          error_code = get_number(src, RPN_stack);
        } else {
          // error_code = check_trigonometry(src, &status, error_code);
        }
        break;
    }
  }
  return error_code;
}

int get_number(char *src, stack_t *stack) {
  errnum error_code = SUCCESS;
  char *endptr = NULL;
  double number = strtod(src, endptr);
  if (endptr == src) {  // число не обнаружено
    printf("Error of read the number\n");
    error_code = INCORRECT_INPUT;
  } else {
    src = endptr;
    Lex lex_tmp = {0};
    lex_tmp.val = number;
    lex_tmp.priority = 1;
    lex_tmp.val_type = DIGIT;
    error_code = push(stack, lex_tmp);
  }
  return error_code;
}