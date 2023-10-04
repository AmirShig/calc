#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 256

// #define operators "+-*/^"

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

typedef enum lex_type {
  DIGIT = 10,
  OPERATOR,
  BRACKET,
  FUNCTION,
  UNARY
  // BINARY,
} data_type;

// typedef union Lex_value {
//   int i_num;
//   double float_num;
//   char character;
// } Lex_value;

typedef enum error_code {
  SUCCESS,
  FAILURE,
  CALC_ERROR,
  INCORRECT_INPUT,
  MALLOC_ERR,
  STACK_OVERFLOW,
  EMPTY_STACK
} errnum;

typedef struct Lex {
  double val;    // Сама лексема
  int priority;  // проиоретет лексемы
  data_type val_type;  // тип лексемы (число/скобка/оператор)
} Lex;

typedef struct Node {
  Lex val;  // Значение, тип и приоритет лексемы
  struct Node *next;  // Указатель на след. элемент стека
} Node;

typedef struct stack_t {
  Node *top;  // Вершина стека
} stack_t;

/***************** validation *******************/

int validation(const char *src);

/***************** stack operations *******************/

void create_stack(stack_t *stack);
int is_empty(stack_t *stack);
int push(stack_t *head, Lex value);
int pop(stack_t *stack, Lex *result);

#endif  // SMART_CALC_H
