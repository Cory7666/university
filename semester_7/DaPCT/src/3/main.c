#include <mpi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSIZE 2

typedef int elem_t;
typedef int vecsize_t;
typedef elem_t matvec_t[MSIZE];
typedef elem_t sqmatrix_t[MSIZE][MSIZE];

static int rank, size;

static void _print_named_vector(const char* name, const matvec_t* vec) {
  printf("Proc%d: %s = [", rank, name);
  for (vecsize_t idx = 0; idx < MSIZE; ++idx) {
    printf("%2d%s", *vec[idx], (idx + 1 < MSIZE) ? ", " : "");
  }
  printf("]\n");
}

static void _print_named_matrix(const char* name, const sqmatrix_t* matrix) {
  int offset = 0;
  printf("Proc%d: %s = [%n", rank, name, &offset);
  for (vecsize_t row = 0; row < MSIZE; ++row) {
    if (1 <= row) {
      printf("%*c", offset, ' ');
    }
    for (vecsize_t col = 0; col < MSIZE; ++col) {
      printf("%2d ", *matrix[row][col]);
    }
    printf("\n");
  }
  printf("]");
}

static void _reduce_vectors(const elem_t* vec_a, const elem_t* vec_b,
                            vecsize_t size, elem_t* result) {
  elem_t tmp = 0;
  for (vecsize_t idx = 0; idx < size; ++idx) {
    tmp += vec_a[idx] * vec_b[idx];
  }
  *result += tmp;
}

static void _sum_vectors(const matvec_t vec_a, const matvec_t vec_b,
                         matvec_t result) {
  for (vecsize_t idx = 0; idx < MSIZE; ++idx) {
    result[idx] += vec_a[idx] * vec_b[idx];
  }
}

static void _create_cart_comm(MPI_Comm* cart_comm) {
  const int dims[] = {MSIZE, MSIZE};
  const int periods[] = {false, false};
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, false, cart_comm);
}

static void _init_matrix_A(sqmatrix_t* matrix) {
  *matrix[0][0] = 1;
  *matrix[0][1] = 2;
  *matrix[1][0] = 3;
  *matrix[1][1] = 4;
}

static void _init_matrix_B(sqmatrix_t* matrix) {
  *matrix[0][0] = 2;
  *matrix[0][1] = 2;
  *matrix[1][0] = 2;
  *matrix[1][1] = 2;
}

static void _init_matrixes_if_root(sqmatrix_t** matrix_a, sqmatrix_t** matrix_b,
                                   sqmatrix_t** matrix_c) {
  if (0 == rank) {
    *matrix_a = calloc(MSIZE * MSIZE, sizeof(elem_t));
    *matrix_b = calloc(MSIZE * MSIZE, sizeof(elem_t));
    *matrix_c = calloc(MSIZE * MSIZE, sizeof(elem_t));
    _init_matrix_A(*matrix_a);
    _init_matrix_B(*matrix_b);
  }
}

static void _free_matrixes_if_root(sqmatrix_t** matrix_a, sqmatrix_t** matrix_b,
                                   sqmatrix_t** matrix_c) {
  if (0 == rank) {
    free(*matrix_a);
    free(*matrix_b);
    free(*matrix_c);
  }
}

static void _send_matrix_by_rows(const sqmatrix_t* matrix, matvec_t* vec) {
  // MPI_Scatter(*matrix, MSIZE * MSIZE, MPI_INT, *vec, MSIZE, MPI_INT, 0,
  //             MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  sqmatrix_t *matrix_a, *matrix_b, *matrix_c;
  _init_matrixes_if_root(&matrix_a, &matrix_b, &matrix_c);

  if (0 == rank) {
    _print_named_matrix("Matrix A", matrix_a);
    printf("\n");
    _print_named_matrix("Matrix B", matrix_b);
  }

  MPI_Comm cart_comm;
  _create_cart_comm(&cart_comm);

  matvec_t local_row = {0}, row = {0}, local_result = {0};
  _send_matrix_by_rows(matrix_a, &local_row);
  _send_matrix_by_rows(matrix_b, &row);

  _print_named_vector("local_row", &local_row);
  _print_named_vector("row", &row);

  _free_matrixes_if_root(&matrix_a, &matrix_b, &matrix_c);
  MPI_Finalize();
}
