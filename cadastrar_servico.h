#ifndef CADASTRAR_SERVICO_H
#define CADASTRAR_SERVICO_H

#include "structs.h"

// Copia os serviços padrão para a lista e devolve quantos foram copiados
int lista_de_servicos_oferecidos(struct servico serv[], int quantidade_de_servico);

// Mostra todos os serviços na tela
void mostrar_servicos(struct servico serv[], int quantidade_de_servico);

// Cadastra novos serviços no fim da lista (o contador é alterado por ponteiro)
void cadastrar_servico(struct servico s[], int *total, int capacidade);

// Mostra os serviços em uma linha cada
void imprimir_servicos(struct servico s[], int quantidade_de_servico);

// Grava todos os serviços no arquivo servicos.txt
void salvar_servicos(struct servico s[], int total);

// Lê os serviços do arquivo e devolve quantos foram lidos
int carregar_servicos(struct servico s[], int quantidade_de_servico);

// Remove um serviço escolhido pela pessoa
void remover_servicos(struct servico s[], int *total);

#endif
