/*
 * utils.c
 * Funções de apoio usadas em várias partes do programa.
 */

#include <stdio.h>
#include <string.h>
#include "util.h"
#include "structs.h"

// Lê e descarta os caracteres do teclado até o fim da linha.
// Evita que um '\n' sobrando faça o próximo fgets "pular" a pergunta.
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Mostra a mensagem e lê um número inteiro.
// Enquanto o número estiver fora do intervalo [minimo, maximo], avisa e pergunta de novo.
int pedir_numero(const char *mensagem, int minimo, int maximo) {
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
