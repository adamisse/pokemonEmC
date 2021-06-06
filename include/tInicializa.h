#ifndef T_INICIALIZA
#define T_INICIALIZA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"

/*
Função para converter um número em formato de string e converte-lo no que representa como inteiro;
@recebe um ponteiro de char contendo o uma string que representa um numero;
@retorna o valor inteiro contido na string;
*/
int convertStringInt(char *string);

/*
Função que representa o menu inicial do jogo, realizando o controle de caminhos a julgar pela entrada do usuário;
@Recebe um ponteiro referencia de tFilaUsuario que armazenará as informações dos usuarios que jogaram e duas strings contendo os nomes dos arquivos de saída que serão abertos futuramentes;
*/
void menuInicial(tFilaUsuario *referencia, char *arqP, char *arqL);

/*
Função que espera uma entrada \n do usuario;
*/
void quebraLinha();

#endif