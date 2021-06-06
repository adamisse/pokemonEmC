#ifndef T_BATALHA
#define T_BATALHA

#include "tGolpes.h"
#include "tPokemon.h"
#include "tUsuario.h"
#include <unistd.h>

#define OF 0
#define ON 1

/* Ponteiro de função que administra funções para printar o painel de golpes especificos para cada pokemon */
typedef void (*fptrPrintaGolpes)();

/* 
Funcao para preencher um vetor do tipo fptrPrintaGolpes com as funções de printar os paineis com os golpes de cada pokemon
*/
void preenchePrintaGolpes();

/*
Funções que printam os paineis de golpes correspondente aos respectivos pokemons;
*/
void golpesPikachu();
void golpesCharizard();
void golpesVenusaur();
void golpesBlastoise();
void golpesSteelix();
void golpesMew();

/*
Função que seta um fptrPrintaGolpes para executar a função contida em um vetor de fptrPrintaGolpes na posição de interesse;
@recebe um char contendo o código de acesso a posição do vetor de fptrPrintaGolpes para executar sua respectiva função;
*/
void printaGolpes(char code);

/*
Função para capturar a ação do usúario para assim realizar a sua rodada;
@retorna um int correspondente a ação do usúario;
*/
int capturaAcao();

/*
Função para gerar, aleatoriamente, um pokemon selvagem que atacará o usuario;
@recebe um ponteiro de tUsuario (para determinar a probabilidade de surgir um Mew)
@retorna um ponteiro do tipo tPokemon preenchido com as informações de um pokemon selvagem aleatório;
*/
tPokemon *geraPokemonSelvagem(tUsuario *usuario);

/*
Função cosmética para gerar suspense entre rodadas ou acontecimento importantes;
*/
void animacao();

/*
Função que marca o início de uma possivel batalha a julgar pelas condições dos pokemons do usuario;
@recebe um ponteiro referencial de tPokemon contendo a fila de pokemons que o usuario possui, um ponteiro do tipo tUsuario que contem as informações do usuario que está jogando atualmente, um ponteiro referencial de tFilaUsuario que contem uma fila com os usuários que já jogaram e dois ponteiros de char contendo os nomes dos arquivos de saída a serem abertos;
*/
void iniciaBatalha(tUsuario *usuario, tPokemon *referencia,tFilaUsuario *referenciaUsuario,char *arqP, char *arqL);

/*
Função para realizar o sorteio de uma pokebola nova ao usuario no final de um combate;
@recebe um ponteiro tUsuario onde será acrescentada a nova pokebola;
*/
void sorteiaPokebola(tUsuario *usuario);

/*
Função que administra o combate entre os pokemons do usuario e um determinado pokemon selvagem;
@recebe 2 ponteiros do tipo tPokemon, um contendo as informações do pokemon selvagem e o outro contendo a fila de pokemons do usuario, além disso, também recebe um ponteiro tUsuario contendo as informações do usuario em batalha e um ponteiro do tipo tFilaUsuario que representa a refência da fila de usuario que já jogaram, por fim, 2 ponteiro de char contendo os nomes dos arquivos de saída;
*/
void batalhando(tUsuario *usuario, tPokemon *pokemonUsuario,tPokemon *pokemonSelvagem,tFilaUsuario *referencia, char *arqP, char *arqL);

/*
Função que administra e executa a rodada do usuario;
@recebe 2 ponteiros do tipo tPokemon representando os pokemons em batalha, logo esses carregam as informações do pokemon selvagem e do pokemon do usuario, além disso também recebe um ponteiro tipo char que contem o nome do arquivo de sáida log e por fim um ponteiro do tipo tUsuario com as informações do usuario que está em partida;
*/
void rodadaUsuario(tPokemon *pokemonUsuario, tPokemon *pokemonSelvagem,tUsuario *usuario, char *arqL);

/*
Função que administra e executa a rodada do pokemon selvagem;
@recebe 2 ponteiros do tipo tPokemon representando os pokemons em batalha, logo esses carregam as informações do pokemon selvagem e do pokemon do usuario, além disso também recebe um ponteiro tipo char que contem o nome do arquivo de sáida log;
*/
void rodadaSelvagem(tPokemon *pokemonSelvagem, tPokemon *pokemonUsuario, char *arqL);

#endif