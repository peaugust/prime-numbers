#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

struct limites {
    int numero_limite_inferior;
    int numero_limite_superior;
    int index_da_thread;
};

bool num_eh_primo(int num) {
    // 0 nao eh primo
    // 1 nao eh primo
    // 2 eh o primeiro numero primo
    // se numero for par nao eh primo

    bool eh_primo = true;
    int i = 2;
    #pragma omp parallel
    while(i <= num / 2 && eh_primo)
    {
        eh_primo = !(num % i == 0);
        i++;
    }
    return eh_primo;
}

void verifica_limites(struct limites limites) {
    int numero_limite_inferior = limites.numero_limite_inferior;
    int numero_limite_superior = limites.numero_limite_superior;
    int index_da_thread = limites.index_da_thread;

    #pragma omp parallel for
    for (int i = numero_limite_inferior; i <= numero_limite_superior; i++) {
        if (num_eh_primo(i)) {
            printf("%d \n", i);
        }
    }
}

int main(int argc, char *argv[]) {

    int numero_limite_superior = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    if (numero_limite_superior < 2) {
        printf("\n 0 e 1 nao sao numeros primos");
        return 0;
    } else if (num_threads > numero_limite_superior) {
        printf("\n Escolha um numero de threads menor do que o numero limite");
        return 0;
    } else {
        int qtd_num_por_thread = numero_limite_superior / num_threads;
        int numero_limite_inferior = 2;
        int numero_limite_superior = qtd_num_por_thread;
        struct limites arguments[num_threads];
        // Nao posso usar o omp aqui, pois como atualizo numero_limite_inferior e superior acabo criando uma regiao critica que gera um gargalo de execucao
        for(int i = 0; i < num_threads; i++) {
            arguments[i].numero_limite_inferior = numero_limite_inferior;
            arguments[i].numero_limite_superior = numero_limite_superior;
            arguments[i].index_da_thread = i;
            verifica_limites(arguments[i]);
            numero_limite_inferior = numero_limite_superior+1;
            numero_limite_superior = numero_limite_superior + qtd_num_por_thread;
        }
    }  
}