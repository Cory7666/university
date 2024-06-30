#include <math.h>
#include <mpi.h>
#include <stdio.h>

static double f(double x) { return exp(x); }

static double _calc_partial_sum(double start, double step) {
  return f(start + step / 2) * step;
}

static void _do_job(int size, int rank) {
  double range[2] = {0}, result = 0;

  if (0 == rank) {
    range[0] = 2;
    range[1] = 3;
  }

  MPI_Bcast(range, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  const double step = (range[1] - range[0]) / size,
               local_start = range[0] + rank * step,
               local_stop = local_start + step;

  const double local_result = _calc_partial_sum(local_start, step);
  printf("Proc%d: In range {%lf, %lf} part sum == %lf\n", rank, local_start,
         local_stop, local_result);

  MPI_Reduce(&local_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (0 == rank) {
    printf("Proc%d: Result is %lf\n", rank, result);
  }
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  _do_job(size, rank);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
