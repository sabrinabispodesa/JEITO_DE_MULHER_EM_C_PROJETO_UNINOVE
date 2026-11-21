
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cadastrar_funcionario.h"
#include "cadastrar_servico.h"
#include "util.h"
#include "structs.h"


// ================= LIBERAR HORÁRIOS =================

void liberar_horarios(struct profissional *prof){

    for (int d = 0; d < 5; d++){
        for (int h = 0; h < 7; h++){
            prof->disponivel[d][h] = 1;
        }
    }
}


// ================= CADASTRAR PROFISSIONAL =================

int cadastrar_profissional(struct servico serv[],
                          int quantidade_de_servico,
                          struct profissional prof[],
                          int quantidade_de_profissionais){

    int quantidade_a_cadastrar;
    int escolha_sim_ou_nao;
    int escolha_servico;
    int inicio = quantidade_de_profissionais;

    int capacidade = 20;
    int vagas = capacidade - inicio;

    printf("\n============================ CADASTRAR PROFISSIONAL ============================\n");

    if (vagas <= 0){
        printf("\nNão há vagas disponíveis para novos profissionais!\n");
        return quantidade_de_profissionais;
    }

    printf("\nVagas disponíveis: %d\n", vagas);
    printf("\nQuantos profissionais deseja cadastrar? (1 - %d) ", vagas);

    if (scanf("%d", &quantidade_a_cadastrar) != 1){
        printf("\nDigite um número válido!\n");
        limpar_buffer();
        return quantidade_de_profissionais;
    }

    limpar_buffer();

    if (quantidade_a_cadastrar < 1 || quantidade_a_cadastrar > vagas){
        printf("\nQuantidade inválida! Vagas restantes: %d\n", vagas);
        return quantidade_de_profissionais;
    }


    // ================= CADASTRAR DADOS =================

    for (int i = inicio; i < inicio + quantidade_a_cadastrar; i++){

        prof[i].total_servico = 0;
        liberar_horarios(&prof[i]);

        printf("\n============================ NOVO PROFISSIONAL ============================\n");

        printf("\nDigite o nome do(a) profissional %d: ", i + 1);
        if (fgets(prof[i].nome_profissional,
                  sizeof(prof[i].nome_profissional), stdin) == NULL){
            return i;
        }

        if (strchr(prof[i].nome_profissional, '\n') == NULL){
            limpar_buffer();
        }

        prof[i].nome_profissional[
            strcspn(prof[i].nome_profissional, "\n")
        ] = '\0';


        // ================= CADASTRAR ID =================

        int id_repetido;

        do{
            id_repetido = 0;

            printf("\nDigite o ID do profissional: ");

            if (scanf("%d", &prof[i].id) != 1){
                prof[i].id = 0;
            }

            limpar_buffer();

            if (prof[i].id <= 0){
                printf("\nID inválido! Digite novamente.\n");
                id_repetido = 1;
            }
            else{
                for (int j = 0; j < i; j++){

                    if (prof[i].id == prof[j].id){
                        printf("\nEsse ID já está cadastrado!\n");
                        id_repetido = 1;
                        break;
                    }
                }
            }

        } while (id_repetido == 1);


        // ================= TELEFONE =================

        printf("\nNúmero de telefone: ");

        if (fgets(prof[i].telefone,
                  sizeof(prof[i].telefone), stdin) == NULL){
            return i;
        }

        if (strchr(prof[i].telefone, '\n') == NULL){
            limpar_buffer();
        }

        prof[i].telefone[
            strcspn(prof[i].telefone, "\n")
        ] = '\0';


        // ================= E-MAIL =================

        printf("\nE-mail: ");

        if (fgets(prof[i].email,
                  sizeof(prof[i].email), stdin) == NULL){
            return i;
        }

        if (strchr(prof[i].email, '\n') == NULL){
            limpar_buffer();
        }

        prof[i].email[
            strcspn(prof[i].email, "\n")
        ] = '\0';


        // ================= ADICIONAR SERVIÇOS =================

        if (quantidade_de_servico <= 0){
            printf("\nNão há serviços disponíveis para adicionar.\n");
        }
        else{

            do{

                printf("\nDeseja adicionar um serviço a esse profissional?");
                printf("\n1 - SIM");
                printf("\n2 - NÃO");
                printf("\n---> ");

                if (scanf("%d", &escolha_sim_ou_nao) != 1){
                    escolha_sim_ou_nao = 0;
                }

                limpar_buffer();

                if (escolha_sim_ou_nao != 1 &&
                    escolha_sim_ou_nao != 2){

                    printf("\nOpção inválida!\n");
                    continue;
                }

                if (escolha_sim_ou_nao == 1){

                    printf("\n============================ LISTA DE SERVIÇOS ============================\n");

                    mostrar_servicos(serv, quantidade_de_servico);

                    printf("\nQual serviço deseja adicionar? ");

                    if (scanf("%d", &escolha_servico) != 1){
                        escolha_servico = 0;
                    }

                    limpar_buffer();

                    if (escolha_servico < 1 ||
                        escolha_servico > quantidade_de_servico){

                        printf("\nServiço inválido!\n");
                        continue;
                    }

                    int repetido = 0;

                    for (int j = 0; j < prof[i].total_servico; j++){

                        if (strcmp(
                            prof[i].servico[j].nome_servico,
                            serv[escolha_servico - 1].nome_servico
                        ) == 0){

                            repetido = 1;
                            break;
                        }
                    }

                    if (repetido == 1){
                        printf("\nEsse serviço já foi adicionado!\n");
                    }
                    else{

                        prof[i].servico[prof[i].total_servico] =
                            serv[escolha_servico - 1];

                        prof[i].total_servico++;

                        printf("\nServiço adicionado com sucesso!\n");
                    }
                }

            } while (escolha_sim_ou_nao != 2 &&
                     prof[i].total_servico < 15);
        }

        printf("\nProfissional cadastrado com sucesso!\n");
    }

    mostrar_profissionais(prof, inicio + quantidade_a_cadastrar);

    return inicio + quantidade_a_cadastrar;
}


