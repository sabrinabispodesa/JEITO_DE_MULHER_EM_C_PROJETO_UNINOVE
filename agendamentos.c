/*
 * agendamentos.c
 * Agendamento de serviços: mostra os horários, deixa o cliente escolher
 * produtos e faz o agendamento completo com resumo e valor total.
 */

#include <stdio.h>
#include <string.h>
#include "agendamento.h"
#include "cadastrar_servico.h"
#include "cadastrar_funcionario.h"
#include "util.h"

// Preenche e mostra os dias da semana (segunda a sexta) e os 7 horários de cada dia.
void horarios_disponiveis(struct agendamento *a) {
    printf("\n============================ HORÁRIOS DISPONÍVEIS ============================\n");

    const char *dias_da_semana[] = {"Segunda - feira", "Terça - feira", "Quarta - feira", "Quinta - feira", "Sexta - feira"};
    const char *horarios[] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00"};

    // Copia os textos para a struct (strncpy evita ultrapassar o tamanho do campo)
    for (int i = 0; i < 5; i++) {
        strncpy(a->dia_da_semana[i], dias_da_semana[i], sizeof(a->dia_da_semana[i]) - 1);
        a->dia_da_semana[i][sizeof(a->dia_da_semana[i]) - 1] = '\0';

        for (int l = 0; l < 7; l++) {
            strncpy(a->horario[l], horarios[l], sizeof(a->horario[l]) - 1);
            a->horario[l][sizeof(a->horario[l]) - 1] = '\0';
        }
    }

    // Mostra cada dia com a lista de horários
    for (int k = 0; k < 5; k++) {
        printf("\n\nDia: %s", a->dia_da_semana[k]);

        for (int j = 0; j < 7; j++) {
            printf("\nHorário %d: %s", j + 1, a->horario[j]);
        }
    }
}

// Pergunta UMA vez se o cliente quer produtos, deixa escolher
// e devolve o valor total dos produtos.
// O estoque é descontado conforme os produtos são escolhidos.
float escolher_produtos(struct produto prod[], int quantidade_de_produto, struct agendar_horario_fazer_compra *compra) {
    int sim_nao2;
    int escolher_produto;
    int quantidade_produto;
    float total_produtos = 0;

    compra->total_produtos = 0;   // o carrinho começa vazio

    sim_nao2 = pedir_numero("\nDeseja adicionar produto?\n1 - SIM\n2 - NÃO\n---> ", 1, 2);
    if (sim_nao2 == 2) {
        return 0;
    }

    // Mostra os produtos disponíveis
    printf("\n============================ Escolha o Produto ============================\n");
    for (int d = 0; d < quantidade_de_produto; d++) {
        printf("\n%d - Produto: %s", d + 1, prod[d].nome);
        printf("\n     Preço: R$%.2f", prod[d].preco);
        printf("\n     Estoque: %d\n", prod[d].estoque);
    }

    // Repete até o cliente escolher 0 (sair)
    do {
        escolher_produto = pedir_numero("\nEscolha produto (0 - SAIR): ", 0, quantidade_de_produto);

        if (escolher_produto == 0) {
            break;
        }

        printf("\nDigite a quantidade que você deseja comprar: ");
        scanf("%d", &quantidade_produto);

        // Não aceita quantidade menor que 1 nem maior que o estoque
        if (quantidade_produto < 1 || quantidade_produto > prod[escolher_produto - 1].estoque) {
            printf("\nQuantidade inválida ou maior que o estoque!\n");
            continue;
        }

        // O carrinho tem no máximo 10 unidades
        if (quantidade_produto + compra->total_produtos > 10) {
            printf("\nLimite de 10 unidades de produtos por agendamento!\n");
            continue;
        }

        // Coloca cada unidade no carrinho
        for (int a = 0; a < quantidade_produto; a++) {
            compra->produto[compra->total_produtos] = prod[escolher_produto - 1];
            compra->total_produtos++;
        }

        // Soma o valor e desconta do estoque
        total_produtos += prod[escolher_produto - 1].preco * quantidade_produto;
        prod[escolher_produto - 1].estoque = prod[escolher_produto - 1].estoque - quantidade_produto;
        printf("\nProduto adicionado!\n");
    } while (escolher_produto != 0);

    return total_produtos;
}

