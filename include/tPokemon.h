#ifndef T_POKEMON
#define T_POKEMON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"

#define POK_INICIAIS 3

#define OF 0
#define ON 1

/* Definição do struct para armazenar os dados de cada pokemon ativo; */
typedef struct Pokemon tPokemon;

/* Fptr interno da struct tPokemon para armazenar as funções dos golpe de cada Pokemon */
typedef void (*fptrAtaque)(tPokemon *,tPokemon *, char *arqL);
/* Fptr para administrar quais golpes serão armazenados no fptrAtaque */
typedef void (*fptrPokemons)(tPokemon *);

/*
Função para armazenar realizar malloc no struct tPokemon;
@recebe um ponteiro de struct tPokemon;
@retorna o endereço do mesmo já armazenado na memoria;
*/
tPokemon *alocaPokemon(tPokemon *pokemon);

/*
Função para realizar a troca de posição na fila de pokemons do usuario quando a vida chegar a zero, essa mesma função tambem libera o pokemon nocauteado;
@recebe o endereço referencial da fila de tPokemons;
@retorna o proximo elemento da fila, que passa a ser a nova referência;
*/
tPokemon *trocaLiberaPokemon(tPokemon *pokemon);

/*
Função para liberar da memória o pokemon selvagem quando ele é nocauteado;
@recebe um ponteiro do struct tPokemon referente a esse pokemon selvagem;
*/
void liberaPokemonSelvagem(tPokemon *pokemon);

/*
Função para adicionar à fila de tPokemons do usuario um novo pokemon capturado;
@recebe um ponteiro com a referencia de tPokemon e o novo do pokemon a ser adicionado na fila;
*/
void capturaPokemon(tPokemon *pokemon,char *nome);

/*
Função para reinicializar os status do tPokemon do usuario antes do inicio de uma nova batalha, alem de curar a vida atual do mesmo;
@recebe um ponteiro de função com as informações a serem reinicializadas;
*/
void resetaStatus(tPokemon *pokemon);

/*
Função para capturar as informações de um pokemon do arquivo base pokemons.csv e armazenar essas informações 
@recebe um ponteiro de tPokemon onde serão salvos os dados e um codigo referente a linha a qual o pokemon em questão está localizado no arquivo csv;
*/
void inicializaDados(tPokemon *pokemon, int cod);

/*
Função para localizar em qual linha do arquivo base pokemons.csv está o pokemon escolhido, a julgar pelo seu nome;
@recebe um ponteiro de tPokemon onde, futuramente, serão armazenados os dados e um ponteiro de char com uma string contendo o nome a ser procurado;
*/
void procuraPokemonArq(tPokemon *pokemon, char *nome);

/*
Função para verificar a validade de uma abertura de arquivo;
@recebe um ponteiro do tipo FILE a ser verificado;
*/
void verificaAbertura(FILE *arq);

/*
Função para administras as escolhas de pokemons iniciais do usuario;
@recebe um ponteiro tUsuario, tFilaUsuario e duas strings com os nomes dos arquivos a serem administrados, esses dados serão ultilizados em funções futuras;
*/
void escolhePokemon(tUsuario *usuario,tFilaUsuario *referencia,char *arqP, char *arqL);

/*
Função para executar o preenchimento dos ataques de cada pokemon a julgar pelo seu respectivo codigo;
@recebe um ponteiro tPokemon onde serão armazenados as funções de ataque e um código que é ultilizado para acessar a devida posição no vetor fptrPokemonsArray;
*/
void administraPokemon(tPokemon *pokemon, int cod);

/*
Função para preencher o vetor fptrPokemonsArray com as funções de preenchimento de golpes;
*/
void preencheVetorFptr();

/*
Funções que preenchem os vetores de ponteiros de funções internos de cada structs tPokemon, nota-se que cada função preenche com os golpes respectivos de cada pokemon
@Recebem os respectivos ponteiros tPokemon onde serão armazenados os dados;
*/
void preencheAtaquesPikachu(tPokemon *pokemon);
void preencheAtaquesCharizard(tPokemon *pokemon);
void preencheAtaquesVenusaur(tPokemon *pokemon);
void preencheAtaquesBlastoise(tPokemon *pokemon);
void preencheAtaquesStelix(tPokemon *pokemon);
void preencheAtaquesMew(tPokemon *pokemon);

/*
Função para printar uma matriz contendo os pokemons iniciais de escolha do usuario;
@Recebe uma matriz contendo a posição e os nomes de cada pokemon e um tamanho que restringe a quantidade de pokemon exibidos a julgar pela quantidade de pokemons que já foram escolhidos;
*/
void printaPokemons(char pokemons[7][30],int tam);

/*
Função para colocar um pokemon inicial já escolhido no final da matriz de pokemons disponiveis;
@recebe a matriz e um inteiro com a posição contendo o elemento a ser redirecionado ao final da matriz;
*/
void trocaOrdem(char pokemons[7][30],int escolhido);

/*
Função para realizar a captura da posição dos pokemons iniciais;
@recebe um inteiro correspondente ao maior número que poderá ser escolhido;
@retorna um inteiro com a entrada do usuario;
*/
int capturaEscolha(int limite);

/*
Funcao para retornar o nome contido num ponteiro de tPokemon;
@Recebe um respectivo ponteiro de tPokemon;
@retorna um ponteiro de char contendo a string correspondente ao nome do pokemon contido em tPokemon;
*/
char *nomePokemon(tPokemon *pokemon);

/*
Funcao para calcular a porcentagem de vida de um pokemon;
@Recebe um ponteiro tPokemon contendo a vida atual e a vida máxima;
@retorna um float correspondente a porcentagem;
*/
float porcentagemVida(tPokemon *pokemon);

