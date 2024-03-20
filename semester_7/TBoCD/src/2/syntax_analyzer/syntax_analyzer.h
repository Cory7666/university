#ifndef _SYNTAX_ANALYZER_H
#define _SYNTAX_ANALYZER_H

#include <stdio.h>
#include <stdlib.h>

/// Задание максимального количества цифр в целой части числа
#define ANALYZER_FLOAT_MAX_INTEGRAL_SIZE 10
/// Задание максимального количества цифр в дробной части числа
#define ANALYZER_FLOAT_MAX_FRAC_SIZE 2

void analyze(FILE* istream);

#endif  //_SYNTAX_ANALYZER_H
