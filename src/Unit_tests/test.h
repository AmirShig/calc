#ifndef TEST_SMARTCALC
#define TEST_SMARTCALC

#include <check.h>

#include "../Backend/smart_calc.h"

Suite *General_test(void);
Suite *Dot_validation(void);
Suite *Brackets_validation(void);
Suite *Whole_validation(void);
Suite *Credit(void);

#endif