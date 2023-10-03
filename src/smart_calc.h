#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 256
#define operators "+-*/^"

typedef enum lex_type {
  DIGIT = 10,
  OPERATOR,
  BRACKET,
  FUNCTION,
  UNARY
  // BINARY,
} data_type;

typedef enum error_code {
  SUCCESS = 0,
  FAILURE,
  CALC_ERROR,
  INCORRECT_INPUT,
  MALLOC_ERR,
  STACK_OVERFLOW
} errnum;

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

typedef struct Lex {
  double val;    // Сама лексема
  int priorety;  // проиоретет лексемы
  int val_type;  // тип лексемы (число/скобка/оператор)
} Lex;

typedef struct stack_t {
  Node *top;  // Вершина стека
} stack_t;

typedef struct Node {
  Lex val;  // Значение, тип и приоритет лексемы
  struct Node *next;  // Указатель на след. элемент стека
} Node;

int validation(const char *src);
#endif  // SMART_CALC_H
