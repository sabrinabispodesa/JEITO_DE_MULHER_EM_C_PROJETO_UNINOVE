#ifndef CADASTRAR_FUNCIONARIO_H
#define CADASTRAR_FUNCIONARIO_H

#include <stdbool.h>
#include "structs.h"

bool verificar_id(struct profissional p[], int quantida_profissional);
void liberar_horarios(struct profissional *prof);
int cadastrar_profissional(struct servico serv[], int quantidade_de_servico, struct profissional prof[], int quantidade_de_profissionais);
int profissionais_cadastrados(struct profissional p[], int quantida_profissional, struct servico serv[],int quantidade_de_servico, struct agendamento *a);
void mostrar_profissionais(struct profissional p[], int quantida_profissional);
int buscar_profissionais(struct profissional p[], int quantida_profissional, struct servico serv_escolhido, int lista[]);


#endif