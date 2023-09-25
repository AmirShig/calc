#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define N_MAX 256
#define operators "+-*/^"

#define IS_UNARY(c) (c == '+' || c == '-')
#define IS_SPACE(c) (c == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')

int validation(const char *src);
#endif  // SMART_CALC_H