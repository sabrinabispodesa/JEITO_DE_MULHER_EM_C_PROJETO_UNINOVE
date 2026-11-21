#ifndef CADASTRAR_SERVICO_H
#define CADASTRAR_SERVICO_H

#include "structs.h"


int lista_de_servicos_oferecidos(struct servico serv[], int quantidade_de_servico);

void mostrar_servicos(struct servico serv[], int quantidade_de_servico);

void cadastrar_servico(struct servico s[], int *total, int capacidade);

void imprimir_servicos(struct servico s[], int quantidade_de_servico);

void salvar_servicos(struct servico s[], int total);

int carregar_servicos(struct servico s[], int quantidade_de_servico);

void remover_servicos(struct servico s[], int *total);

#endif

