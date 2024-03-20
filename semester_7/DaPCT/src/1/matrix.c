#include "matrix.h"

#include <mpi.h>
#include <stdio.h>
#include <string.h>

static inline elem_t _matrix_minor_prod_of(const matrix_t matrix, uint8_t row1,
                                           uint8_t row2, uint8_t col1,
                                           uint8_t col2) {
  return matrix[row1][col1] * matrix[row2][col2] -
         matrix[row2][col1] * matrix[row1][col2];
}

elem_t matrix_get_minor(const matrix_t matrix, uint32_t minor) {
  elem_t ret = 0;
  switch (minor) {
    case 0:
      ret = _matrix_minor_prod_of(matrix, 1, 2, 1, 2);
      break;
    case 1:
      ret = _matrix_minor_prod_of(matrix, 1, 2, 0, 2);
      break;
    case 2:
      ret = _matrix_minor_prod_of(matrix, 1, 2, 0, 1);
      break;
    case 3:
      ret = _matrix_minor_prod_of(matrix, 0, 2, 1, 2);
      break;
    case 4:
      ret = _matrix_minor_prod_of(matrix, 0, 2, 0, 2);
      break;
    case 5:
      ret = _matrix_minor_prod_of(matrix, 0, 2, 0, 1);
      break;
    case 6:
      ret = _matrix_minor_prod_of(matrix, 0, 1, 1, 2);
      break;
    case 7:
      ret = _matrix_minor_prod_of(matrix, 0, 1, 0, 2);
      break;
    case 8:
      ret = _matrix_minor_prod_of(matrix, 0, 1, 0, 1);
      break;
  }
  return ret;
}

void matrix_calculate_minor_matrix(matrix_t out, const matrix_t in_matr) {
  for (uint32_t i = 0; i < 9; ++i) {
    out[i / 3][i % 3] = matrix_get_minor(in_matr, i);
  }
}

void matrix_print(const matrix_t matrix) {
  matrix_print_named("matrix", matrix);
}

elem_t matrix_calculate_determinant(const matrix_t matrix) {
  return matrix[0][0] * _matrix_minor_prod_of(matrix, 1, 2, 1, 2) -
         matrix[0][1] * _matrix_minor_prod_of(matrix, 1, 2, 0, 2) +
         matrix[0][2] * _matrix_minor_prod_of(matrix, 1, 2, 0, 1);
}

void matrix_print_named(const char* name, const matrix_t matrix) {
  const int offset = strlen(name) + 3;
  printf("%s=[ ", name);
  printf(
      "% 7.2f % 7.2f % 7.2f\n"
      "%*c% 7.2f % 7.2f % 7.2f\n"
      "%*c% 7.2f % 7.2f % 7.2f ]\n",
      matrix[0][0], matrix[0][1], matrix[0][2], offset, ' ', matrix[1][0],
      matrix[1][1], matrix[1][2], offset, ' ', matrix[2][0], matrix[2][1],
      matrix[2][2]);
}

void matrix_make_algebr_addit(matrix_t matrix) {
  for (uint8_t row = 0; row < 3; ++row) {
    for (uint8_t col = 0; col < 3; ++col) {
      if (1 == (row + col) % 2) {
        matrix[row][col] = (-1) * matrix[row][col];
      }
    }
  }
}

void matrix_transpose(matrix_t matrix) {
  elem_t tmp;
  for (uint8_t idx = 1; idx < 3; ++idx) {
    for (uint8_t row = 0; row < idx; ++row) {
      tmp = matrix[row][idx];
      matrix[row][idx] = matrix[idx][row];
      matrix[idx][row] = tmp;
    }
  }
}

void matrix_calculate_inverse_matrix(matrix_t matrix, elem_t determinant) {
  for (uint8_t idx = 0; idx < 9; ++idx) {
    const uint8_t row = idx / 3, col = idx % 3;
    matrix[row][col] *= determinant;
  }
}

/*
 * Функция, считывающая из файла матрицу вида:
X X X
X X X
X X X
 */
void matrix_init_from_file(FILE* stream, matrix_t matrix) {
  double tmp;
  for (uint8_t row = 0; row < 3; ++row) {
    for (uint8_t col = 0; col < 3; ++col) {
      fscanf(stream, "%lf", &tmp);
      matrix[row][col] = tmp;
    }
  }
}
