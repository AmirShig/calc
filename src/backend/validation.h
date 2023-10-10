#ifndef VALIDATE_H
#define VALIDATE_H

#include "smart_calc.h"

int check_bracket(const char *src);
int check_operators(char **src, Position *status);
int check_unary(Position **status, errnum error_code);
char check_trigonometry(char **src, Position **status, errnum *error_code);

#endif  // VALIDATE_H