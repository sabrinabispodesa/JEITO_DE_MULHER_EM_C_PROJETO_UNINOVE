#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include "structs.h"



void horarios_disponiveis(struct agendamento *a);
float escolher_produtos(struct produto prod[], int quantidade_de_produto, struct agendar_horario_fazer_compra *compra);
void agendar_servico_para_cliente(struct servico serv[], int quantidade_de_servico, struct profissional p[], int quantida_profissional, struct produto prod[], int quantidade_de_produto);


#endif