#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define x 1000

int main(){
    MPI_Init(NULL, NULL);
    
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        time_t t;
        srand((unsigned) time(&t));
        int vetor[x], i, soma = 0, soma_dobro = 0;
        for (i = 0; i < x; i++) {
            vetor[i] = (rand() % x);
        }
        MPI_Bcast(vetor, x, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Recv(&soma, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&soma_dobro, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Soma: %d\n", soma);
        printf("Soma dobro: %d\n", soma_dobro);
    }
    if(rank == 1){
        int vetor[x], i, soma = 0;
        MPI_Bcast(vetor, x, MPI_INT, 0, MPI_COMM_WORLD);
        for(i = 0; i < x; i++){
            soma+=vetor[i];
        }
        MPI_Send(&soma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if(rank == 2){
        int vetor[x], i, soma = 0;
        MPI_Bcast(vetor, x, MPI_INT, 0, MPI_COMM_WORLD);
        for(i = 0; i < x; i++){
            soma+=vetor[i] * 2;
        }
        MPI_Send(&soma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    return 0;
}
