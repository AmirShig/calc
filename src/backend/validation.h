#ifndef VALIDATE_H
#define VALIDATE_H

#include "smart_calc.h"

// // status of current position
// typedef enum Position {
//   START_POS = 1,  // Начало выражения / сразу после откр. скобки
//   CALC_OPER = 2,  // Арифметический оператор
//   END_POS = 3,  // Конец выражения / после закр. скобки
//   UNARY = 4,  // Послу унарного оператора
//   DIGIT = 5,  // После числа
//   TRG_POS = 6  // После тригонометрического оператора
// } Position;

int check_bracket(const char *src);
int check_operators(char **src, Position *status);
int check_unary(Position **status, errnum error_code);
char check_trigonometry(char **src, Position **status, errnum *error_code);

#endif  // VALIDATE_H