#ifndef T_USUARIO
#define T_USUARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Definição do struct para armazenar os dados de cada usuario; */
typedef struct Usuario tUsuario;

/*Definição do struct que representa a lista de usuários*/
typedef struct tFilaUsuario tFilaUsuario;

/*
Função que armazena e realiza malloc no struct tUsuario;
@recebe um ponteiro do struct tUsuario;
@retorna o endereço do struct tUsuario, já armazenado na memoria;
*/
tUsuario *alocaUsuario(tUsuario *usuario);

/*
Função utilizada para alocar a fila de struct de usuários e atualizar o final da fila, setando referencia->next para NULL;
@recebe um ponteiro da struct tFilaUsuario;
@retorna o endereço sa struct tFilaUsuario, já alocado;
*/
tFilaUsuario *alocaReferencia(tFilaUsuario *referencia);

/*
Realiza a alocação da fila de struct dos usuários e atualiza o final da fila, setando referencia->next para NULL;
@recebe um ponteiro de tFilaUsuario e dois ponteiros de char (que representam os arquivos de pontuação e de log, respectivamente);
*/
void capturaUsuario(tFilaUsuario *referencia, char *arqP, char *arqL);

/*
Faz a liberação do usuário que fora alocado, dando free e atribuindo tanto a string usuario->nome quanto o ponteiro do tipo tUsuario para NULL;
@recebe um ponteiro do tipo tUsuario;
*/
void liberaUsuario(tUsuario *usuario);

/*
Responsável por fazer a alocação de uma string qualquer por meio de um malloc, retornando um aviso no caso da string alocada estar vazio;
@recebe um ponteiro de char e um inteiro (representando o tamanho da string);
@retorna a string devidamente alocada;
*/
char *alocaString(char *string, int tam);

/*
Função responsável por realizar a liberação da fila, sendo chamada no momento em que o usuário opta por sair do programa;
@recebe um ponteiro do tipo tFilaUsuario, representando a nossa lista de usuários;
*/
void liberaFila(tFilaUsuario *fila);

/*
Tem por objetivo realizar, através de um looping, toda a lógica de adição de um novo usuário dentro da fila de usuários e dos arquivos. Ao fim da lógica, a função efetua a chamada das funções liberaUsuario e menuInicial.
@recebe um usuário, uma referencia da lista de usuários e as strings que representam os arquivos a serem abertos.
*/
void adicionaFilaUsuario(tUsuario *usuario,tFilaUsuario *referenciaUsuario, char *arqP, char *arqL);

/*Realiza a ordenação dos usuários por pontuação (do maior ponto para o menor) através de um algoritmo de ordenação (bubble sort), sendo que em caso de empate a mesma é feita considerando o tamanho do nome como critério de desempate.
@recebe apenas a referencia para a lista de usuários;
*/
void ordenaFila(tFilaUsuario *fila);

/*
Faz a impressão dos nomes dos usuários cadastrados na fila e suas pontuações (já ordenados anteriormente por ordenaFila). Caso não haja usuário cadastrado a função imprime um aviso no terminal.
@recebe uma referencia da lista de usuários e uma string que representa o arquivo de pontuação a ser aberto.
*/
void printaFila(tFilaUsuario *fila, char *arqP);

/*
Função que tem por objetivo contabilizar quantos usuários a fila possui, sendo chamada em tBatalha.c referenciando o número de usuários que já jogaram o jogo numa mesma sessão.
@recebe apenas a referencia para a lista de usuários;
@retorna o tamanho atual da fila, simbolizando a quantidade de usuários;
*/
int tamFila(tFilaUsuario *fila);

/*
Efetua o acesso ao valor de quantas rodadas se passaram desde o ultimo Mew, contido dentro de tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna um inteiro representando quantas rodadas se passaram desde o ultimo Mew;
*/
int retornaUltMew(tUsuario *usuario);

/*
Faz o reset do ultimo mew assim que o usuário confronta um novo Mew;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void resetaUltMew(tUsuario *usuario);

/*
Realiza o incremento da variável "qtdBatalhas" contida em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void incrementaBatalhas(tUsuario *usuario);

/*
Função para acessar o valor interno de quantidade de batalhas de um usuário;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna a quantidade de batalhas que o jogador atual participou;
*/
int retornaQtdBatalhas(tUsuario *usuario);

/*
Responsável por atualizar a quantidade de rodadas passadas desde que a ultima pokebola foi encontrada
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna, de forma atualizada, a variavel "ultimaPokebola" contida em tUsuario;
*/
int incrementaUltimaPokebola(tUsuario *usuario);

/*
Faz o incremento à quantidade de pokebolas que o usuário possui;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void incrementaPokebola(tUsuario *usuario);

/*
Reduz uma pokebola da quantidade de pokebolas que o usuário possui, quando o mesmo opta por tentar capturar um pokemon selvagem;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void decrementaPokebola(tUsuario *usuario);

/*
Função para acessar o valor interno de quantidade de pokebolas de um usuário;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna a quantidade de pokebolas que o jogador atual possui;
*/
int retornaQtdPokebola(tUsuario *usuario);

/*
Função para acessar o valor interno do nome do usuário contido em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna a string contendo o nome do usuário;
*/
char *retornaNome(tUsuario *usuario);

/*
Adiciona uma vitória à variável "qtdVitórias" contida em tUsuario quando o mesmo vence uma batalha;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void incrementaVitoria(tUsuario *usuario);

/*
Atribui 1 à variável "atacou" contida em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void setaAtaque(tUsuario *usuario);

/*
Função para acessar o valor interno da variável "atacou" contida em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna um inteiro contendo "usuario->atacou";
*/
int retornaCondicaoAtaque(tUsuario *usuario);

/*
Incrementa a quantidade de fugas que um usuário tentou durante uma mesma batalha;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void incrementaFuga(tUsuario *usuario);

/*
Função para acessar o valor interno da variável "tentativasFuga" contida em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
@retorna um inteiro contendo "usuario->tentativasFuga";
*/
int retornaFugas(tUsuario *usuario);

/*
Chamada ao fim da batalha para fazer o reset dos elementos "atacou" e "tentativasFuga" contidos em tUsuario;
@recebe um ponteiro tUsuario contendo as informações do usuário;
*/
void resetaUltAtaqueFugas(tUsuario *usuario);

#endif