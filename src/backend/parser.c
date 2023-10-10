#include "smart_calc.h"

/*header start*/
typedef struct params {
  Position status;
  char RPN_tmp[N_MAX * 2];
  int index;
} params;

int closing_bracket(stack_tt *operators_stack, params *args);
int operators(stack_tt *operators_stack, char **src, params *args);
void number(char **src, params *args);
int get_priority(char src);
int functions(char **src, stack_tt *operators_stack, params *args);
/*header end*/

int parser_to_rpn(char *src, char *RPN_exp) {
  errnum error_code = SUCCESS;
  stack_tt operators_stack;
  create_stack(&operators_stack);
  params args = {0};
  for (int end_status = 0; error_code == SUCCESS && !end_status; src++) {
    Lex lex_tmp = {0};
    if (*src == '\0') {
      end_status = 1;
      while (!is_empty(&operators_stack) && error_code == SUCCESS) {
        error_code = pop(&operators_stack, &lex_tmp);
        args.RPN_tmp[args.index++] = (int)lex_tmp.val;
        args.RPN_tmp[args.index++] = ' ';
      }
      break;  // ??????????????
    }
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
    switch (*src) {
      case '(':
        args.status = START_POS;
        lex_tmp.val = (int)*src;
        push(&operators_stack, &lex_tmp);
        break;
      case ')':
        args.status = END_POS;
        error_code = closing_bracket(&operators_stack, &args);
        break;
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        error_code = operators(&operators_stack, &src, &args);
        break;
      default:
        if (IS_DIGIT(*src)) {
          number(&src, &args);
        } else {
          error_code = functions(&src, &operators_stack, &args);
        }
        break;
    }
  }
  if (error_code == SUCCESS) strcpy(RPN_exp, args.RPN_tmp);
  return error_code;
}

int closing_bracket(stack_tt *operators_stack, params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  while (!is_empty(operators_stack) && operators_stack->top->val.val != '(') {
    error_code = pop(operators_stack, &lex_tmp);
    if (lex_tmp.unary) args->RPN_tmp[args->index++] = 'u';
    args->RPN_tmp[args->index++] = (int)lex_tmp.val;
    args->RPN_tmp[args->index++] = ' ';
  }
  if (!is_empty(operators_stack) && operators_stack->top->val.val == '(') {
    error_code = pop(operators_stack, NULL);
  } else {
    error_code = FAILURE;
  }
  return error_code;
}

int operators(stack_tt *operators_stack, char **src, params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  if ((args->status == CALC_OPER || args->status == START_POS) &&
      **src == '-') {
    args->status = UNARY;
  } else {
    args->status = CALC_OPER;
    lex_tmp.priority = get_priority(**src);
    while (!is_empty(operators_stack) &&
           lex_tmp.priority <= operators_stack->top->val.priority) {
      error_code = pop(operators_stack, &lex_tmp);
      if (lex_tmp.unary) args->RPN_tmp[args->index++] = 'u';
      args->RPN_tmp[args->index++] = (int)lex_tmp.val;
      args->RPN_tmp[args->index++] = ' ';
    }
    lex_tmp.val = (int)**src;
    lex_tmp.priority = get_priority(**src);
    error_code = push(operators_stack, &lex_tmp);
  }
  return error_code;
}

void number(char **src, params *args) {
  if (args->status == UNARY) {
    args->RPN_tmp[args->index++] = 'u';
  }
  args->status = DIGIT;
  while (IS_DIGIT(**src)) {
    args->RPN_tmp[args->index++] = **src;
    *src += 1;
  }
  if ((**src) == '.') {
    args->RPN_tmp[args->index] = '.';
    args->index += 1;
    *src += 1;
    while (IS_DIGIT(**src)) {
      args->RPN_tmp[args->index] = **src;
      args->index += 1;
      *src += 1;
    }
  }
  args->RPN_tmp[args->index++] = ' ';
  if (**src != '\0') *src -= 1;
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

int functions(char **src, stack_tt *operators_stack, params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  if (args->status == UNARY) lex_tmp.unary = 1;
  if (strncmp(*src, "sin", 3) == 0) {
    *src += 3;
    lex_tmp.val = (int)'s';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "sqrt", 4) == 0) {
    *src += 4;
    lex_tmp.val = (int)'Q';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "cos", 3) == 0) {
    *src += 3;
    lex_tmp.val = (int)'c';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "tan", 3) == 0) {
    *src += 3;
    lex_tmp.val = (int)'t';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "acos", 4) == 0) {
    *src += 4;
    lex_tmp.val = (int)'C';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "asin", 4) == 0) {
    *src += 4;
    lex_tmp.val = (int)'S';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "atan", 4) == 0) {
    *src += 4;
    lex_tmp.val = (int)'T';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "log", 3) == 0) {
    *src += 3;
    lex_tmp.val = (int)'L';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "ln", 2) == 0) {
    *src += 2;
    lex_tmp.val = (int)'l';
    lex_tmp.priority = 3;
  } else if (strncmp(*src, "mod", 3) == 0) {
    *src += 3;
    lex_tmp.unary = 0;
    lex_tmp.val = (int)'M';
    lex_tmp.priority = 2;
  }
  if (lex_tmp.priority) {
    if (**src != '\0') *src -= 1;
    error_code = push(operators_stack, &lex_tmp);
  }
  return error_code;
}