// Faz o agendamento completo. Para cada serviço pedido:
//   1) escolhe o serviço
//   2) escolhe um profissional que o realiza
//   3) escolhe dia e horário livres
// No final, pergunta pelos produtos e mostra o resumo com o total estimado.
void agendar_servico_para_cliente(struct servico serv[], int quantidade_de_servico, struct profissional p[], int quantida_profissional, struct produto prod[], int quantidade_de_produto) {
    printf("\n============================ AGENDAMENTO ============================\n");
    char nome_cliente[30];
    int quantos_servicos;
    int servicos_agendados = 0;
    float total = 0;
    float total_produtos = 0;
    struct agendamento ag;
    struct agendar_horario_fazer_compra compra;   // carrinho de produtos deste cliente

    // guardam o que foi escolhido em cada serviço, para mostrar no resumo
    struct servico servicos_escolhidos[10];
    int profissional_escolhido[10];
    int dia_escolhido[10];
    int horario_escolhido[10];

    getchar();
    printf("\nDigite o nome do(a) cliente: ");
    fgets(nome_cliente, sizeof(nome_cliente), stdin);
    nome_cliente[strcspn(nome_cliente, "\n")] = '\0';

    quantos_servicos = pedir_numero("\nQuantos serviços deseja realizar? (1 - 10) ", 1, 10);

    for (int n = 0; n < quantos_servicos; n++) {
        int escolher_servico;
        int total_profissional = 0;
        int profissionais_que_realizam_servico[10];
        int escolher_profissional;
        int escolher_dia;
        int escolher_horario;

        // ----- 1) escolher o serviço -----
        printf("\n============================ Escolha o Serviço %d ============================\n", n + 1);
        mostrar_servicos(serv, quantidade_de_servico);

        // Repete até escolher um serviço que tenha profissional (ou 0 para sair)
        do {
            escolher_servico = pedir_numero("\nDigite o número do serviço escolhido (0 para sair): ", 0, quantidade_de_servico);
            if (escolher_servico == 0) {
                break;
            }
            total_profissional = buscar_profissionais(p, quantida_profissional, serv[escolher_servico - 1], profissionais_que_realizam_servico);
            if (total_profissional == 0) {
                printf("\nNão há profissionais cadastrados para esse serviço.\n");
            }
        } while (total_profissional == 0);

        if (escolher_servico == 0) {
            break;
        }

        // ----- 2) escolher o profissional -----
        printf("\nEscolha o profissional que irá realizar esse serviço:\n");
        for (int k = 0; k < total_profissional; k++) {
            int indice = profissionais_que_realizam_servico[k];
            printf("\n%d - %s", k + 1, p[indice].nome_profissional);
        }
        escolher_profissional = pedir_numero("\n\nEscolha profissional: ", 1, total_profissional);
        int m = profissionais_que_realizam_servico[escolher_profissional - 1];   // posição do profissional escolhido

        // ----- 3) escolher dia e horário (só aceita horário livre) -----
        horarios_disponiveis(&ag);
        do {
            escolher_dia = pedir_numero("\nEscolher dia (1 - 5): ", 1, 5);
            escolher_horario = pedir_numero("\nEscolha o horário (1 - 7): ", 1, 7);

            if (p[m].disponivel[escolher_dia - 1][escolher_horario - 1] == 0) {
                printf("\nEsse horário já está ocupado, escolha outro!\n");
            }
        } while (p[m].disponivel[escolher_dia - 1][escolher_horario - 1] == 0);

        p[m].disponivel[escolher_dia - 1][escolher_horario - 1] = 0;   // agora o horário fica ocupado

        // ----- 4) guardar o que foi escolhido -----
        servicos_escolhidos[servicos_agendados] = serv[escolher_servico - 1];
        profissional_escolhido[servicos_agendados] = m;
        dia_escolhido[servicos_agendados] = escolher_dia - 1;
        horario_escolhido[servicos_agendados] = escolher_horario - 1;
        total += serv[escolher_servico - 1].preco;
        servicos_agendados++;
    }

    // ----- Fora do for: produtos e resumo acontecem só UMA vez -----
    if (servicos_agendados > 0) {
        total_produtos = escolher_produtos(prod, quantidade_de_produto, &compra);
        total += total_produtos;

        // Resumo do agendamento
        printf("\n============================ AGENDAMENTO ============================");

        for (int h = 0; h < servicos_agendados; h++) {
            printf("\n%d - %s", h + 1, servicos_escolhidos[h].nome_servico);
            printf("\nAgendado com %s", p[profissional_escolhido[h]].nome_profissional);
            printf("\nDia: %s | Horário: %s", ag.dia_da_semana[dia_escolhido[h]], ag.horario[horario_escolhido[h]]);
            printf("\nDuração: %s | a partir de R$%.2f\n", servicos_escolhidos[h].duracao, servicos_escolhidos[h].preco);
        }

        if (compra.total_produtos > 0) {
            printf("\nLista de produtos escolhidos:");
            for (int f = 0; f < compra.total_produtos; f++) {
                printf("\n%d - %s", f + 1, compra.produto[f].nome);
                printf(" | R$%.2f", compra.produto[f].preco);
            }
            printf("\nValor total dos produtos: R$%.2f", total_produtos);
        } else {
            printf("\nNenhum produto adicionado.");
        }

        printf("\nTotal estimado (serviços a partir de + produtos): R$%.2f", total);
        printf("\nAgendamento de %s finalizado!\n", nome_cliente);
    } else {
        printf("\nNenhum serviço foi agendado.\n");
    }
}
