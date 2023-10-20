#include "smart_calc.h"

int validation(char *input) {
  valid_params args = {0};
  if (input == NULL) return INCORRECT_INPUT;
  size_t len = strlen(input);
  if (len < 1 || len > 255) return INCORRECT_INPUT;
  char src_tmp[N_MAX + 10] = {0};
  strcpy(src_tmp, input);
  args.src = src_tmp;
  args.error_code = check_bracket(args.src);  // Проверка корректности скобок
  for (; *args.src && !args.error_code;) {
    while (IS_SPACE(*args.src)) args.src++;  // пропускаем все пробелы

    // проверяем корректность числа
    if (IS_DIGIT(*args.src)) {
      args.error_code = check_number(&args);
    } else if (*args.src == 'x') {
      if (args.status == END_POS) {
        args.error_code = FAILURE;
      } else {
        args.status = DIGIT;
        args.src++;
      }
    } else {
      args.error_code = check_operators(&args);
    }
  }
  if ((args.status == DIGIT || args.status == END_POS) && !args.error_code)
    args.error_code = SUCCESS;
  else
    args.error_code = INCORRECT_INPUT;
  return args.error_code;
}

int check_number(valid_params *args) {
  if (args->status == END_POS) {
    args->error_code = FAILURE;
  } else {
    args->status = DIGIT;
    while (IS_DIGIT(*args->src)) args->src++;
    if ((*args->src) == '.') {
      args->src++;
      if (!IS_DIGIT(*args->src)) {
        args->error_code = FAILURE;
      } else {
        while (IS_DIGIT(*args->src)) args->src++;
        if ((*args->src) == '.') args->error_code = FAILURE;
      }
    }
  }
  return args->error_code;
}

int check_operators(valid_params *args) {
  if (*args->src == '(') {
    args->src++;
    if (args->status == DIGIT || args->status == END_POS) {
      args->error_code = FAILURE;
    }
    args->status = START_POS;
  } else if (*args->src == ')') {
    args->src++;
    if (args->status == START_POS || args->status == CALC_OPER ||
        args->status == UNARY) {
      args->error_code = FAILURE;
    }
    args->status = END_POS;
  } else if (strchr("+-", *args->src)) {
    args->error_code = check_unary(args);
    args->src++;
  } else if (strchr("*/^", *args->src)) {
    args->src++;
    if (args->status == START_POS || args->status == CALC_OPER ||
        args->status == UNARY) {
      args->error_code = FAILURE;
    } else {
      args->status = CALC_OPER;
    }
  } else if (*args->src == 'm') {
    if (args->status == START_POS || args->status == CALC_OPER ||
        args->status == UNARY) {
      args->error_code = FAILURE;
    } else if (strncmp(args->src, "mod", 3) == 0) {
      args->src += 3;
      args->status = CALC_OPER;
    } else {
      args->error_code = FAILURE;
    }
  } else {
    check_trigonometry(args);
    if (args->error_code == SUCCESS && args->status == TRG_POS) {
      if (*args->src == '(') {
        args->status = START_POS;
      } else {
        args->error_code = FAILURE;
      }
    }
  }
  return args->error_code;
}

int check_bracket(const char *src) {
  int border = 0, error_code = SUCCESS;
  for (; *src != '\0' && !error_code; src++) {
    if ((*src) == '(') {
      border++;
    } else if ((*src) == ')') {
      border--;
      if (border < 0) error_code = FAILURE;
    }
  }
  if (border != 0) error_code = FAILURE;
  return error_code;
}

int check_unary(valid_params *args) {
  switch (args->status) {
    case START_POS:
    case CALC_OPER:
      args->status = UNARY;
      break;
    case UNARY:
      args->error_code = FAILURE;
      break;
    case END_POS:
    case DIGIT:
    case TRG_POS:
      args->status = CALC_OPER;
      break;
    default:
      args->error_code = FAILURE;
      break;
  }
  return args->error_code;
}

errnum trg_validation(Position *status) {
  errnum error_code = SUCCESS;
  if (*status == END_POS || *status == DIGIT) {
    error_code = INCORRECT_INPUT;
  }
  return error_code;
}

// проверка тригонометрических операторов
void check_trigonometry(valid_params *args) {
  const char *functions[] = {"sin",  "cos",  "tan", "asin", "acos",
                             "atan", "sqrt", "log", "ln"};
  int operators_num = sizeof(functions) / sizeof(functions[0]);

  if (strchr("actsl", *args->src) != NULL) {
    for (int i = 0, end_flag = 0; !end_flag && i < operators_num; i++) {
      if (strncmp(args->src, functions[i], strlen(functions[i])) == 0) {
        args->src += strlen(functions[i]);
        args->error_code = trg_validation(&args->status);
        if (args->error_code == SUCCESS) args->status = TRG_POS;
        end_flag = 1;
      }
      if (i == 8 && !end_flag) args->error_code = INCORRECT_INPUT;
    }
  } else if (args->status != END_POS && args->status != DIGIT) {
    args->error_code = FAILURE;
  }
}