// ================= PROFISSIONAIS INICIAIS =================

int profissionais_cadastrados(struct profissional p[],
                             int quantida_profissional,
                             struct servico serv[],
                             int quantidade_de_servico,
                             struct agendamento *a){

    (void)a;

    // A lista inicial utiliza os serviços de 0 a 11.
    if (quantidade_de_servico < 12){
        printf("\nErro: a lista inicial precisa de 12 serviços!\n");
        return 0;
    }

    struct profissional pro[] = {

        {
            .nome_profissional = "Camila Ferreira",
            .id = 1234,
            .telefone = "(11)90000-0001",
            .email = "camila.ferreira@exemplo.com",
            .servico = {serv[0], serv[1], serv[3]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Juliana Martins",
            .id = 2345,
            .telefone = "(11)90000-0002",
            .email = "juliana.martins@exemplo.com",
            .servico = {serv[2], serv[3]},
            .total_servico = 2
        },

        {
            .nome_profissional = "Patricia Souza",
            .id = 5678,
            .telefone = "(11)90000-0003",
            .email = "patricia.souza@exemplo.com",
            .servico = {serv[4], serv[5]},
            .total_servico = 2
        },

        {
            .nome_profissional = "Fernanda Oliveira",
            .id = 8910,
            .telefone = "(11)90000-0004",
            .email = "fernanda.oliveira@exemplo.com",
            .servico = {serv[5], serv[6], serv[7]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Beatriz Almeida",
            .id = 1011,
            .telefone = "(11)90000-0005",
            .email = "beatriz.almeida@exemplo.com",
            .servico = {serv[8], serv[9], serv[10]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Larissa Costa",
            .id = 1112,
            .telefone = "(11)90000-0006",
            .email = "larissa.costa@exemplo.com",
            .servico = {serv[11]},
            .total_servico = 1
        },

        {
            .nome_profissional = "Mariana Rocha",
            .id = 1213,
            .telefone = "(11)90000-0007",
            .email = "mariana.rocha@exemplo.com",
            .servico = {serv[0], serv[4], serv[8]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Aline Nascimento",
            .id = 1314,
            .telefone = "(11)90000-0008",
            .email = "aline.nascimento@exemplo.com",
            .servico = {serv[1], serv[9], serv[10]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Renata Barbosa",
            .id = 1415,
            .telefone = "(11)90000-0009",
            .email = "renata.barbosa@exemplo.com",
            .servico = {serv[6], serv[7], serv[11]},
            .total_servico = 3
        },

        {
            .nome_profissional = "Gabriela Lima",
            .id = 1516,
            .telefone = "(11)90000-0010",
            .email = "gabriela.lima@exemplo.com",
            .servico = {serv[0], serv[2], serv[3], serv[10]},
            .total_servico = 4
        }
    };

    int total_funcionario = sizeof(pro) / sizeof(pro[0]);

    if (quantida_profissional > total_funcionario){
        quantida_profissional = total_funcionario;
    }

    if (quantida_profissional < 0){
        return 0;
    }

    for (int i = 0; i < quantida_profissional; i++){
        p[i] = pro[i];
        liberar_horarios(&p[i]);
    }

    return quantida_profissional;
}


// ================= VERIFICAR ID =================

bool verificar_id(struct profissional p[], int quantida_profissional){

    int id;

    printf("\nDigite o ID do funcionário: ");

    if (scanf("%d", &id) != 1){
        limpar_buffer();
        printf("\nID inválido!\n");
        return false;
    }

    limpar_buffer();

    for (int i = 0; i < quantida_profissional; i++){

        if (id == p[i].id){
            return true;
        }
    }

    printf("\nFuncionário inválido!\n");
    return false;
}


// ================= MOSTRAR PROFISSIONAIS =================

void mostrar_profissionais(struct profissional p[], int quantida_profissional){

    printf("\n============================ PROFISSIONAIS CADASTRADOS ============================\n");

    for (int i = 0; i < quantida_profissional; i++){

        printf("\n%d - Profissional: %s", i + 1, p[i].nome_profissional);
        printf("\n     ID: %d", p[i].id);
        printf("\n     Telefone: %s", p[i].telefone);
        printf("\n     E-mail: %s", p[i].email);

        printf("\n     Serviços:");

        if (p[i].total_servico == 0){
            printf("\n        Nenhum serviço cadastrado.");
        }

        for (int k = 0; k < p[i].total_servico; k++){

            printf("\n        %d - %s",
                   k + 1,
                   p[i].servico[k].nome_servico);
                   
        }

        printf("\n\n");
    }
}


// ================= BUSCAR PROFISSIONAIS =================

int buscar_profissionais(struct profissional p[],
                        int quantida_profissional,
                        struct servico serv_escolhido,
                        int lista[]){

    int total = 0;

    for (int k = 0; k < quantida_profissional; k++){

        for (int j = 0; j < p[k].total_servico; j++){

            if (strcmp(
                p[k].servico[j].nome_servico,
                serv_escolhido.nome_servico
            ) == 0){

                lista[total] = k;
                total++;
                break;
            }
        }
    }

    return total;
}
