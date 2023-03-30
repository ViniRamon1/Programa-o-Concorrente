#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

double *gerar_vetor(int n);
void mostrar_vetor(float *v,int tamanho);

int main() {

    int MAX = 500000000;
    time_t t;
    srand(time(NULL));
    double *vetor = NULL;
    vetor = gerar_vetor(MAX);
    int i;
    double soma = 0.0;
    double inicio,fim;

    inicio = omp_get_wtime();
    for (i=0;i<MAX;i++) {
        soma = soma + vetor[i];
        
    }
    fim = omp_get_wtime();
    double media = soma/MAX;
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double temposeq = fim-inicio;
    printf("Tempo sequencial: %lf\n",temposeq);

    soma = 0;
    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
            for (i=0;i<MAX;i++) {
                soma = soma + vetor[i];
            }
    }
    fim = omp_get_wtime();
    media = soma/MAX;
    printf("Soma: %lf\n",soma);
    printf("Media: %lf\n",media);
    double tempoparalelo = fim-inicio;
    printf("Tempo paralelo: %.4f\n",tempoparalelo);
    double speedup = temposeq/tempoparalelo;
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiencia: %f\n",eficiencia);
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i, valor = 100000;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() % valor);
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
