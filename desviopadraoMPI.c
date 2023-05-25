#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Definir o conjunto de valores
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int num_elements = sizeof(data) / sizeof(data[0]);

        // Dividir o conjunto em partes iguais para cada processo
        int elements_per_process = num_elements / size;

        // Enviar partes do conjunto para os demais processos
        MPI_Scatter(data, elements_per_process, MPI_INT, MPI_IN_PLACE, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        // Receber parte do conjunto do processo mestre
        int elements_per_process;
        MPI_Scatter(NULL, 0, MPI_INT, data, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Calcular a média local dos valores
    int elements_per_process;
    double sum = 0.0;
    for (int i = 0; i < elements_per_process; i++) {
        sum += data[i];
    }
    double local_mean = sum / elements_per_process;

    // Calcular a soma das diferenças ao quadrado entre cada valor e a média local
    double sum_diff_squared = 0.0;
    for (int i = 0; i < elements_per_process; i++) {
        double diff = data[i] - local_mean;
        sum_diff_squared += diff * diff;
    }

    // Reduzir a soma das diferenças ao quadrado em todos os processos
    double global_sum_diff_squared = 0.0;
    MPI_Reduce(&sum_diff_squared, &global_sum_diff_squared, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Calcular o desvio padrão global no processo mestre e exibir o resultado
        int num_elements;
        double global_variance = global_sum_diff_squared / num_elements;
        double global_stddev = sqrt(global_variance);
        printf("Desvio padrão: %lf\n", global_stddev);
    }

    MPI_Finalize();
    return 0;
}
