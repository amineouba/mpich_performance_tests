#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

const int NUM_OF_MSGS = 8;
const int NUM_TESTS = 10;

int main(int argc, char** argv) {
    int rank, size;
    int* send_data;
    int* recv_data;
    int message_size;
    double execution_time;
    int message_sizes[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
    double* execution_times;
    clock_t start_t, end_t;
    int* recvcounts;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    execution_times = (double*)malloc(NUM_OF_MSGS * sizeof(double));
    recvcounts = (int*)malloc(size*sizeof(int));

    for (int i = 0; i < NUM_OF_MSGS; i++) {
        message_size = message_sizes[i];
        execution_time = 0;
        for(int j=0; j<size; j++) {
          recvcounts[j] = message_size/size;
          if (j < message_size % size)
            recvcounts[j]++;
        }
        for (int j = 0; j < NUM_TESTS; j++) {   
            send_data = (int*)malloc(size * message_size * sizeof(int));
            recv_data = (int*)malloc(message_size * sizeof(int));

            MPI_Barrier(MPI_COMM_WORLD);
            start_t = clock();
            MPI_Reduce_scatter(send_data, recv_data, recvcounts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
            end_t = clock();

            execution_time += (double)(end_t - start_t) * 1000 / CLOCKS_PER_SEC;
            free(send_data);
            free(recv_data);
        }
        execution_times[i] = execution_time / NUM_TESTS;
    }

    if (rank == 0) {
        printf("{ ");
        for (int i = 0; i < NUM_OF_MSGS; i++) {
            printf("%d: %f, ", message_sizes[i], execution_times[i]);
        }
        printf("}\n");
    }

    free(execution_times);
    free(recvcounts);
    MPI_Finalize();
    return 0;
}