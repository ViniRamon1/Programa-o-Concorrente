#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAMANHO 100000000
#define MAX 1000000

int main() {
    time_t t;
    srand((unsigned) time(&t));
    long int *vetor;
    vetor = (long int*)malloc(TAMANHO * sizeof(long int));
    int i;
    int maior;
    long int indiceSerial, indiceParalelo;
    for(i = 0; i < TAMANHO; i++) {
        int num = 1 + (rand() % MAX);
        vetor[i] = num;
    }

    // Execução Serial
    maior = 0;
    double inicio = omp_get_wtime();
    for(i = 0; i < TAMANHO; i++) {
        if(vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    double fim = omp_get_wtime();
    double tSerial = fim - inicio;
    printf("Execucao Sequencial: %f\n", tSerial);
    printf("Maior valor encontrado: %d\n", maior);
    
    //Execução Paralela
    maior = 0;
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {   
        #pragma omp for 
            for(i = 0; i < TAMANHO; i++) {
                if(vetor[i] > maior) {
                    maior = vetor[i];
                }
            }
    }
    fim = omp_get_wtime();
    double tParalelo = fim - inicio;
    double speedup = tSerial/tParalelo;
    printf("Execucao paralela: %f\n",tParalelo);
    printf("Maior valor encontrado: %d\n", maior);
    printf("Speedup: %f\n", speedup);
    printf("Eficiencia: %f\n",speedup/4.0);
    return 0;
}