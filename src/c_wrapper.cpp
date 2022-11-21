#include <vector>
#include <mpi.h>
#include <binary_tree_summation.h>
#include <numeric>
#include "binary_tree.hpp"



ReductionContext new_reduction_context(int local_summands) {
    const MPI_Comm comm = MPI_COMM_WORLD;

    int size, rank;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    std::vector<int> n_summands;
    n_summands.resize(size);

    MPI_Allgather(&local_summands, 1, MPI_INT,
                  &n_summands[0], 1, MPI_INT,
                  comm);

    return new BinaryTreeSummation(rank, std::move(n_summands), comm);
}

double *get_reduction_buffer(ReductionContext ctx) {
    auto *ptr = static_cast<BinaryTreeSummation *>(ctx);

    return ptr->getBuffer();
}


double reproducible_reduce(ReductionContext ctx) {
    auto *ptr = static_cast<BinaryTreeSummation *>(ctx);

    return ptr->accumulate();
}

void free_reduction_context(ReductionContext ctx) {
    auto *ptr = static_cast<BinaryTreeSummation *>(ctx);

    delete ptr;
}
