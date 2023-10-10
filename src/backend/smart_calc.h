#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define M_PI 3.14159265358979323846
#define N_MAX 256
#define OPERATORS "+-*/^M"
#define TRG_FUNCTION "sScCtTlLQ"

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_OPERATOR(c) (strchr(OPERATORS, c) != NULL)
#define IS_FUNCTION(c) (strchr(TRG_FUNCTION, c) != NULL)

typedef enum func { COS = 20, SIN, TAN, ACOS, ASIN, ATAN, SQRT, LN, LOG } func;

// typedef union Lex_value {
//   int value;
//   double value;
//   char value;
// } Lex_value;

// status of current position
typedef enum Position {
  START_POS,  // Начало выражения / сразу после откр. скобки
  CALC_OPER,  // Арифметический оператор
  END_POS,  // Конец выражения / после закр. скобки
  UNARY,    // Послу унарного оператора
  DIGIT,    // После числа
  TRG_POS  // После тригонометрического оператора
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
} Lex;

typedef struct Node {
  Lex val;            // Значение и приоритет лексемы
  struct Node *next;  // Указатель на след. элемент стека
} Node;

typedef struct stack_tt {
  Node *top;  // Вершина стека
} stack_tt;

/***************** validation *******************/

int validation(char *input);

/***************** stack operations *******************/

void create_stack(stack_tt *stack);
int is_empty(stack_tt *stack);
int push(stack_tt *head, Lex *value);
int pop(stack_tt *stack, Lex *result);

/***************** parser *******************/

int parser_to_rpn(char *src, char *RPN_exp);

/***************** calculation *******************/

int calculation(char *src, double *result);

#endif  // SMART_CALC_H
