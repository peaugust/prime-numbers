// The C library function int atoi(const char *str) converts the string argument str to an integer (type int)
// The C library function void *malloc(size_t size) allocates the requested memory and returns a pointer to it
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int main(int argc, char *argv[]) {

    int numero_limite_superior = atoi(argv[1]);
    if (numero_limite_superior < 2) {
        printf("\n 0 e 1 nao sao numeros primos");
        return 0;
    }
    
    int resultado[numero_limite_superior];
    for (int i = 2; i <= numero_limite_superior; i++) {
        if (num_eh_primo(i)) {
            resultado[i] = i;
        } else {
            resultado[i] = 0;
        }
    }

    printf("Sao numeros primos: \n");

    for (int i = 2; i <= numero_limite_superior; i++) {
        if(resultado[i] != 0){
            printf("%d \n", resultado[i]);
        }
    }   
}