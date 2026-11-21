#ifndef CADASTRAR_PRODUTOS_H
#define CADASTRAR_PRODUTOS_H

#include "structs.h"

// Copia os produtos padrão para a lista e devolve quantos foram copiados
int lista_de_produtos(struct produto prod[], int quantidade_de_produto);

// Mostra todos os produtos na tela
void mostrar_produtos(struct produto prod[], int quantidade_de_produto);

// Cadastra novos produtos no fim da lista (o contador é alterado por ponteiro)
void cadastrar_produto(struct produto p[], int *total, int quantidade);

// Mostra os produtos em uma linha cada
void imprimir_produtos(struct produto p[], int quantidade_de_produto);

// Grava todos os produtos no arquivo produtos.txt
void salvar_produtos(struct produto p[], int total);

// Lê os produtos do arquivo e devolve quantos foram lidos
int carregar_produtos(struct produto p[], int quantidade_de_produto);

// Remove um produto escolhido pela pessoa
void remover_produtos(struct produto p[], int *total);

#endif
