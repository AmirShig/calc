#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 256
#define OPERATORS_ "+-*/^M"
#define TRG_FUNCTION "sScCtTlLQ"

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_OPERATOR(c) (strchr(OPERATORS_, c) != NULL)
#define IS_FUNCTION(c) (strchr(TRG_FUNCTION, c) != NULL)

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

/***************** stack operations *******************/

typedef struct Lex {
  double val;    // Сама лексема
  int priority;  // проиоретет лексемы
  int unary;     // Аргумент для унарного минуса
} Lex;

typedef struct Node {
  Lex val;            // Значение и приоритет лексемы
  struct Node *next;  // Указатель на след. элемент стека
} Node;

typedef struct stack_tt {
  Node *top;  // Вершина стека
} stack_tt;

void create_stack(stack_tt *stack);
int is_empty(stack_tt *stack);
int push(stack_tt *head, Lex *value);
int pop(stack_tt *stack, Lex *result);

/***************** validation *******************/

typedef struct valid_params {
  errnum error_code;
  Position status;
  char *src;
} valid_params;

int validation(char *input);
int check_number(valid_params *args);
int check_bracket(const char *src);
int check_operators(valid_params *args);
int check_unary(valid_params *args);
void check_trigonometry(valid_params *args);

/***************** parser *******************/

typedef struct parser_params {
  Position status;
  char RPN_tmp[N_MAX * 2];
  int index;
  int unary_bracket;
  int brackets;
} parser_params;

int parser_to_rpn(char *src, char *RPN_exp);
int closing_bracket(stack_tt *operators_stack, parser_params *args);
int operators(stack_tt *operators_stack, char **src, parser_params *args);
void number(char **src, parser_params *args);
int get_priority(char src);
int functions(char **src, stack_tt *operators_stack, parser_params *args);

/***************** calculation *******************/

int calculation(char *src, double *result, double x_value);
int get_number(char **src, stack_tt *stack, double x_value);
int arithmetic_calculate(stack_tt *stack, int oper);
int function_calculate(stack_tt *stack, int oper, char **src);

/***************** entrance *******************/

errnum entrance(char *input, double *result, double x_value);

/***************** credit *******************/

typedef struct cred_info {
  double monthly_payment;
  double last_monthly_payment;
  double total_interest_paid;
  double total_payment;
} cred_info;

cred_info credit(double loan_amount, int loan_term, double interest_rate,
                 char loan_type);
void annuity(double loan_amount, int loan_term, double interest_rate,
             cred_info *args);
void differentiated(double loan_amount, int loan_term, double interest_rate,
                    cred_info *args);

/***************** credit *******************/

#endif  // SMART_CALC_H
