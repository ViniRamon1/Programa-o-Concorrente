#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    int i, qtd = 0;
    int x = 50;
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    //mostrar_vetor_inteiro(vetor, TAMANHO);

    //sequencial 
    double inicio = omp_get_wtime();
    for(i = 0; i < TAMANHO; i++){
        if(vetor[i] == x){
            qtd++;
        }
    }
    double fim = omp_get_wtime();
    double duracaosequencial = fim-inicio;
    printf("quantidade de ocorrencias sequencial: %d\n", qtd);
    printf("duracao sequencial: %f\n", duracaosequencial);

    //paralelo
    qtd = 0; 
    double inicioP = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for reduction ( + : qtd)
        for(i = 0; i < TAMANHO; i++){
            if(x == vetor[i]){
                qtd++;
            }
        }
    }
    double fimP = omp_get_wtime();
    double duracaoparalela = fimP-inicioP;
    printf("quantidade de ocorrencias paralela: %d\n", qtd);
    printf("duracao sequencial: %f\n", duracaoparalela);
    double speedup = duracaosequencial/duracaoparalela;
    printf("speedup: %f\n", speedup);
    printf("eficiencia: %f\n", speedup/4);
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}