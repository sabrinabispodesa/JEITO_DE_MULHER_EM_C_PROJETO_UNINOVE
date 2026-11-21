#include <stdio.h>
#include <string.h>
#include "cadastrar_produtos.h"
#include "util.h"
#include "structs.h"


int lista_de_produtos(struct produto prod[], int quantidade_de_produto){
    // {nome, preço, estoque}  -> ajuste o estoque de cada produto como quiser
    struct produto pro[] = {
        {"Shampoo Revitalizante 300ml",   45.90, 10},
        {"Condicionador Nutritivo 300ml", 49.90, 10},
        {"Máscara de Hidratação 250g",    75.50, 10},
        {"Creme de Pentear 200ml",        38.00, 10},
        {"Mousse Modelador 150ml",        55.00, 10},
        {"Óleo Reparador Argan 60ml",     54.00, 10}
    };

    int quantidade = sizeof(pro) / sizeof(pro[0]);
    if (quantidade_de_produto > quantidade){
       quantidade_de_produto =  quantidade;
    }

    for (int i = 0; i < quantidade_de_produto; i++){
        prod[i] = pro[i];
    }
    return quantidade_de_produto;

}

void mostrar_produtos(struct produto prod[], int quantidade_de_produto){
    printf("\n============================ LISTA DE PRODUTOS ============================\n");
    
    for(int i = 0; i < quantidade_de_produto; i++){
    printf("Produto %d - %s\n", i + 1, prod[i].nome);
    printf("Preço: R$%.2f\n", prod[i].preco);
    printf("Quantidade disponível no estoque: %d\n", prod[i].estoque);
    printf("\n");
}
}

void cadastrar_produto(struct produto p[], int *total, int capacidade){
    printf("\n============================ CADASTRAR PRODUTO ============================\n");

    int vagas = capacidade - *total;

    if (vagas <= 0){
        printf("\nNão há espaço para novos produtos!\n");
        return;
    }

    /* pedir_numero já repete a pergunta até o número estar entre 1 e vagas */
    int quantidade_a_cadastrar = pedir_numero("\nQuantos produtos deseja cadastrar? ", 1, vagas);
    limpar_buffer();   /* tira o Enter que sobrou, para o fgets do nome funcionar */

    for(int i = 0; i < quantidade_a_cadastrar; i++){
        int pos = *total;   /* próxima posição livre */

        printf("\nDigite o nome do produto %d: ", i + 1);
        fgets(p[pos].nome, sizeof(p[pos].nome), stdin);
        p[pos].nome[strcspn(p[pos].nome, "\n")] = '\0';

        printf("\nDigite o preço do produto %d: ", i + 1);
        scanf("%f", &p[pos].preco);
        limpar_buffer();

        do{
            printf("\nDigite a quantidade de %s disponível no estoque: ", p[pos].nome);
            scanf("%d", &p[pos].estoque);
            limpar_buffer();

            if (p[pos].estoque <= 0){
                printf("\nQuantidade inválida!\n");
            }
        } while (p[pos].estoque <= 0);

        (*total)++;   /* DENTRO do for, com parênteses: conta cada produto cadastrado */
    }
}

void imprimir_produtos(struct produto p[], int quantidade_de_produto){
    printf("\n============================ PRODUTOS CADASTRADOS ============================\n");
    for (int j = 0; j < quantidade_de_produto; j++){
        printf("\n%d - %s", j + 1, p[j].nome);
        printf(" | R$ %.2f", p[j].preco);
        printf(" | Estoque: %d", p[j].estoque);
    }
}

void salvar_produtos (struct produto p[], int total){
    FILE *arq = fopen(ARQUIVO_PRODUTOS, "w");
    if(arq == NULL){
        printf("\nErro ao salvar os produtos!\n");
        return;
    }

    for (int i = 0; i < total; i++){
        fprintf(arq, "%s;%.2f;%d\n", p[i].nome, p[i].preco, p[i].estoque);
    }
    fclose(arq);
}

int carregar_produtos(struct produto p[], int quantidade_de_produto){
    FILE *arq = fopen(ARQUIVO_PRODUTOS, "r");
    if(arq == NULL){
        return 0;
    }

    int total = 0;
    while (total < quantidade_de_produto && fscanf(arq, " %39[^;];%f;%d", p[total].nome, &p[total].preco, &p[total].estoque) == 3){
        total++;
    }
    fclose(arq);
    return total;
}

void remover_produtos(struct produto p[], int *total){
     printf("\n============================ REMOVER PRODUTO ============================\n");

    if (*total == 0){
        printf("\nNão há produtos para remover!\n");
        return;
    }

    /* mostra os produtos com o número de cada um */
    for (int i = 0; i < *total; i++){
        printf("\n%d - %s | R$%.2f | Estoque: %d", i + 1, p[i].nome, p[i].preco, p[i].estoque);
    }
    printf("\n");

    int escolha = pedir_numero("\nQual produto deseja remover? (0 - CANCELAR) ", 0, *total);
    limpar_buffer();

    if (escolha == 0){
        printf("\nOperação cancelada.\n");
        return;
    }

    int pos = escolha - 1;   /* posição no array (começa em 0) */

    /* "puxa" cada produto seguinte uma posição para trás, cobrindo o removido */
    for (int i = pos; i < *total - 1; i++){
        p[i] = p[i + 1];
    }

    (*total)--;   /* agora existe um produto a menos */
    printf("\nProduto removido!\n");
}
