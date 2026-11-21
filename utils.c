#include <stdio.h>
#include <string.h>
#include "util.h"
#include "structs.h"

void limpar_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int pedir_numero(const char *mensagem, int minimo, int maximo){
    int numero;
    do {
        printf("%s", mensagem);
        scanf("%d", &numero);
        if (numero < minimo || numero > maximo) {
            printf("\nOpção inválida!\n");
        }
    } while (numero < minimo || numero > maximo);
    return numero;
}
