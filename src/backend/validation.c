#include "validation.h"

int validation(char *input) {
  errnum error_code = SUCCESS;
  Position status = START_POS;
  if (!input) return INCORRECT_INPUT;  //   ???
  char *src = (char *)calloc(strlen(input), sizeof(char));
  if (src == NULL) {
    error_code = MALLOC_ERR;
  } else {
    strcpy(src, input);
    error_code = check_bracket(src);  // Проверка корректности скобок
  }
  for (; *src && !error_code; src++) {
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы

    // проверяем корректность числа
    if (IS_DIGIT(*src)) {
      if (status == END_POS) {
        error_code = FAILURE;
        break;
      }
      status = DIGIT;
      while (IS_DIGIT(*src)) src++;
      if ((*src) == '.') {
        src++;
        if (!IS_DIGIT(*src)) {
          error_code = FAILURE;
          break;
        }
        while (IS_DIGIT(*src)) src++;
      }
    }
    while (IS_SPACE(*src)) src++;  // пропускаем все пробелы

    error_code = check_operators(&src, &status);
  }
  if ((status == DIGIT || status == END_POS) && !error_code)
    error_code = SUCCESS;
  else
    error_code = INCORRECT_INPUT;
  return error_code;
}

int check_operators(char **src, Position *status) {
  errnum error_code = SUCCESS;
  switch (**src) {
    case '(':
      if (*status == DIGIT || *status == END_POS) {
        error_code = FAILURE;
      }
      *status = START_POS;
      break;
    case ')':
      if (*status == START_POS || *status == CALC_OPER || *status == UNARY) {
        error_code = FAILURE;
      }
      *status = END_POS;
      break;
    case '+':
    case '-':
      error_code = check_unary(&status, error_code);
      break;
    case '*':
    case '/':
    case '^':
      if (*status == START_POS || *status == CALC_OPER || *status == UNARY) {
        error_code = FAILURE;
      } else {
        *status = CALC_OPER;
      }
      break;
    case 'm':
      if (*status == START_POS || *status == CALC_OPER || *status == UNARY) {
        error_code = FAILURE;
      } else if (strncmp(*src, "mod", 3) == 0) {
        *src += 2;
        *status = CALC_OPER;
      } else {
        error_code = FAILURE;
      }
      break;
    default:
      **src = check_trigonometry(src, &status, &error_code);
      if (error_code == SUCCESS && *status == TRG_POS) {
        if (**src == '(') {
          *status = START_POS;
        } else {
          error_code = FAILURE;
        }
      }
      break;
  }
  return error_code;
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

int check_unary(Position **status, errnum error_code) {
  switch (**status) {
    case START_POS:
    case CALC_OPER:
      **status = UNARY;
      break;
    case UNARY:
      error_code = FAILURE;
      break;
    case END_POS:
    case DIGIT:
    case TRG_POS:
      **status = CALC_OPER;
      break;
    default:
      error_code = FAILURE;
      break;
  }
  return error_code;
}

// проверка тригонометрических операторов
char check_trigonometry(char **src, Position **status, errnum *error_code) {
  switch (**src) {
    case 's':  // sin(x), sqrt(x)
      if (strncmp(*src, "sin", 3) == 0) {
        *src += 3;
        **status = TRG_POS;
      } else if (strncmp(*src, "sqrt", 4) == 0) {
        *src += 4;
        **status = TRG_POS;
      } else {
        *error_code = FAILURE;
      }
      break;
    case 'c':  // cos(x)
      if (strncmp(*src, "cos", 3) == 0) {
        *src += 3;
        **status = TRG_POS;
      } else {
        *error_code = FAILURE;
      }
      break;
    case 't':  // tan(x)
      if (strncmp(*src, "tan", 3) == 0) {
        *src += 3;
        **status = TRG_POS;
      } else {
        *error_code = FAILURE;
      }
      break;
    case 'a':  // acos(x), asin(x), atan(x)
      if (strncmp(*src, "acos", 4) == 0) {
        *src += 4;
        **status = TRG_POS;
      } else if (strncmp(*src, "asin", 4) == 0) {
        *src += 4;
        **status = TRG_POS;
      } else if (strncmp(*src, "atan", 4) == 0) {
        *src += 4;
        **status = TRG_POS;
      } else {
        *error_code = FAILURE;
      }
      break;
    case 'l':  // log(x), ln(x)
      if (strncmp(*src, "log", 3) == 0) {
        *src += 3;
        **status = TRG_POS;
      } else if (strncmp(*src, "ln", 2) == 0) {
        *src += 2;
        **status = TRG_POS;
      } else {
        *error_code = FAILURE;
      }
      break;
    default:
      if (**status != END_POS && **status != DIGIT) *error_code = FAILURE;
      break;
  }
  return **src;
}