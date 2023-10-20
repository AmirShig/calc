#include "smart_calc.h"

int parser_to_rpn(char *src, char *RPN_exp) {
  errnum error_code = SUCCESS;
  stack_tt operators_stack;
  create_stack(&operators_stack);
  parser_params args = {0};
  for (int end_status = 0; error_code == SUCCESS && !end_status; src++) {
    Lex lex_tmp = {0};
    if (*src == '\0') {
      end_status = 1;
      while (!is_empty(&operators_stack) && error_code == SUCCESS) {
        error_code = pop(&operators_stack, &lex_tmp);
        args.RPN_tmp[args.index++] = (int)lex_tmp.val;
        args.RPN_tmp[args.index++] = ' ';
      }
    } else {
      while (IS_SPACE(*src)) src++;  // пропускаем все пробелы
      if (*src == '(') {
        if (args.status == UNARY) args.unary_bracket++;
        args.brackets++;
        args.status = START_POS;
        lex_tmp.val = (int)*src;
        push(&operators_stack, &lex_tmp);
      } else if (*src == ')') {
        args.status = END_POS;
        error_code = closing_bracket(&operators_stack, &args);
      } else if (strchr("+-*/^", *src)) {
        error_code = operators(&operators_stack, &src, &args);
      } else if (IS_DIGIT(*src) || *src == 'x') {
        number(&src, &args);
      } else {
        error_code = functions(&src, &operators_stack, &args);
      }
    }
  }
  if (error_code == SUCCESS) strcpy(RPN_exp, args.RPN_tmp);
  return error_code;
}

int closing_bracket(stack_tt *operators_stack, parser_params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  while (!is_empty(operators_stack) && operators_stack->top->val.val != '(') {
    error_code = pop(operators_stack, &lex_tmp);
    if (lex_tmp.unary) args->RPN_tmp[args->index++] = 'u';
    args->RPN_tmp[args->index++] = (int)lex_tmp.val;
    args->RPN_tmp[args->index++] = ' ';
  }
  if (args->unary_bracket == args->brackets) {
    strcat(args->RPN_tmp, "u1 * ");
    args->index += 5;
    args->unary_bracket--;
  }
  args->brackets--;
  if (!is_empty(operators_stack) && operators_stack->top->val.val == '(') {
    error_code = pop(operators_stack, NULL);
  } else {
    error_code = FAILURE;
  }
  return error_code;
}

int operators(stack_tt *operators_stack, char **src, parser_params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  Lex lex_current = {0};
  if ((args->status == CALC_OPER || args->status == START_POS) &&
      (**src == '-' || **src == '+')) {
    if (**src == '-') args->status = UNARY;
  } else {
    args->status = CALC_OPER;
    lex_current.priority = get_priority(**src);
    while (!is_empty(operators_stack) &&
           lex_current.priority <= operators_stack->top->val.priority) {
      error_code = pop(operators_stack, &lex_tmp);
      if (lex_tmp.unary) args->RPN_tmp[args->index++] = 'u';
      args->RPN_tmp[args->index++] = (int)lex_tmp.val;
      args->RPN_tmp[args->index++] = ' ';
    }
    lex_current.val = (int)**src;
    lex_current.priority = get_priority(**src);
    error_code = push(operators_stack, &lex_current);
  }
  return error_code;
}

void number(char **src, parser_params *args) {
  if (args->status == UNARY) {
    args->RPN_tmp[args->index++] = 'u';
  }
  args->status = DIGIT;
  if (**src == 'x') {
    args->RPN_tmp[args->index++] = 'x';
    *src += 1;
  } else if (IS_DIGIT(**src)) {
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
  }
  args->RPN_tmp[args->index++] = ' ';
  if (**src != '\0') *src -= 1;
}

// Функция для получения приоритета оператора
int get_priority(char src) {
  int priority = 0;
  if (src == '+' || src == '-') {
    priority = 1;
  } else if (src == '*' || src == '/' || src == 'm') {
    priority = 2;
  } else if (src == '^') {
    priority = 4;
  } else if (strchr(TRG_FUNCTION, src)) {  // trigonometry
    priority = 3;
  }
  return priority;
}

int functions(char **src, stack_tt *operators_stack, parser_params *args) {
  errnum error_code = SUCCESS;
  Lex lex_tmp = {0};
  char *function_name[] = {"sin",  "cos",  "tan", "asin", "acos",
                           "atan", "sqrt", "log", "ln",   "mod"};
  char functions_code[] = {'s', 'c', 't', 'S', 'C', 'T', 'Q', 'L', 'l', 'M'};
  int func_num = sizeof(function_name) / sizeof(function_name[0]);

  if (args->status == UNARY) lex_tmp.unary = 1;
  for (int i = 0; i < func_num; i++) {
    if (strncmp(*src, function_name[i], strlen(function_name[i])) == 0) {
      args->status = CALC_OPER;
      *src += strlen(function_name[i]);
      lex_tmp.val = (int)functions_code[i];
      lex_tmp.priority = (functions_code[i] == 'M' ? 2 : 3);
      lex_tmp.unary = (functions_code[i] == 'M' ? 0 : lex_tmp.unary);
      if (**src != '\0') *src -= 1;
      error_code = push(operators_stack, &lex_tmp);
    }
  }
  return error_code;
}
