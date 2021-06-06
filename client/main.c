#include "../include/tInicializa.h"
#include "../include/tGolpes.h"
#include "../include/tPokemon.h"
#include "../include/tBatalha.h"

/*
É esperado que receba pelo menos 3 strings de parametros, contendo os nomes dos arquivos de saída e um número inteiro ultilizado como seed;
*/
int main(int argc, char **argv) {
  if(argc < 4){
    printf("Erro: os parâmetro nao foram informados da maneira apropiada!\n");
    return 0;
  }

  //Inicizalição da seed;
  int seed = convertStringInt(argv[3]);
  srand(seed);

  //Preenchimento dos vetores de ponteiros de função
  preencheAtaqueAleatorio();
  preencheAtacante();
  preencheVetorFptr();
  preenchePrintaGolpes();

  //Inicizalição do referencial da fila de usuarios;
  tFilaUsuario *referencia = alocaReferencia(referencia);
  //Inicialização do menu principal;
  menuInicial(referencia,argv[1],argv[2]);
  return 0;
}