#include "smart_calc.h"

int get_priority(char src);

int parser_to_rpn(char *src, char *RPN_exp) {
  errnum error_code = SUCCESS;
  stack_t operators_stack;
  create_stack(&operators_stack);
  char RPN_tmp[N_MAX] = {0};
  for (int index = 0; *src && error_code == SUCCESS; src++) {
    Lex lex_tmp = {0};
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    switch (*src) {
      case '(':
        lex_tmp.val = (int)*src;
        lex_tmp.val_type = BRACKET;
        push(&operators_stack, &lex_tmp);
        break;
      case ')':
        while (!is_empty(&operators_stack) && operators_stack.top->val != '(') {
          error_code = pop(&operators_stack, &lex_tmp);
          RPN_tmp[index++] = (int)lex_tmp.val;
        }
        if (!is_empty(&operators_stack) && operators_stack.top->val == '(') {
          // Удалить '(' из стека
          error_code = pop(&operators_stack, &lex_tmp);  // Заменить на NULL?
        } else {
          error_code = FAILURE;
        }
        break;
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        lex_tmp.priority = get_priority(*src);
        while (!is_empty(&operators_stack) &&
               lex_tmp.priority <= operators_stack.top->priority) {
          error_code = pop(&operators_stack, &lex_tmp);
          RPN_tmp[index++] = (int)lex_tmp.val;
        }
        lex_tmp.val = (int)*src;
        lex_tmp.priority = get_priority(*src);
        error_code = push(&operators_stack, &lex_tmp);
        break;
      default:
        // while (IS_DIGIT(*src)) {
        //   RPN_tmp[index++] = *src++;
        // }
        if (IS_DIGIT(*src)) {
          while (IS_DIGIT(*src)) RPN_tmp[index++] = *src++;
          if ((*src) == '.') {
            src++;
            while (IS_DIGIT(*src)) RPN_tmp[index++] = *src++;
          }
          src--;
        } else if (*src == '\0') {
          while (!is_empty(&operators_stack)) {
            error_code = pop(&operators_stack, &lex_tmp);
            RPN_tmp[index++] = (int)lex_tmp.val;
          }
        }
        // error_code = check_trigonometry(src, &status, error_code);
        break;
    }
  }
  if (error_code == SUCCESS) strcpy(RPN_exp, RPN_tmp);
  return error_code;
}

// Функция для получения приоритета оператора
int get_priority(char src) {
  int priority = 0;
  if (src == '+' || src == '-') {
    priority = 1;
  } else if (src == '*' || src == '/') {
    priority = 2;
  } else if (src == '^') {
    priority = 3;
  }
  return priority;
}

// int get_number(char *src, stack_t *stack) {
//   errnum error_code = SUCCESS;
//   char *endptr = NULL;
//   double number = strtod(src, endptr);
//   if (endptr == src) {  // число не обнаружено
//     printf("Error of read the number\n");
//     error_code = INCORRECT_INPUT;
//   } else {
//     src = endptr;
//     Lex lex_tmp = {0};
//     lex_tmp.val = number;
//     lex_tmp.priority = 1;
//     lex_tmp.val_type = DIGIT;
//     error_code = push(stack, &lex_tmp);
//   }
//   return error_code;
// }