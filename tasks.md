# OpenMP Tasks

OpenMP (Open Multi-Processing) é uma API de programação paralela que suporta programação multi-plataforma em C, C++ e Fortran. Uma das principais características do OpenMP é a capacidade de dividir um grande problema em tarefas menores, que podem ser executadas em paralelo. O OpenMP fornece duas formas principais de executar tarefas paralelas: através de `sections` ou através de `tasks`.

## O que são OpenMP Tasks

As `tasks` são blocos de código que podem ser executados de fora de sincronia em relação ao restante do código. O OpenMP permite que os programadores criem tarefas em qualquer lugar do código e as executem em paralelo. Isso é especialmente útil quando se tem muitas tarefas pequenas e independentes que podem ser executadas em paralelo.

## Como utilizar OpenMP Tasks

Para usar OpenMP Tasks, é necessário habilitar a diretiva `omp task` e o bloco de código dentro da diretiva `omp parallel`. O código dentro da diretiva `omp task` é a tarefa a ser executada em paralelo. A diretiva `omp taskwait` é usada para garantir que todas as tarefas tenham sido concluídas antes que a execução continue.

Exemplo:

```
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                printf("Tarefa 1 executada pelo thread %d\n", omp_get_thread_num());
            }
            #pragma omp task
            {
                printf("Tarefa 2 executada pelo thread %d\n", omp_get_thread_num());
            }
        }
    }
    return 0;
}
```

Este código define duas tarefas para serem executadas em paralelo e aguardar a conclusão delas com a diretiva `omp taskwait`. O bloco `single` garante que apenas um thread mestre execute as tarefas. O `omp_get_thread_num()` é usado para obter o número do fio que está executando a tarefa.

## Diferença entre OpenMP Tasks e Sections

As `sections` permitem que os programadores dividam o código em seções independentes e os threads executem cada seção em paralelo. Por outro lado, as `tasks` permitem que os programadores dividam o código em tarefas independentes que podem ser executadas em paralelo. A principal diferença é que as `sections` executam todas as seções em todos os threads disponíveis, enquanto as `tasks` executam as tarefas de forma dinâmica, distribuindo as tarefas para os threads disponíveis.

## Quando utilizar OpenMP Tasks

As `tasks` são úteis quando se tem muitas tarefas independentes e não é possível prever o tempo de execução de cada tarefa. As `tasks` também podem ser usadas para equilibrar a carga em um sistema com vários processadores. Por exemplo, em um sistema com quatro processadores, pode-se criar quatro tarefas e distribuí-las entre os processadores.

Em geral, as `tasks` são mais flexíveis que as `sections` e permitem que o programador tenha mais controle sobre a execução paralela. No entanto, o uso de `tasks` também requer mais atenção ao gerenciamento de memória e ao controle de sincronização.

### Referências:
https://web.engr.oregonstate.edu/~mjb/cs575/Handouts/tasks.1pp.pdf
https://www.openmp.org/wp-content/uploads/openmp.webinar.22.09.2021.ruudvdp.pdf
