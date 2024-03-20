#include <mpi.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "matrix.h"

typedef enum {
  PROCESS_READ = 0,
  PROCESS_MINORS,
  PROCESS_PRINT_RESULT,
  PROCESS_MAX
} mpi_proc_t;

void matrix_mpi_send(const matrix_t matrix, int32_t dest) {
  MPI_Send((const void*)matrix, 9, MPI_DOUBLE, dest, 11, MPI_COMM_WORLD);
}

void matrix_mpi_recv(matrix_t matrix, int32_t src) {
  MPI_Recv((void*)matrix, 9, MPI_DOUBLE, src, 11, MPI_COMM_WORLD, NULL);
}

int main(int argc, char** argv) {
  int rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  switch (rank) {
    case PROCESS_READ: {
      matrix_t matrix;
      FILE* file = stdin;
      puts("Read matrix from user.");
      matrix_init_from_file(file, matrix);
      matrix_print_named("input", matrix);
      matrix_mpi_send(matrix, PROCESS_MINORS);
      break;
    }

    case PROCESS_MINORS: {
      matrix_t input, minors;
      matrix_mpi_recv(input, PROCESS_READ);
      matrix_mpi_send(input, PROCESS_PRINT_RESULT);
      matrix_calculate_minor_matrix(minors, input);
      matrix_print_named("minors", minors);
      matrix_mpi_send(minors, PROCESS_PRINT_RESULT);
      break;
    }

    case PROCESS_PRINT_RESULT: {
      matrix_t input, minors;
      matrix_mpi_recv(input, PROCESS_MINORS);
      const elem_t determinant = matrix_calculate_determinant(input);
      matrix_mpi_recv(minors, PROCESS_MINORS);
      matrix_calculate_inverse_matrix(minors, determinant);
      matrix_make_algebr_addit(minors);
      matrix_transpose(minors);
      matrix_print_named("inverse matrix", minors);
      break;
    }

    default:
      break;
  }

  printf("%d is waiting at barrier.\n", rank);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
