#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14159265358979323846
#define N_MAX 256
#define OPERATORS "+-*/^"
#define TRG_FUNCTION "sScCtTlLQ"

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_OPERATOR(c) (strchr(OPERATORS, c) != NULL)
#define IS_FUNCTION(c) (strchr(TRG_FUNCTION, c) != NULL)

typedef enum func { COS = 20, SIN, TAN, ACOS, ASIN, ATAN, SQRT, LN, LOG } func;

typedef enum lex_type {
  // DIGIT = 10,
  // OPERATOR,
  // BRACKET,
  // FUNCTION,
  // UNARY
  BINARY
} data_type;

// typedef union Lex_value {
//   int i_num;
//   double float_num;
//   char character;
// } Lex_value;

// status of current position
typedef enum Position {
  START_POS = 1,  // Начало выражения / сразу после откр. скобки
  CALC_OPER = 2,  // Арифметический оператор
  END_POS = 3,  // Конец выражения / после закр. скобки
  UNARY = 4,  // Послу унарного оператора
  DIGIT = 5,  // После числа
  TRG_POS = 6  // После тригонометрического оператора
} Position;

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
  // Lex val;  // Значение, тип и приоритет лексемы
  double val;    // Сама лексема
  int priority;  // проиоретет лексемы
  data_type val_type;  // тип лексемы (число/скобка/оператор)
  struct Node *next;  // Указатель на след. элемент стека
} Node;

typedef struct stack_t {
  Node *top;  // Вершина стека
} stack_t;

/***************** validation *******************/

int validation(char *src);

/***************** stack operations *******************/

void create_stack(stack_t *stack);
int is_empty(stack_t *stack);
int push(stack_t *head, Lex *value);
int pop(stack_t *stack, Lex *result);

/***************** parser *******************/

int parser_to_rpn(char *src, char *RPN_exp);

/***************** calculation *******************/

int calculation(char *src, double *result);

#endif  // SMART_CALC_H
