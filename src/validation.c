#include "smart_calc.h"

// status of current position
#define START_POS 1  // Начало выражения / сразу после откр. скобки
#define CALC_OPER 2  // Арифметический оператор
#define END_POS 3  // Конец выражения / после закр. скобки
#define UNARY 4  // Послу унарного оператора
#define DIGIT 5  // После числа
#define TRG_POS 6  // После тригонометрического оператора

int check_bracket(const char *src);
int check_operators(const char *src, int *status);
int check_unary(int **status, int error_code);
int check_trigonometry(const char *src, int **status, int error_code);

int validation(const char *src) {
  int error_code = SUCCESS;
  int status = START_POS;

  error_code = check_bracket(src);  // Проверка корректности скобок

  for (; *src && !error_code; src++) {
    while (is_space(*src)) src++;  // пропускаем все пробелы

    // проверяем корректность числа
    if (is_digit(*src)) {
      status = DIGIT;
      while (is_digit(*src)) src++;
      if ((*src) == '.') {
        src++;
        if (!is_digit(*src)) {
          error_code = FAILURE;
          break;
        }
        while (is_digit(*src)) src++;
      }
    }
    while (is_space(*src)) src++;  // пропускаем все пробелы

    error_code = check_operators(src, &status);
  }
  if ((status == DIGIT || status == END_POS) && !error_code)
    error_code = SUCCESS;
  else
    error_code = FAILURE;
  return error_code;
}

int check_operators(const char *src, int *status) {
  int error_code = SUCCESS;

  switch (*src) {
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
    default:
      error_code = check_trigonometry(src, &status, error_code);
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

int check_unary(int **status, int error_code) {
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
int check_trigonometry(const char *src, int **status, int error_code) {
  switch (*src) {
    case 's':  // sin(x), sqrt(x)
      if (strncmp(src, "sin", 3) == 0) {
        **status = TRG_POS;
      } else if (strncmp(src, "sqrt", 4) == 0) {
        **status = TRG_POS;
      } else {
        error_code = FAILURE;
      }
      break;
    case 'c':  // cos(x)
      if (strncmp(src, "cos", 3) == 0) {
        **status = TRG_POS;
      } else {
        error_code = FAILURE;
      }
      break;
    case 't':  // tan(x)
      if (strncmp(src, "tan", 3) == 0) {
        **status = TRG_POS;
      } else {
        error_code = FAILURE;
      }
      break;
    case 'a':  // acos(x), asin(x), atan(x)
      if (strncmp(src, "acos", 4) == 0) {
        **status = TRG_POS;
      } else if (strncmp(src, "asin", 4) == 0) {
        **status = TRG_POS;
      } else if (strncmp(src, "atan", 4) == 0) {
        **status = TRG_POS;
      } else {
        error_code = FAILURE;
      }
      break;
    case 'l':  // log(x), ln(x)
      if (strncmp(src, "log", 3) == 0) {
        **status = TRG_POS;
      } else if (strncmp(src, "ln", 2) == 0) {
        **status = TRG_POS;
      } else {
        error_code = FAILURE;
      }
      break;
    default:
      if (**status != END_POS && **status != DIGIT) error_code = FAILURE;
      break;
  }
  return error_code;
}