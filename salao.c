
#include <stdio.h>
#include <string.h>
#include "cadastrar_clientee.h"
#include "cadastrar_funcionario.h"
#include "cadastrar_produtos.h"
#include "cadastrar_servico.h"
#include "agendamento.h"
#include "util.h"
#include "structs.h"


int main(){

    int quantidade = 20;
    int escolha_fun_cli;
    int escolha_opcao_menu;
    int opcao_executar;

    struct cliente cliente[quantidade];
    struct produto produto[quantidade];
    struct servico servico[quantidade];
    struct profissional profissional[quantidade];
    struct agendamento agendamento[10];


    // ================= CARREGAR PRODUTOS =================

    int quantidade_de_produto = carregar_produtos(produto, quantidade);

    if (quantidade_de_produto == 0){
        quantidade_de_produto = lista_de_produtos(produto, quantidade);
        salvar_produtos(produto, quantidade_de_produto);
    }


    // ================= CARREGAR SERVIÇOS =================

    int quantidade_de_servico = carregar_servicos(servico, quantidade);

    if (quantidade_de_servico == 0){
        quantidade_de_servico = lista_de_servicos_oferecidos(servico, quantidade);
        salvar_servicos(servico, quantidade_de_servico);
    }


    // ================= CARREGAR PROFISSIONAIS =================

    int quantidade_de_profissionais = profissionais_cadastrados(
        profissional,
        10,
        servico,
        quantidade_de_servico,
        agendamento
    );


    // ================= MENU INICIAL =================

    printf("\n============================ BEM-VINDO ============================\n");
    printf("\n1 - FUNCIONÁRIO");
    printf("\n2 - CLIENTE");

    escolha_fun_cli = pedir_numero("\n-> ", 1, 2);


    // ================= VERIFICAR ID =================

    if (escolha_fun_cli == 1){

        if (verificar_id(profissional, quantidade_de_profissionais)){
            printf("\nAcesso permitido!\n");
        }
        else{
            printf("\nAcesso negado!\n");
            return 0;
        }
    }


    // ================= MENUS =================

    do{

        if (escolha_fun_cli == 1){

            // ================= MENU FUNCIONÁRIO =================

            printf("\n============================ MENU FUNCIONÁRIO ============================\n");
            printf("\n0 - SAIR");
            printf("\n1 - CADASTRAR CLIENTE");
            printf("\n2 - CADASTRAR PROFISSIONAL");
            printf("\n3 - VER LISTA DE PRODUTOS");
            printf("\n4 - VER LISTA DE SERVIÇOS");
            printf("\n5 - PROFISSIONAIS CADASTRADOS");
            printf("\n6 - VER HORÁRIOS DISPONÍVEIS");
            printf("\n7 - AGENDAR SERVIÇO");
            printf("\n8 - CADASTRAR PRODUTO");
            printf("\n9 - REMOVER PRODUTO");
            printf("\n10 - CADASTRAR SERVIÇO");
            printf("\n11 - REMOVER SERVIÇO");

            escolha_opcao_menu = pedir_numero(
                "\nESCOLHA A OPERAÇÃO: ", 0, 11
            );

            opcao_executar = escolha_opcao_menu;
        }

        else if (escolha_fun_cli == 2){

            // ================= MENU CLIENTE =================

            printf("\n============================ MENU CLIENTE ============================\n");
            printf("\n0 - SAIR");
            printf("\n1 - VER LISTA DE PRODUTOS");
            printf("\n2 - VER LISTA DE SERVIÇOS");
            printf("\n3 - VER LISTA DE PROFISSIONAIS");
            printf("\n4 - VER HORÁRIOS DISPONÍVEIS");
            printf("\n5 - AGENDAR SERVIÇO");

            escolha_opcao_menu = pedir_numero(
                "\nESCOLHA A OPERAÇÃO: ", 0, 5
            );

            // Converte a opção do cliente para o switch
            if (escolha_opcao_menu == 0){
                opcao_executar = 0;
            }
            else{
                opcao_executar = escolha_opcao_menu + 2;
            }
        }


        // ================= EXECUTAR OPERAÇÃO =================

        switch(opcao_executar){

            case 0:
                printf("\nSaindo do sistema...\n");
                break;


            // ================= CADASTRAR CLIENTE =================

            case 1:
                cadastrar_cliente(cliente, quantidade);
                break;


            // ================= CADASTRAR PROFISSIONAL =================

            case 2:
                quantidade_de_profissionais = cadastrar_profissional(
                    servico,
                    quantidade_de_servico,
                    profissional,
                    quantidade_de_profissionais
                );
                break;


            // ================= MOSTRAR PRODUTOS =================

            case 3:
                mostrar_produtos(produto, quantidade_de_produto);
                break;


            // ================= MOSTRAR SERVIÇOS =================

            case 4:
                mostrar_servicos(servico, quantidade_de_servico);
                break;


            // ================= MOSTRAR PROFISSIONAIS =================

            case 5:
                mostrar_profissionais(
                    profissional,
                    quantidade_de_profissionais
                );
                break;


            // ================= HORÁRIOS DISPONÍVEIS =================

            case 6:
                horarios_disponiveis(agendamento);
                break;


            // ================= AGENDAR SERVIÇO =================

            case 7:
                agendar_servico_para_cliente(
                    servico,
                    quantidade_de_servico,
                    profissional,
                    quantidade_de_profissionais,
                    produto,
                    quantidade_de_produto
                );
                break;


            // ================= CADASTRAR PRODUTO =================

            case 8:
                cadastrar_produto(
                    produto,
                    &quantidade_de_produto,
                    quantidade
                );

                salvar_produtos(produto, quantidade_de_produto);

                mostrar_produtos(produto, quantidade_de_produto);
                break;


            // ================= REMOVER PRODUTO =================

            case 9:
                remover_produtos(produto, &quantidade_de_produto);

                salvar_produtos(produto, quantidade_de_produto);
                break;


            // ================= CADASTRAR SERVIÇO =================

            case 10:
                cadastrar_servico(
                    servico,
                    &quantidade_de_servico,
                    quantidade
                );

                salvar_servicos(servico, quantidade_de_servico);

                mostrar_servicos(servico, quantidade_de_servico);
                break;


            // ================= REMOVER SERVIÇO =================

            case 11:
                remover_servicos(servico, &quantidade_de_servico);

                salvar_servicos(servico, quantidade_de_servico);
                break;


            default:
                printf("\nOpção inválida!\n");
                break;
        }

    } while (escolha_opcao_menu != 0);

    return 0;
}
