// struct e nome da função

#ifndef CADASTRAR_CLIENTEE_H
#define CADASTRAR_CLIENTEE_H

// Cliente do salão
struct cliente {
    char nome[40];
    char telefone[15];
    char email[50];
};

void cadastrar_cliente(struct cliente cli[], int quantidade_de_cliente);

#endif
