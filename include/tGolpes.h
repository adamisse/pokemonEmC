#ifndef T_GOLPES
#define T_GOLPES

#include <stdio.h>
#include <stdlib.h>
#include "tPokemon.h"

/*Fptr que armazena e lida com os tipos elementares de cada pokemon;*/
typedef float (*fptrTipoAtacante)(char);

/*Função que atribui cada posição do array da fptrAtaqueAleatorio a um golpe, sendo cada um dos golpes representado por uma função;*/
void preencheAtaqueAleatorio();

/*Função que atribui cada posição do array de fptrTipoAtacanteArray a um tipo de pokemon, sendo cada um dos tipos de pokemon representado por uma função;*/
void preencheAtacante();

/*
Utiliza a função rand() para realizar uma lógica de sorteio, retornando se será adicionado dano crítico ao ataque atual;
@retorna um multiplicador, sendo 1(caso não sorteie crítico) e 2 (caso sorteie crítico);
*/
int sorteiaCritico();

/*
Realiza a chamada de uma das funções contidas em fptrTipoAtacanteArray, tomando o char que representa o pokemon de ataque e chamando a função relacionada ao seu tipo (que está contida no array do ponteiro de função);
@recebe dois char, representando respectivamente o pokemon de ataque e o de defesa;
@retorna um float, representando o multiplicador resultante da combinação entre o pokemon de ataque e o pokemon de defesa;
*/
float administraTipos(char tAtacante, char tDefensivo);


/*
Calcula o dano real que a skill terá na vida do adversário através de uma lógica aritmética simples com base nos parâmetros passados;
@recebe 3 int (poder, ataque e defesa) e um float (modificador, que representa o produto de alguns parâmetros extras que modificam o dano base do pokemon atacante);
@retorna um float que representa o dano calculado;
*/
float calculaDano(int poder,int ataque,int defesa,float modificador);

/*
Funções que foram atribuidas ao fptrTipoAtacanteArray pela função preencheAtacante. São chamadas por administraTipos, sendo estas responsáveis por retornar um multiplicador cujo valor é determinado pela lógica de combinação entre a função que foi chamada e o tipo de pokemon defensivo que foi passado;
@recebe um char, representando o pokemon defensivo;
@retorna um float que representa o multiplicador obtido após a lógica de verificação;
*/
float atacanteElectric(char defesa);
float atacanteSteel(char defesa);
float atacanteFire(char defesa);
float atacanteWater(char defesa);
float atacantePsychic(char defesa);
float atacanteGrass(char defesa);

/*
Funções responsáveis por imprimir tanto no terminal, quando no arquivo de log, o ataque realizado. Além disso, cada uma das funções a seguir representa um golpe, nele está contida todas as lógicas de ataque, chamadas para outras funções, atribuições e verificações necessárias para que o golpe seja feito e batalha prossiga;
@recebe os pokemons de ataque e defesa, além do arquivo de log;
*/
void choqueDoTrovao(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void ondaDeChoque(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void bater(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void lancaChamas(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void dormir(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void poDeSono(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void bombaDeSemente(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void doisGumes(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void armaDeAgua(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void proteger(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void raboDeFerro(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void cavar(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void metronomo(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);
void autoDestruir(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL);

#endif