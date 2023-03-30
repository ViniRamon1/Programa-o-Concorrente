#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500000000

float *gerar_vetor(int n);
void mostrar_vetor(float *v,int tamanho);

int main() {
    int i; 
    float soma;
    float media;
    time_t t;
    srand(time(NULL));
    double inicio = omp_get_wtime();
    float *vetor = malloc(MAX*sizeof(float));
    vetor = gerar_vetor(MAX);
    //mostrar_vetor(vetor, MAX);

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction(+:soma) 
            for(i = 0; i < MAX; i++){
                soma = soma + vetor[i];
            }
    }
    media = soma/(float)MAX;
    double fim = omp_get_wtime();
    double t_paralelo = fim-inicio;
    printf("soma: %d\n", soma);
    printf("media: %d\n", media);
    printf("Execucao paralela sequencial: %f\n",t_paralelo);


    float somaP;
    float mediaP;
    double inicioParalelo = omp_get_wtime();
    float *vetor1 = malloc(MAX*sizeof(float));
    vetor1 = gerar_vetor(MAX);
    //mostrar_vetor(vetor1, MAX);
    for(i = 0; i < MAX; i++){
        somaP = somaP + vetor1[i];
    }
    mediaP = somaP/(float)MAX;
    double fimParalelo = omp_get_wtime();
    double t_serial = fimParalelo-inicioParalelo;
    float speedup = (t_serial - t_paralelo);
    printf("soma serial: %d\n", somaP);
    printf("media serial: %d\n", mediaP);
    printf("Execucao serial: %f\n",t_serial);
    printf("speedup: %f\n", speedup);
    printf("eficiencia: %f\n", (speedup/3));
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        int num = (rand()%100000);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}