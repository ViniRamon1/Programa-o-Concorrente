#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

float *gera_vetor(int n);

int main()
{
    // Iniciando mpi.h
    int nprocs, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    // Iniciando time.h
    time_t t;
    srand(time(NULL) * rank);

    /*
    INICIO
    */

    /*
    FIM
    */

    MPI_Finalize();
    return 0;
}

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}
