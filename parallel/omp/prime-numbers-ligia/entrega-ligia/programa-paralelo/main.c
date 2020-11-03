#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

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
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void *verifica_limites(void *args) {
    struct limites *arguments = args;
    int numero_limite_inferior = arguments->numero_limite_inferior;
    int numero_limite_superior = arguments->numero_limite_superior;
    int index_da_thread = arguments->index_da_thread;

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
        pthread_t threads[num_threads]; 
        int qtd_num_por_thread = numero_limite_superior / num_threads;
        int numero_limite_inferior = 2;
        int numero_limite_superior = qtd_num_por_thread;

        // inicia as threads
        int rc;
        struct limites arguments[num_threads];
        
        for(int i = 0; i < num_threads; i++) {
            arguments[i].numero_limite_inferior = numero_limite_inferior;
            arguments[i].numero_limite_superior = numero_limite_superior;
            arguments[i].index_da_thread = i;
            // slides SO criacao de thread
            rc = pthread_create(&threads[i], NULL, verifica_limites, (void *)&arguments[i]);
            if (rc){
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }
            numero_limite_inferior = numero_limite_superior+1;
            numero_limite_superior = numero_limite_superior + qtd_num_por_thread;
        }
        for(int j=0; j<num_threads; j++){
            pthread_join(threads[j], NULL);
        }
    }  
}