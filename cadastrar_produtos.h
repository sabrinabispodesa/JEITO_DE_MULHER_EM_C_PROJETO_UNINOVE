#ifndef CADASTRAR_PRODUTOS_H
#define CADASTRAR_PRODUTOS_H

#include "structs.h"


int lista_de_produtos(struct produto prod[], int quantidade_de_produto);
void mostrar_produtos(struct produto prod[], int quantidade_de_produto);
void cadastrar_produto(struct produto p[], int *total, int quantidade);
void imprimir_produtos(struct produto p[], int quantidade_de_produto);
void salvar_produtos (struct produto p[], int total);
int carregar_produtos(struct produto p[], int quantidade_de_produto);
void remover_produtos(struct produto p[], int *total);



#endif