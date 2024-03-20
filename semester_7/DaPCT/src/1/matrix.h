#pragma once

#include <stdint.h>
#include <stdio.h>

typedef double elem_t;
typedef elem_t matrix_t[3][3];

extern void matrix_init_from_file(FILE* steram, matrix_t matrix);
extern elem_t matrix_get_minor(const matrix_t matrix, uint32_t minor);
extern elem_t matrix_calculate_determinant(const matrix_t matrix);
extern void matrix_calculate_minor_matrix(matrix_t out, const matrix_t in_matr);
extern void matrix_make_algebr_addit(matrix_t matrix);
extern void matrix_transpose(matrix_t matrix);
extern void matrix_calculate_inverse_matrix(matrix_t matrix,
                                            elem_t determinant);

extern void matrix_print(const matrix_t matrix);
extern void matrix_print_named(const char* name, const matrix_t matrix);
