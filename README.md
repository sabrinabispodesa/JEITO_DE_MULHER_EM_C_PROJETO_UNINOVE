Sistema de Gestão – Salão de Beleza Jeito de Mulher

Projeto desenvolvido na disciplina de -- PROJETO DE EXTENSÃO EM DESENVOLVIMENTO DE SOFTWARE -- UNINOVE
GRUPO: ENZO VALDIVINO ROSSI - RA: 1726203184
       GIOVANNA RODRIGUES LANZONI - RA: 926200505
       GUILHERME DOS SANTOS PAULINO - RA: 926202269
       IZABELA BARBOSA LOPES - RA: 926205861
       SABRINA LOPES BISPO DE SÁ YOUTE - RA: 926205109
       VITÓRIA ALVES PEREIRA SILVA - RA: 926205897

Projeto acadêmico em C, executado no terminal, para gerenciar um salão de beleza: clientes, profissionais, produtos, serviços e agendamento de horários. O código é dividido em módulos (.h e .c) e usa arquivos de texto para guardar produtos e serviços.

Todos os dados do projeto (nomes, telefones, e-mails e IDs) são fictícios, criados apenas para teste.

Funcionalidades

O programa começa perguntando se a pessoa é funcionário ou cliente.

Menu do funcionário (exige ID)
Opção	O que faz
1	Cadastrar cliente
2	Cadastrar profissional
3	Ver lista de produtos
4	Ver lista de serviços
5	Ver profissionais cadastrados
6	Ver horários disponíveis
7	Agendar serviço
8	Cadastrar produto
9	Remover produto
10	Cadastrar serviço
11	Remover serviço
0	Sair
Menu do cliente (sem ID)
Opção	O que faz
1	Ver lista de produtos
2	Ver lista de serviços
3	Ver lista de profissionais
4	Ver horários disponíveis
5	Agendar serviço
0	Sair
Como cada parte funciona

Acesso de funcionário. Ao escolher "Funcionário", o programa pede um ID e compara com o ID dos profissionais cadastrados. Se não existir, mostra "Acesso negado" e encerra.

Produtos (produtos.txt)

Cada produto tem nome, preço e estoque.
Ao iniciar, o programa lê o produtos.txt. Se o arquivo não existir ou estiver vazio, carrega 6 produtos padrão e já os salva.
Cadastrar e remover produtos atualiza o arquivo automaticamente.
O estoque precisa ser maior que 0 ao cadastrar.

Serviços (servicos.txt)

Cada serviço tem nome, categoria, duração (ex.: 1h30) e preço "a partir de".
Funciona como os produtos: carrega do arquivo ou, se estiver vazio, usa 12 serviços padrão (Cortes, Luzes e Colorações) e os salva.
É possível cadastrar e remover serviços, e o arquivo é atualizado.

Profissionais

O programa já começa com 10 profissionais de exemplo, cada um com ID, telefone, e-mail e uma lista de serviços que realiza.
Ao cadastrar um novo, informa-se: nome, ID (positivo e único), telefone, e-mail e os serviços (sem repetir, até 15).
O limite é de 20 profissionais no total.

Clientes

Cadastra de 1 a 10 clientes por vez (nome, telefone com DDD e e-mail) e mostra a lista com o telefone formatado.

Agendamento

Informa o nome do cliente e quantos serviços quer realizar (1 a 10).
Para cada serviço, escolhe o serviço, depois um profissional que o realiza, e então o dia (segunda a sexta) e o horário (7 horários, das 09:00 às 15:00).
Só aceita horários livres. Ao agendar, o horário daquele profissional fica ocupado.
Ao final, pode adicionar produtos (até 10 unidades por agendamento), e o estoque é descontado.
Mostra um resumo com serviços, profissionais, dias, horários e o total estimado (serviços "a partir de" + produtos).
Estrutura do projeto
salao.c                 → função main e os menus
structs.h               → structs (produto, servico, profissional, agendamento...) e constantes
util.h / utils.c        → limpar_buffer e pedir_numero
cadastrar_clientee.h / clientes.c
cadastrar_produtos.h / Produtos.c
cadastrar_servico.h / servicos.c
cadastrar_funcionario.h / funcionarios.c
agendamento.h / agendamentos.c
produtos.txt            → produtos salvos
servicos.txt            → serviços salvos
Como compilar e executar

Você precisa de um compilador C (gcc ou clang).

1. Clone o repositório (ou baixe o ZIP) e entre na pasta do projeto:

git clone https://github.com/sabrinabispodesa/JEITO_DE_MULHER_EM_C_PROJETO_UNINOVE
cd JEITO_DE_MULHER_EM_C_PROJETO_UNINOVE

2. Compile:

gcc salao.c utils.c Produtos.c servicos.c funcionarios.c agendamentos.c clientes.c -o salao

3. Execute:

macOS / Linux: ./salao
Windows: .\salao.exe

Rode sempre de dentro da pasta do projeto, porque o programa procura o produtos.txt e o servicos.txt na pasta atual.

No Windows, se os acentos aparecerem errados, digite chcp 65001 no terminal antes de executar.

Exemplo de uso

Entrar como funcionário (ID de teste: 1234):

============================ BEM-VINDO ============================

1 - FUNCIONÁRIO
2 - CLIENTE
-> 1

Digite o ID do funcionário: 1234

Acesso permitido!

O ID 1234 pertence à profissional de exemplo "Camila Ferreira". Para testar como cliente, escolha a opção 2: não é pedido ID.

Limitações conhecidas
Só produtos e serviços são salvos em arquivo. Clientes, profissionais cadastrados durante o uso e agendamentos ficam apenas na memória e são perdidos quando o programa fecha.
O estoque descontado em um agendamento só é gravado no produtos.txt na próxima vez que um produto for cadastrado ou removido.
A opção "Ver horários disponíveis" mostra a grade de dias e horários, e não os horários livres de cada profissional. A disponibilidade é checada na hora de agendar.
Os IDs dos funcionários são números simples no código, usados só para demonstração. Em um sistema real, o acesso precisaria de autenticação segura.
Cada lista tem tamanho fixo (20 posições para clientes, produtos, serviços e profissionais).
O nome de produtos e serviços tem tamanho máximo, definido nas struct.
O que foi praticado
Organização em módulos com arquivos .h e .c e #include de cabeçalhos
struct e vetores de struct
Ponteiros (passagem de contador por referência nas funções de cadastro e remoção)
Leitura e escrita de arquivos de texto (fopen, fgets, fscanf, fprintf)
Validação de entradas do usuário
