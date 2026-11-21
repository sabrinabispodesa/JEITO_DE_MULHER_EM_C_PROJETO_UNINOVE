#ifndef CADASTRAR_FUNCIONARIO_H
#define CADASTRAR_FUNCIONARIO_H

#include <stdbool.h>
#include "structs.h"

// Pede um ID e devolve true se ele existir entre os profissionais cadastrados
bool verificar_id(struct profissional p[], int quantida_profissional);

// Marca todos os horários do profissional como livres
void liberar_horarios(struct profissional *prof);

// Cadastra novos profissionais e devolve o novo total
int cadastrar_profissional(struct servico serv[], int quantidade_de_servico, struct profissional prof[], int quantidade_de_profissionais);

// Cria os profissionais de exemplo e devolve quantos foram criados
int profissionais_cadastrados(struct profissional p[], int quantida_profissional, struct servico serv[], int quantidade_de_servico, struct agendamento *a);

// Mostra os profissionais e os serviços que cada um realiza
void mostrar_profissionais(struct profissional p[], int quantida_profissional);

// Guarda em lista[] quais profissionais realizam o serviço e devolve quantos encontrou
int buscar_profissionais(struct profissional p[], int quantida_profissional, struct servico serv_escolhido, int lista[]);

#endif
