#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include "structs.h"

// Mostra os dias da semana e os horários
void horarios_disponiveis(struct agendamento *a);

// Deixa o cliente escolher produtos durante o agendamento e devolve o valor total
float escolher_produtos(struct produto prod[], int quantidade_de_produto, struct agendar_horario_fazer_compra *compra);

// Faz o agendamento completo: serviços, profissionais, dia, horário e produtos
void agendar_servico_para_cliente(struct servico serv[], int quantidade_de_servico, struct profissional p[], int quantida_profissional, struct produto prod[], int quantidade_de_produto);

#endif
