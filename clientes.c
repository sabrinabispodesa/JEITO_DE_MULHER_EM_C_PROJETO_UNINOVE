/*
 * clientes.c
 * Cadastro de clientes. Os dados ficam só na memória (não são salvos em arquivo).
 */

#include <stdio.h>
#include <string.h>
#include "cadastrar_clientee.h"
#include "structs.h"

void cadastrar_cliente(struct cliente cli[], int quantidade_de_cliente) {
    printf("\n============================ CADASTRAR CLIENTE ============================\n");

    printf("\nQuantos clientes deseja cadastrar? (1 - 10) ");
    scanf("%d", &quantidade_de_cliente);

    // Só aceita de 1 a 10 clientes por vez
    if (quantidade_de_cliente > 10 || quantidade_de_cliente < 1) {
        printf("\nOpção Inválida!!!");
    }
    else {
        getchar();   // limpa o '\n' que o scanf deixou

        // Pede nome, telefone e e-mail de cada cliente
        for (int i = 0; i < quantidade_de_cliente; i++) {
            printf("\nDigite o nome do(a) cliente %d: ", i + 1);
            fgets(cli[i].nome, sizeof(cli[i].nome), stdin);
            cli[i].nome[strcspn(cli[i].nome, "\n")] = '\0';   // tira o '\n' do final

            printf("\nNúmero de telefone (só números, com DDD): ");
            fgets(cli[i].telefone, sizeof(cli[i].telefone), stdin);
            cli[i].telefone[strcspn(cli[i].telefone, "\n")] = '\0';
            // o getchar() que ficava aqui foi removido: agora o fgets já lê a linha inteira

            printf("\nE-mail: ");
            fgets(cli[i].email, sizeof(cli[i].email), stdin);
            cli[i].email[strcspn(cli[i].email, "\n")] = '\0';
        }

        printf("\n============================ CLIENTE CADASTRADOS ============================\n");

        // Mostra os clientes cadastrados, com o telefone no formato (DD)NNNNN-NNNN
        for (int k = 0; k < quantidade_de_cliente; k++) {
            printf("\nCliente %d\n", k + 1);
            printf("      Nome: %s\n", cli[k].nome);
            printf("      Telefone: (%c%c)%c%c%c%c%c-%c%c%c%c\n",
                   cli[k].telefone[0], cli[k].telefone[1],
                   cli[k].telefone[2], cli[k].telefone[3], cli[k].telefone[4],
                   cli[k].telefone[5], cli[k].telefone[6],
                   cli[k].telefone[7], cli[k].telefone[8], cli[k].telefone[9],
                   cli[k].telefone[10]);
            printf("      E-mail: %s\n", cli[k].email);
        }
    }
}
