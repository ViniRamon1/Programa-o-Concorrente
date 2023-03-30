#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define num_passos 300000000

int main() {

    double passo;
    int i; double x, pi, sum = 0.0;
    int t = omp_get_num_threads();

    double inicio = omp_get_wtime();
    passo = 1.0/(double) num_passos;
    for (i=0;i< num_passos; i++){
        x = (i + 0.5) * passo; 
        sum = sum + 4.0 / (1.0 + x*x); 
    }
    pi = passo * sum;
    double fim = omp_get_wtime();
    double temposeq = fim-inicio;
    printf("%f\n",pi);
    printf("Execucao sequencial: %f\n",temposeq);

    x = 0;
    pi = 0;
    sum = 0;
    inicio = omp_get_wtime();
    passo = 1.0/(double)num_passos;
    #pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction (+:sum)
        for (i=0; i< num_passos; i++){
            x = (i + 0.5) * passo; 
            sum = sum + 4.0 / (1.0 + x*x); 
        }
    }
    pi = passo * sum;
    fim = omp_get_wtime();
    double tempoparalelo = fim-inicio;
    double speedup = temposeq/tempoparalelo;
    printf("Pi: %f\n",pi);
    printf("Execucao paralela: %f\n",tempoparalelo);
    printf("Speedup: %.4f\n", speedup);
    printf("Eficiencia: %.4f\n",speedup/3.0);
    return 0;
}
