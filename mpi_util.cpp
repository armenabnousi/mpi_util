#include "mpi_util.h"

void MpiUtil::broadcast_char_array(char** array, int* array_size, int root) {
	int me;
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	MPI_Bcast(array_size, 1, MPI_INT, root, MPI_COMM_WORLD);
	if (me != root) {
		*array = new char[*array_size];
	}
	MPI_Bcast(&(*array)[0], *array_size, MPI_CHAR, root, MPI_COMM_WORLD);
}

void MpiUtil::gatherv_char_array(char* local_input, int local_input_size, char** output, int* output_size, int root) {
	int nproc, me;
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	int local_sizes[nproc];
	int displacements[nproc];
	MPI_Gather(&local_input_size, 1, MPI_INT, local_sizes, 1, MPI_INT, root, MPI_COMM_WORLD);
	*output_size = 0;
	if (me == root) {
		for (int i = 0; i < nproc; i++) {
			displacements[i] = *output_size;
			*output_size += local_sizes[i];
		}
	}
	*output = new char[*output_size];
	MPI_Gatherv(local_input, local_input_size, MPI_CHAR, &(*output)[0], local_sizes, displacements, MPI_CHAR, root, MPI_COMM_WORLD);
}
