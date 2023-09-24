#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define N_MAX 255
#define operators "+-*/^"

#define is_unary(c) (c == '+' || c == '-')
#define is_space(c) (c == ' ')
#define is_digit(c) ((c) >= '0' && (c) <= '9')

int validation(const char *src);
#endif  // SMART_CALC_H
