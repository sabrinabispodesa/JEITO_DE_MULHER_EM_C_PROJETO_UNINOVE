#ifndef UTIL_H
#define UTIL_H

// Descarta o que sobrou digitado no teclado (por exemplo, o Enter depois de um scanf)
void limpar_buffer(void);

// Pergunta um número e repete a pergunta até ele estar entre minimo e maximo
int pedir_numero(const char *mensagem, int minimo, int maximo);

#endif
