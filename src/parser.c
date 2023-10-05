#include "smart_calc.h"

int get_priority(char src);
int trigonometry(char **src, stack_t *operators_stack, Position *status);

int parser_to_rpn(char *src, char *RPN_exp) {
  Position status = START_POS;
  errnum error_code = SUCCESS;
  stack_t operators_stack;
  create_stack(&operators_stack);
  char RPN_tmp[N_MAX * 2] = {0};
  int index = 0, end_status = 0;
  for (; error_code == SUCCESS && !end_status; src++) {
    Lex lex_tmp = {0};
    if (*src == '\0') {
      end_status = 1;
      while (!is_empty(&operators_stack) && error_code == SUCCESS) {
        error_code = pop(&operators_stack, &lex_tmp);
        RPN_tmp[index++] = (int)lex_tmp.val;
        RPN_tmp[index++] = ' ';
      }
      break;
    }
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    switch (*src) {
      case '(':
        status = START_POS;
        lex_tmp.val = (int)*src;
        push(&operators_stack, &lex_tmp);
        break;
      case ')':
        status = END_POS;
        while (!is_empty(&operators_stack) && operators_stack.top->val != '(') {
          error_code = pop(&operators_stack, &lex_tmp);
          RPN_tmp[index++] = (int)lex_tmp.val;
          RPN_tmp[index++] = ' ';
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
        if ((status == CALC_OPER || status == START_POS) && *src == '-') {
          status = UNARY;
        } else {
          status = CALC_OPER;
          lex_tmp.priority = get_priority(*src);
          while (!is_empty(&operators_stack) &&
                 lex_tmp.priority <= operators_stack.top->priority) {
            error_code = pop(&operators_stack, &lex_tmp);
            RPN_tmp[index++] = (int)lex_tmp.val;
            RPN_tmp[index++] = ' ';
          }
          lex_tmp.val = (int)*src;
          lex_tmp.priority = get_priority(*src);
          error_code = push(&operators_stack, &lex_tmp);
        }
        break;
      default:
        if (IS_DIGIT(*src)) {
          if (status == UNARY) {
            RPN_tmp[index++] = 'u';
          }
          status = DIGIT;
          while (IS_DIGIT(*src)) RPN_tmp[index++] = *src++;
          if ((*src) == '.') {
            RPN_tmp[index++] = '.';
            src++;
            while (IS_DIGIT(*src)) RPN_tmp[index++] = *src++;
          }
          RPN_tmp[index++] = ' ';
          if (*src != '\0') src--;
        } else {
          error_code = trigonometry(&src, &operators_stack, &status);
        }
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
    priority = 4;
  } else if (isalpha(src)) {  // trigonometry
    priority = 3;
  }
  return priority;
}

int trigonometry(char **src, stack_t *operators_stack, Position *status) {
  errnum error_code = SUCCESS;
  int trg_status = 0;
  Lex lex_tmp = {0};
  if (strncmp(*src, "sin", 3) == 0) {
    *src += 3;
    trg_status = 1;
    lex_tmp.val = (int)'s';
  } else if (strncmp(*src, "sqrt", 4) == 0) {
    *src += 4;
    trg_status = 1;
    lex_tmp.val = (int)'Q';
  } else if (strncmp(*src, "cos", 3) == 0) {
    *src += 3;
    trg_status = 1;
    lex_tmp.val = (int)'c';
  } else if (strncmp(*src, "tan", 3) == 0) {
    *src += 3;
    trg_status = 1;
    lex_tmp.val = (int)'t';
  } else if (strncmp(*src, "acos", 4) == 0) {
    *src += 4;
    trg_status = 1;
    lex_tmp.val = (int)'C';
  } else if (strncmp(*src, "asin", 4) == 0) {
    *src += 4;
    trg_status = 1;
    lex_tmp.val = (int)'S';
  } else if (strncmp(*src, "atan", 4) == 0) {
    *src += 4;
    trg_status = 1;
    lex_tmp.val = (int)'T';
  } else if (strncmp(*src, "log", 3) == 0) {
    *src += 3;
    trg_status = 1;
    lex_tmp.val = (int)'L';
  } else if (strncmp(*src, "ln", 2) == 0) {
    *src += 2;
    trg_status = 1;
    lex_tmp.val = (int)'l';
  }
  if (trg_status) {
    *status = TRG_POS;
    if (**src != '\0') *src -= 1;
    lex_tmp.priority = 3;
    error_code = push(operators_stack, &lex_tmp);
  }
  return error_code;
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