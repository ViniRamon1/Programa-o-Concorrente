#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000

int main() {
    float *x;
    float u = 0.0, var = 0.0, std_dev = 0.0;
    int i;

    // Alocando o vetor de floats
    x = (float*) malloc(N * sizeof(float));

    // Inicializando o vetor com valores aleatórios entre 0 e 1
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        x[i] = (float) rand() / RAND_MAX;
    }

    // Calculando a esperança (u)
    #pragma omp parallel for reduction(+:u)
    for (i = 0; i < N; i++) {
        u += x[i];
    }
    u /= N;

    // Calculando a variância (var)
    #pragma omp parallel for reduction(+:var)
    for (i = 0; i < N; i++) {
        var += (x[i] - u) * (x[i] - u);
    }
    var /= N;

    // Calculando o desvio padrão (std_dev)
    std_dev = sqrt(var);

    // Imprimindo o resultado
    printf("Desvio padrao = %f\n", std_dev);

    // Liberando a memória alocada
    free(x);

    return 0;
}