/*
Funcao para retornar a quantidade de vida atual de um tPokemon;
@recebe o ponteiro de tPokemon;
@retorna um float com a vida atual;
*/
float retornaHpAtual(tPokemon *pokemon);

/*
Funcao para retornar a quantidade de vida máxima de um tPokemon;
@recebe o ponteiro de tPokemon;
@retorna um float com a vida máxima;
*/
float retornaHpMax(tPokemon *pokemon);

/*
Funcao para verificar a incidencia do estado de chamas de um pokemon no inicio de sua rodade de combate, caso esteja ligado, desconta a vida do mesmo;
@recebe um ponteiro tPokemon a ser analizado;
*/
void statusQueimando(tPokemon *pokemon);

/*
Funcao para ativar o status de chamas dentro do struct tPokemon;
@recebe o ponteiro do respectivo pokemon onde será ativado o status;
*/
void ativaChamas(tPokemon *pokemon);

/*
Função para verificar a incidencia de elementos que podem alunar a rodada de um pokemon, sendo esses os status de paralisia e de dormindo;
@recebe um ponteiro com o pokemon a ser analisado;
@retorna um inteiro, podendo ser 1 (o pokemon atacante perde a sua rodada) ou 0 (o pokemon atacante não perde a sua rodada) a julgar pelo seus status atuais;
*/
int statusParalisiaDormindo(tPokemon *pokemon);

/*
Função para avaliar se o status de paralisia será ligado ou não a um pokemon que sofreu um ataque elétrico;
@Recebe um ponteiro com o pokemon afetado e int divisor que determina as chances do status paralisia ser ativado;
*/
void paralisia(tPokemon *pokemon, int divisor);

/*
Função para verificar, ao inicio de sua rodada, se o pokemon está com o status cavando ativado, caso sim, essa função retornará 1 e causara o dano respondente a habilidade de cavar no inimigo, se não for o caso, ela retornará 0 e o pokemon poderá realizar sua ação normal;
@recebe 2 ponteiro de struct com as informações de um atacante(que poderá estar executando o golpe de cavar) e um defensivo, que sofrerá o dano caso o ataque de fato ocorra;
@retorna um inteiro, podendo ser 1 (o pokemon atacante perde a sua rodada) ou 0 (o pokemon atacante não perde a sua rodada) a julgar pelo seus status atuais; 
*/
int danoCavando(tPokemon *pokemonAtq,tPokemon *pokemonDfs);

/*
Função para printar no arquivo de saída as informações contidas nos status de um pokemon;
@recebe um ponteiro referente ao arquivo log já previamente aberto, e um ponteiro de pokemon o qual terá suas informações impressas;
*/
void printaStatus(FILE *arq,tPokemon *pokemon);

/*
Função para desativar o status protegido de um pokemon;
@recebe um ponteiro de tPokemon a ser modificado;
*/
void resetaProtegido(tPokemon *pokemon);

/*
Função para ativar o status protegido de um pokemon;
@recebe um ponteiro de tPokemon a ser modificado;
*/
void ativaProtegido(tPokemon *pokemon);

/*
Função para retornar o status protegido de um pokemon;
@recebe um ponteiro de tPokemon a ser avaliado;
@retornar um int podendo ser 1 ou 0 (ativado ou desativo)
*/
int retornaProtegido(tPokemon *pokemon);

/*
Função para ativar o ponteiro de função contido no struct tPokemon após o mesmo decidir atacar;
@recebe 2 ponteiros de struct tPokemon, onde um será o pokemon que executa o golpe (Pokatq) e o outro que sofre (Pokdef), também recebe um inteiro correspondente a posição do golpe no vetor fptrAtaque golpe[3] e uma string com o nome do arquivo de saída log;
*/
void executaGolpe(tPokemon *Pokatq, tPokemon *Pokdef,int num,char *arqL);

/*
Função para retornar o tipo de um pokemon contido no struct tPokemon;
@Recebe um ponteiro tPokemon que armazena as informações;
@retornar um char correspondente ao tipo do pokemon;
*/
char retornaTipo(tPokemon *pokemon);

/*
Função para setar a vida de um pokemon selvagem em -1;
@recebe um ponteiro tPokemon a ser modificado;
*/
void setaVidaNegativa(tPokemon *pokemon);

/*
Função para setar a vida de um pokemon em 0;
@recebe um ponteiro tPokemon a ser modificado;
*/
void setaVidaZero(tPokemon *pokemon);

/*
Função para acessar o valor interno dano de ataque de um pokemon;
@recebe o ponteiro tPokemon com as informações;
@retorna um int correspondente ao ataque;
*/
int retornaAtaque(tPokemon *pokemon);

/*
Função para acessar o valor interno de defesa de um pokemon;
@recebe o ponteiro tPokemon com as informações;
@retorna um int correspondente ao defesa;
*/
int retornaDefesa(tPokemon *pokemon);

/*
Função para descontar a vida atual de um determinado pokemon em combate;
@recebe o ponteiro tPokemon com a ser modificado e a quantidade de dano que ele irá tomar;
@retorna um int correspondente ao defesa;
*/
void descontaVida(tPokemon *pokemon, float dano);

/*
Função para ativar o status de dormindo de um pokemon
@recebe o ponteiro de tPokemon a ser modificado, uma condição que determina se o pokemon dormiu por conta própia ou foi dormido por um inimigo e um inteiro com a quantidade de turnos que ficará dormindo;
*/
void ativaDormir(tPokemon *pokemon, int condicao, int qtdTurnos);

/*
Função para ativar o status cavando de um pokemon;
@recebe um ponteiro de tPokemon a ser modificado;
*/
void ativaCavar(tPokemon *pokemon);

#endif