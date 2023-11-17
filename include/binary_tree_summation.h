#ifndef BINARY_TREE_SUMMATION_H_
#define BINARY_TREE_SUMMATION_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This header file exposes functions for binary tree summation for use in C programs */

typedef void * ReductionContext;


/* TODO: remove void * type and replace with MPI_Comm. Requires MPI inclusion in every source file that includes
 * this header, so we avoid it here
 */
void set_default_reduction_context_communicator(void *communicator);
ReductionContext new_reduction_context(int global_start_idx, int local_summands);
ReductionContext new_reduction_context_comm(int global_start_idx, int local_summands, void *communicator);
void store_summand(ReductionContext context, uint64_t local_idx, double val);
double reproducible_reduce(ReductionContext);
double *get_reduction_buffer(ReductionContext ctx);
void free_reduction_context(ReductionContext);

#ifdef __cplusplus
}
#endif

#endif
