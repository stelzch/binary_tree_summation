#include "allreduce_summation.hpp"
#include <numeric>

AllreduceSummation::AllreduceSummation(MPI_Comm comm, size_t local_summands)
    : local_summands(local_summands), comm(comm), buffer(local_summands) {

  MPI_Comm_rank(comm, &rank);
}

AllreduceSummation::~AllreduceSummation() {}

double *AllreduceSummation::getBuffer() { return buffer.data(); }

double AllreduceSummation::accumulate() {
  auto local_sum =
      std::reduce(buffer.begin(), buffer.end(), 0.0, std::plus<double>());

  // Reducation across communicator
  double sum;
  MPI_Allreduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, comm);

  return sum;
}
