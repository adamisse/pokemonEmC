#include "../include/tUsuario.h"
#include "../include/tPokemon.h"
#include "../include/tInicializa.h"

struct Usuario{
  char *nome;
  int qtdPokebola, qtdVitorias, qtdBatalha, ultMew;
  int atacou, tentativasFuga, ultimaPokebola;
};

struct tFilaUsuario{
  int qtdVitorias;
  char *nome;
  
  tFilaUsuario *next;
};


tUsuario *alocaUsuario(tUsuario *usuario){
  usuario = malloc(sizeof(tUsuario));
  if(usuario == NULL){
    printf("Erro na alocação de usuario.\n");
    exit(1);
  }
  return usuario;
}

tFilaUsuario *alocaReferencia(tFilaUsuario *referencia){
  referencia = (tFilaUsuario *)malloc(sizeof(tFilaUsuario));
  if(referencia == NULL){
    printf("Erro na alocação de usuario.\n");
    exit(1);
  }
  referencia->next = NULL;

  return referencia;
}

int validaNome(char *nome){
  int tam = strlen(nome);
  for(int i=0; i<tam ;i++){
    if((nome[i] > 'z' || nome[i] < 'a') && (nome[i] != '_') && (nome[i] > 'Z' || nome[i] < 'A') && (nome[i] > '9' || nome[i] < '0'))
      return 0;
  }
  return 1;
}

char *alocaString(char *string, int tam){
  string = (char *)malloc(sizeof(char)*tam);
  if(string == NULL){
    printf("Erro na alocação de uma string.\n");
    exit(1);
  }
  return string;
}

void preencheUsuario(tUsuario *usuario){
  char nome[128];
  int aux;
  printf("Qual o seu nome?\n");
  do{
    scanf(" %[^\n]",nome);
    aux = validaNome(nome);
    if(aux == 0){
      system("clear");
      printf("Digite um nome válido!\n");
    }
  }while(aux == 0);

  usuario->nome = alocaString(usuario->nome,strlen(nome)+1);
  strcpy(usuario->nome,nome);

  usuario->qtdPokebola = 3;
  usuario->qtdVitorias = 0;
  usuario->atacou = 0;
  usuario->tentativasFuga = 0;
  usuario->ultimaPokebola = 0;
  usuario->ultMew = 0;
  usuario->qtdBatalha = 0;
}

void liberaUsuario(tUsuario *usuario){
  free(usuario->nome);
  usuario->nome = NULL;
  free(usuario);
  usuario = NULL;
}

void capturaUsuario(tFilaUsuario *referencia, char *arqP, char *arqL){
  tUsuario *usuario = alocaUsuario(usuario);
  preencheUsuario(usuario);

  system("clear");
  escolhePokemon(usuario,referencia,arqP,arqL);
}

void adicionaFilaUsuario(tUsuario *usuario,tFilaUsuario *referenciaUsuario, char *arqP, char *arqL){
  tFilaUsuario *atual = referenciaUsuario;
  tFilaUsuario *proximo = NULL;
  while(1){
    proximo = atual->next;
    if(proximo == NULL){
      proximo = alocaReferencia(proximo);
      proximo->nome = alocaString(proximo->nome, strlen(usuario->nome)+1);
      strcpy(proximo->nome,usuario->nome);
      proximo->qtdVitorias = usuario->qtdVitorias;

      proximo->next = NULL;
      atual->next = proximo;
      break;
    }else{
      atual = atual->next;
    }
  }
  liberaUsuario(usuario);
  menuInicial(referenciaUsuario,arqP,arqL);
}

void liberaFila(tFilaUsuario *fila){
  tFilaUsuario *celula_atual;
  tFilaUsuario *proxima_celula;

  celula_atual = fila;
  proxima_celula = celula_atual->next;
  free(celula_atual);

  while(proxima_celula != NULL){
    celula_atual = proxima_celula;
    proxima_celula = celula_atual->next;

    free(celula_atual->nome);
    free(celula_atual);

    celula_atual = proxima_celula;
  }
}

