#ifndef STRUCTS_H
#define STRUCTS_H

/*
 * structs.h
 * Define as estruturas de dados e constantes usadas por todo o projeto.
 */

#define MAX_PRODUTOS 100
#define ARQUIVO_PRODUTOS "produtos.txt"   // arquivo onde os produtos são salvos
#define ARQUIVO_SERVICOS "servicos.txt"   // arquivo onde os serviços são salvos

// Produto vendido no salão
struct produto {
    char nome[40];
    float preco;
    int estoque;
};

// Serviço oferecido (ex.: Corte Feminino)
struct servico {
    char nome_servico[30];
    char categoria[20];   // Cortes, Luzes ou Colorações
    char duracao[10];     // ex.: "1h30"
    float preco;          // preço "a partir de"
};

// Dias da semana e horários usados no agendamento
struct agendamento {
    char dia_da_semana[5][20];   // segunda a sexta
    char horario[7][20];         // 7 horários por dia
};

// Profissional do salão
struct profissional {
    char nome_profissional[50];
    int id;                       // usado no acesso de funcionário
    char telefone[15];
    char email[50];
    struct servico servico[15];   // serviços que o profissional realiza
    int total_servico;            // quantos serviços já foram adicionados
    int disponivel[5][7];         // 1 = horário livre, 0 = ocupado (5 dias x 7 horários)
};

// "Carrinho" de produtos de um agendamento
struct agendar_horario_fazer_compra {
    struct produto produto[10];
    int total_produtos;
};

#endif
