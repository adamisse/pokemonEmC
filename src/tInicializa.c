#include "../include/tInicializa.h"
#include "../include/tUsuario.h"

void menuInicial(tFilaUsuario *referencia, char *arqP, char *arqL){
  printf("1- Jogar\n2- Melhores pontuações\n3- Sair\n");
  int op;
  do{
    scanf("%d", &op);
  }while(op!=1 && op!=2 && op!=3);
  
  if (op == 1){
    system("clear");

    FILE *arqLog = fopen(arqL,"w");
    fclose(arqLog);

    capturaUsuario(referencia,arqP,arqL);
  }
  else if (op == 2){
    system("clear");
    ordenaFila(referencia);
    printaFila(referencia,arqP);

    char limpa = getchar();
    quebraLinha();
    system("clear");

    menuInicial(referencia,arqP,arqL);
  }else{
    liberaFila(referencia);
  }
}

int convertStringInt(char *string){
  int numF = 0,numAux, tam = strlen(string), pot = 1;
    
  for(int i=tam-1; i>=0 ;i--){
    numAux = (string[i] - '0') * pot;
    numF = numF + numAux;
    pot = pot * 10;
  }
  return numF;
}

void quebraLinha(){
  char quebra;
  do{
    quebra = getchar();
  }while(quebra != '\n');
}
