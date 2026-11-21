#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_PRODUTOS 100
#define ARQUIVO_PRODUTOS "produtos.txt"
#define ARQUIVO_SERVICOS "servicos.txt"

struct produto{
    char nome[40];
    float preco;
    int estoque;
};

struct servico{
    char nome_servico[30];
    char categoria[20];   
    char duracao[10];     
    float preco;          
};


struct agendamento{
    char dia_da_semana[5][20];
    char horario[7][20];
};

struct profissional{
    char nome_profissional[50];
    int id;
    char telefone[15];
    char email[50];      
    struct servico servico[15];   
    int total_servico;
    int disponivel[5][7];   
};

struct agendar_horario_fazer_compra{
    struct produto produto[10];
    int total_produtos;
};


#endif