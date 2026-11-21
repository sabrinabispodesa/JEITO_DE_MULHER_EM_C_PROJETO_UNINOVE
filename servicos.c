
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "util.h"
#include "cadastrar_servico.h"


int lista_de_servicos_oferecidos(struct servico serv[], int quantidade_de_servico){

    struct servico lista[] = {
        {"Corte Feminino", "Cortes", "1h", 90.00},
        {"Corte + Escova", "Cortes", "1h30", 130.00},
        {"Corte Infantil", "Cortes", "40min", 60.00},
        {"Franja e Acabamento", "Cortes", "20min", 35.00},
        {"Mechas Tradicionais", "Luzes", "3h", 280.00},
        {"Balayage", "Luzes", "4h", 450.00},
        {"Morena Iluminada", "Luzes", "4h", 520.00},
        {"Platinado", "Luzes", "5h", 600.00},
        {"Coloração Global", "Colorações", "2h", 180.00},
        {"Retoque de Raiz", "Colorações", "1h30", 120.00},
        {"Tonalização", "Colorações", "1h", 90.00},
        {"Coloração Fantasia", "Colorações", "3h", 250.00}
    };

    int quantidade = sizeof(lista) / sizeof(lista[0]);

    if (quantidade_de_servico > quantidade){
        quantidade_de_servico = quantidade;
    }

    for (int i = 0; i < quantidade_de_servico; i++){
        serv[i] = lista[i];
    }

    return quantidade_de_servico;
}


void mostrar_servicos(struct servico serv[], int quantidade_de_servico){

    printf("\n============================ LISTA DE SERVIÇOS ============================\n");

    for (int i = 0; i < quantidade_de_servico; i++){

        printf("\nServiço %d - %s\n", i + 1, serv[i].nome_servico);
        printf("Categoria: %s\n", serv[i].categoria);
        printf("Duração: %s\n", serv[i].duracao);
        printf("Preço: R$%.2f\n", serv[i].preco);
    }
}


void cadastrar_servico(struct servico s[], int *total, int capacidade){

    printf("\n============================ CADASTRAR SERVIÇO ============================\n");

    int vagas = capacidade - *total;

    if (vagas <= 0){
        printf("\nNão há espaço para novos serviços!\n");
        return;
    }

    int quantidade_a_cadastrar = pedir_numero(
        "\nQuantos serviços deseja cadastrar? ", 1, vagas
    );

    limpar_buffer();

    for (int i = 0; i < quantidade_a_cadastrar; i++){

        int pos = *total;

        printf("\nDigite o nome do serviço %d: ", i + 1);
        if (fgets(s[pos].nome_servico, sizeof(s[pos].nome_servico), stdin) == NULL){
            return;
        }
        s[pos].nome_servico[strcspn(s[pos].nome_servico, "\n")] = '\0';

        printf("\nDigite a categoria do serviço: ");
        if (fgets(s[pos].categoria, sizeof(s[pos].categoria), stdin) == NULL){
            return;
        }
        s[pos].categoria[strcspn(s[pos].categoria, "\n")] = '\0';

        printf("\nDigite a duração do serviço (Ex: 1h30): ");
        if (fgets(s[pos].duracao, sizeof(s[pos].duracao), stdin) == NULL){
            return;
        }
        s[pos].duracao[strcspn(s[pos].duracao, "\n")] = '\0';

        int preco_valido = 0;

        while (!preco_valido){

            printf("\nDigite o preço do serviço: ");

            if (scanf("%f", &s[pos].preco) == 1 && s[pos].preco > 0){
                preco_valido = 1;
            }
            else{
                printf("\nPreço inválido!\n");
            }

            limpar_buffer();
        }

        (*total)++;

        printf("\nServiço cadastrado com sucesso!\n");
    }
}


void imprimir_servicos(struct servico s[], int quantidade_de_servico){

    printf("\n============================ SERVIÇOS CADASTRADOS ============================\n");

    for (int i = 0; i < quantidade_de_servico; i++){

        printf("\n%d - %s", i + 1, s[i].nome_servico);
        printf(" | %s", s[i].categoria);
        printf(" | %s", s[i].duracao);
        printf(" | R$%.2f\n", s[i].preco);
    }
}


void salvar_servicos(struct servico s[], int total){

    FILE *arq = fopen(ARQUIVO_SERVICOS, "w");

    if (arq == NULL){
        printf("\nErro ao salvar os serviços!\n");
        return;
    }

    for (int i = 0; i < total; i++){

        fprintf(arq, "%s;%s;%s;%.2f\n",
                s[i].nome_servico,
                s[i].categoria,
                s[i].duracao,
                s[i].preco);
    }

    fclose(arq);
}


int carregar_servicos(struct servico s[], int quantidade_de_servico){

    FILE *arq = fopen(ARQUIVO_SERVICOS, "r");

    if (arq == NULL){
        return 0;
    }

    int total = 0;
    char linha[200];

    while (total < quantidade_de_servico && fgets(linha, sizeof(linha), arq)){

        if (sscanf(linha, " %29[^;];%19[^;];%9[^;];%f",
                   s[total].nome_servico,
                   s[total].categoria,
                   s[total].duracao,
                   &s[total].preco) == 4){

            total++;
        }
    }

    fclose(arq);

    return total;
}


void remover_servicos(struct servico s[], int *total){

    printf("\n============================ REMOVER SERVIÇO ============================\n");

    if (*total == 0){
        printf("\nNão há serviços para remover!\n");
        return;
    }

    for (int i = 0; i < *total; i++){

        printf("\n%d - %s | %s | %s | R$%.2f",
               i + 1,
               s[i].nome_servico,
               s[i].categoria,
               s[i].duracao,
               s[i].preco);
    }

    printf("\n");

    int escolha = pedir_numero(
        "\nQual serviço deseja remover? (0 - CANCELAR) ", 0, *total
    );

    if (escolha == 0){
        printf("\nOperação cancelada.\n");
        return;
    }

    int pos = escolha - 1;

    for (int i = pos; i < *total - 1; i++){
        s[i] = s[i + 1];
    }

    (*total)--;

    printf("\nServiço removido!\n");
}