int tamFila(tFilaUsuario *fila){
  tFilaUsuario *celula_atual;
  tFilaUsuario *proxima_celula;

  int tam = 1;
  celula_atual = fila;
  proxima_celula = celula_atual->next;

  while(proxima_celula != NULL){
    celula_atual = proxima_celula;
    tam++;

    proxima_celula = celula_atual->next;
    celula_atual = proxima_celula;
  }

  return tam;
}

void printaFila(tFilaUsuario *fila, char *arqP){
  tFilaUsuario *celula_atual;
  tFilaUsuario *proxima_celula;
  int i=1;

  celula_atual = fila;
  proxima_celula = celula_atual->next;

  FILE *arquivoS = fopen(arqP,"w");
  verificaAbertura(arquivoS);

  if(proxima_celula == NULL){
    printf("Nenhum cadastrado!\n");
  }

  while(proxima_celula != NULL){
    celula_atual = proxima_celula;
    printf("%d- %s: %d\n",i,celula_atual->nome,celula_atual->qtdVitorias);
    fprintf(arquivoS,"%s %d\n",celula_atual->nome,celula_atual->qtdVitorias);

    proxima_celula = celula_atual->next;
    celula_atual = proxima_celula;
    i++;
  }

  fclose(arquivoS);
}

void ordenaFila(tFilaUsuario *fila){
  tFilaUsuario *pi;
  tFilaUsuario *pj;
  tFilaUsuario *pfim = NULL;

  if(fila->next != NULL){
    for(pi = fila->next; pi->next != NULL ; pi=pi->next){
      for(pj = fila->next; pj->next != pfim; pj=pj->next){
        if(pj->qtdVitorias < pj->next->qtdVitorias){
          char *nomeAux = pj->nome;
          int vitoriasAux = pj->qtdVitorias;

          pj->nome = pj->next->nome;
          pj->qtdVitorias = pj->next->qtdVitorias;
          pj->next->nome = nomeAux;
          pj->next->qtdVitorias = vitoriasAux;

        }else if(pj->qtdVitorias == pj->next->qtdVitorias){
          if(strcmp(pj->nome, pj->next->nome) > 0){
            char *nomeAux = pj->nome;
            int vitoriasAux = pj->qtdVitorias;

            pj->nome = pj->next->nome;
            pj->qtdVitorias = pj->next->qtdVitorias;
            pj->next->nome = nomeAux;
            pj->next->qtdVitorias = vitoriasAux;
            
          }
        }
      }
      pfim = pj;
    }
  }
}

int retornaUltMew(tUsuario *usuario){
  return usuario->ultMew;
}

void resetaUltMew(tUsuario *usuario){
  usuario->ultMew = 0;
}

void resetaUltAtaqueFugas(tUsuario *usuario){
  usuario->atacou = 0;
  usuario->tentativasFuga = 0;
}

void incrementaBatalhas(tUsuario *usuario){
  usuario->qtdBatalha++;
}

int retornaQtdBatalhas(tUsuario *usuario){
  return usuario->qtdBatalha;
}

int incrementaUltimaPokebola(tUsuario *usuario){
  usuario->ultimaPokebola++;
  return usuario->ultimaPokebola;
}

void incrementaPokebola(tUsuario *usuario){
  usuario->qtdPokebola++;
  usuario->ultimaPokebola = 0;
}

void decrementaPokebola(tUsuario *usuario){
  usuario->qtdPokebola--;
}

int retornaQtdPokebola(tUsuario *usuario){
  return usuario->qtdPokebola;
}

char *retornaNome(tUsuario *usuario){
  return usuario->nome;
}

void incrementaVitoria(tUsuario *usuario){
  usuario->qtdVitorias++;
  usuario->ultMew++;
}

void setaAtaque(tUsuario *usuario){
  usuario->atacou = 1;
}

void incrementaFuga(tUsuario *usuario){
  usuario->tentativasFuga++;
}

int retornaCondicaoAtaque(tUsuario *usuario){
  return usuario->atacou;
}

int retornaFugas(tUsuario *usuario){
  return usuario->tentativasFuga;
}