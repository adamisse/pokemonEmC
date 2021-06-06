#include "../include/tBatalha.h"
#include "../include/tInicializa.h"

fptrPrintaGolpes fptrPrintaGolpesArray[91];

void preenchePrintaGolpes(){
  fptrPrintaGolpesArray['E'] = golpesPikachu;
  fptrPrintaGolpesArray['F'] = golpesCharizard;
  fptrPrintaGolpesArray['G'] = golpesVenusaur;
  fptrPrintaGolpesArray['W'] = golpesBlastoise;
  fptrPrintaGolpesArray['S'] = golpesSteelix;
  fptrPrintaGolpesArray['P'] = golpesMew;
}

void printaGolpes(char code){
  fptrPrintaGolpes aux = fptrPrintaGolpesArray[code];
  aux();
}

void golpesPikachu(){
  printf("1- Choque do Trovão\n");
  printf("2- Onda de Choque\n");
  printf("3- Bater\n");
}
void golpesCharizard(){
  printf("1- Lança Chamas\n");
  printf("2- Dormir\n");
  printf("3- Bater\n");
}
void golpesVenusaur(){
  printf("1- Pó de sono\n");
  printf("2- Bomba de Semente\n");
  printf("3- Dois Gumes\n");
}
void golpesBlastoise(){
  printf("1- Arma de Água\n");
  printf("2- Proteger\n");
  printf("3- Bater\n");
}
void golpesSteelix(){
  printf("1- Rabo de Ferro\n");
  printf("2- Dormir\n");
  printf("3- Cavar\n");
}
void golpesMew(){
  printf("1- Metronomo\n");
  printf("2- Bater\n");
  printf("3- Auto-Destruir\n");
}

int capturaAcao(){
  int acao;
  char quebra;
  do{
    scanf("%d%c",&acao,&quebra); 
  }while((acao < 1 || acao > 5) || (quebra != '\n'));
  
  return acao;
}

tPokemon *geraPokemonSelvagem(tUsuario *usuario){
  tPokemon *pokemonSelvagem = NULL;
  pokemonSelvagem = alocaPokemon(pokemonSelvagem);

  int mew = rand() % 128;
  int ultMew = retornaUltMew(usuario);
  if(mew < ultMew){
    resetaUltMew(usuario);
    inicializaDados(pokemonSelvagem, 5);
  }else{
    int aleatoridade = rand() % 5;
    inicializaDados(pokemonSelvagem, aleatoridade);
  }

  return pokemonSelvagem;
}

void animacao(){
  sleep(1);
  printf(".\n");
  sleep(1);
  printf(".\n");
  sleep(1);
  printf(".\n");
  sleep(1);
  system("clear");
}

void iniciaBatalha(tUsuario *usuario, tPokemon *referencia,tFilaUsuario *referenciaUsuario,char *arqP, char *arqL){
  resetaUltAtaqueFugas(usuario);
  
  if(referencia == NULL){
    printf("Você perdeu.\n");

    quebraLinha();
    system("clear");
    adicionaFilaUsuario(usuario,referenciaUsuario,arqP,arqL);

  }else{
    tPokemon *pokemon = referencia;
    tPokemon *pokemonSelvagem;

    resetaStatus(pokemon);
    animacao();

    pokemonSelvagem = geraPokemonSelvagem(usuario);
    char *nomeSelvagem = nomePokemon(pokemonSelvagem);
    char *nomePokUsuario = nomePokemon(pokemon);

    printf("Um %s selvagem apareceu!\n\n", nomeSelvagem); 

    int qtdUsuario = tamFila(referenciaUsuario);
    int qtdBatalhas = retornaQtdBatalhas(usuario);
    incrementaBatalhas(usuario);
    
    FILE *arqLog = fopen(arqL,"a+");
    verificaAbertura(arqLog);
    fprintf(arqLog,"%d.%d- %s vs %s\n",qtdUsuario,qtdBatalhas,nomePokUsuario,nomeSelvagem);
    fclose(arqLog);

    batalhando(usuario,pokemon,pokemonSelvagem,referenciaUsuario,arqP,arqL);
  }
}

void sorteiaPokebola(tUsuario *usuario){
  int probabilidade = rand() % 12;
  int ultimaPokebola = incrementaUltimaPokebola(usuario);

  if(probabilidade < ultimaPokebola){
    animacao();
    
    printf("Você achou uma Pokebola!\n");
    incrementaPokebola(usuario);
    sleep(2);
    system("clear");
  }
}

void batalhando(tUsuario *usuario, tPokemon *pokemonUsuario,tPokemon *pokemonSelvagem,tFilaUsuario *referencia, char *arqP, char *arqL){
  while(1){
    rodadaUsuario(pokemonUsuario, pokemonSelvagem,usuario,arqL);
    float pokemonUsuarioHp = retornaHpAtual(pokemonUsuario);
    float pokemonSelvagemHp = retornaHpAtual(pokemonSelvagem);

    char *nomeUsuario = retornaNome(usuario);

    if(pokemonUsuarioHp == 0){
      pokemonUsuario = trocaLiberaPokemon(pokemonUsuario);
      if(pokemonUsuario == NULL){ 
        FILE *arqLog = fopen(arqL,"a+");
        verificaAbertura(arqLog);
        fprintf(arqLog,"%s perde!\n\n", nomeUsuario);
        fclose(arqLog);

        liberaPokemonSelvagem(pokemonSelvagem);
        break;   
      }
    }
    if(pokemonSelvagemHp == 0){
      liberaPokemonSelvagem(pokemonSelvagem);
      printf("Caçador %s venceu!\n",nomeUsuario);
      
      FILE *arqLog = fopen(arqL,"a+");
      verificaAbertura(arqLog);
      fprintf(arqLog,"%s vence!\n\n", nomeUsuario);

      incrementaVitoria(usuario);
      quebraLinha();
      system("clear");

      sorteiaPokebola(usuario);
      fclose(arqLog);
      break;
    }else if(pokemonSelvagemHp == -1.0){
      liberaPokemonSelvagem(pokemonSelvagem);

      sorteiaPokebola(usuario);
      break;
    }

    rodadaSelvagem(pokemonSelvagem, pokemonUsuario,arqL);

    pokemonUsuarioHp = retornaHpAtual(pokemonUsuario);
    pokemonSelvagemHp = retornaHpAtual(pokemonSelvagem);
    if(pokemonUsuarioHp == 0){
      pokemonUsuario = trocaLiberaPokemon(pokemonUsuario);
      if(pokemonUsuario == NULL){ 
        FILE *arqLog = fopen(arqL,"a+");
        verificaAbertura(arqLog);
        fprintf(arqLog,"%s perde!\n\n", nomeUsuario);
        fclose(arqLog);

        liberaPokemonSelvagem(pokemonSelvagem);
        break;     
      }
    }
    if(pokemonSelvagemHp == 0){
      liberaPokemonSelvagem(pokemonSelvagem);
      printf("Caçador %s venceu!\n", nomeUsuario);
      FILE *arqLog = fopen(arqL,"a+");
      verificaAbertura(arqLog);
      fprintf(arqLog,"%s vence!\n\n", nomeUsuario);
      
      incrementaVitoria(usuario);
      quebraLinha();
      system("clear");

      sorteiaPokebola(usuario);
      fclose(arqLog);
      break;
    }
  }
  iniciaBatalha(usuario, pokemonUsuario,referencia, arqP,arqL);
}

void rodadaSelvagem(tPokemon *pokemonSelvagem, tPokemon *pokemonUsuario, char *arqL){
  resetaProtegido(pokemonSelvagem);

  char *nomeSelvagem = nomePokemon(pokemonSelvagem);
  char *nomePokemonUsuario = nomePokemon(pokemonUsuario);

  printf("----- Turno de %s Selvagem -----\n", nomeSelvagem);
  statusQueimando(pokemonSelvagem);
  int condicional = statusParalisiaDormindo(pokemonSelvagem);
  if(condicional == 0){
    condicional = danoCavando(pokemonSelvagem,pokemonUsuario);
  }

  float pokemonSelvagemHp = retornaHpAtual(pokemonSelvagem);

  if(condicional == 0 && pokemonSelvagemHp != 0.0){
    int nGolpe = rand() % 3;
    executaGolpe(pokemonSelvagem, pokemonUsuario, nGolpe, arqL);
    printf("\n");
    printf("%s selvagem: %.2f%% HP\n", nomeSelvagem, porcentagemVida(pokemonSelvagem));
    printf("%s: %.2f%% HP\n\n", nomePokemonUsuario, porcentagemVida(pokemonUsuario));


    FILE *arqLog = fopen(arqL,"a+");
    verificaAbertura(arqLog);
    fprintf(arqLog,"%s: %.2f%% HP ",nomePokemonUsuario,porcentagemVida(pokemonUsuario));
    printaStatus(arqLog, pokemonUsuario);
    fprintf(arqLog,"%s: %.2f%% HP ",nomeSelvagem,porcentagemVida(pokemonSelvagem));
    printaStatus(arqLog, pokemonSelvagem);
    fprintf(arqLog,"\n");
    fclose(arqLog);
  }
  quebraLinha();
  system("clear");
}

void rodadaUsuario(tPokemon *pokemonUsuario, tPokemon *pokemonSelvagem,tUsuario *usuario, char *arqL){
  resetaProtegido(pokemonUsuario);

  char *nomeSelvagem = nomePokemon(pokemonSelvagem);
  char *nomePokemonUsuario = nomePokemon(pokemonUsuario);
  char *nomeUsuario = retornaNome(usuario);
  char tipo = retornaTipo(pokemonUsuario);
  int qtdPokebola = retornaQtdPokebola(usuario);
  float pokemonSelvagemHpMax = retornaHpMax(pokemonSelvagem);

  printf("----- Turno de %s -----\n", nomeUsuario);
  statusQueimando(pokemonUsuario);
  int condicional = statusParalisiaDormindo(pokemonUsuario);

  if(condicional == 0)
  condicional = danoCavando(pokemonUsuario,pokemonSelvagem);

  float pokemonUsuarioHp = retornaHpAtual(pokemonUsuario);
  float pokemonSelvagemHp = retornaHpAtual(pokemonSelvagem);

  if(condicional == 0 && pokemonUsuarioHp != 0.0){
    printf("%s selvagem: %.2f%% HP\n", nomeSelvagem, porcentagemVida(pokemonSelvagem));
    printf("%s: %.2f%% HP\n\n", nomePokemonUsuario, porcentagemVida(pokemonUsuario));
    
    printf("Escolha Um Movimento\n");
    printaGolpes(tipo);
    printf("4- Pokebola(%d disponíveis)\n",qtdPokebola);
    printf("5- Fugir\n");

    int acao = capturaAcao();
    while(acao == 4 && qtdPokebola <=0){
      printf("Sem mais Pokebolas!\n");
      acao = capturaAcao();
    }
    system("clear");
    if(acao < 4){
      setaAtaque(usuario);

      executaGolpe(pokemonUsuario, pokemonSelvagem, acao-1, arqL);
      printf("\n");
      printf("%s selvagem: %.2f%% HP\n", nomeSelvagem, porcentagemVida(pokemonSelvagem));
      printf("%s: %.2f%% HP\n\n", nomePokemonUsuario, porcentagemVida(pokemonUsuario));

      FILE *arqLog = fopen(arqL,"a+");
      verificaAbertura(arqLog);
      fprintf(arqLog,"%s: %.2f%% HP ",nomePokemonUsuario,porcentagemVida(pokemonUsuario));
      printaStatus(arqLog, pokemonUsuario);
      fprintf(arqLog,"%s: %.2f%% HP ",nomeSelvagem,porcentagemVida(pokemonSelvagem));
      printaStatus(arqLog, pokemonSelvagem);
      fprintf(arqLog,"\n");
      fclose(arqLog);
    }else{
      if(acao == 4 && qtdPokebola > 0){
        FILE *arqLog = fopen(arqL,"a+");
        verificaAbertura(arqLog);
        fprintf(arqLog,"Tentativa de Captura\n");

        float dividendo = pokemonSelvagemHpMax/pokemonSelvagemHp;
        int num = rand() % 20;
        animacao();
        if(num < dividendo){
          printf("Caçador %s capturou um %s selvagem!\n",nomeUsuario, nomeSelvagem);
          setaVidaZero(pokemonSelvagem);
          capturaPokemon(pokemonUsuario, nomeSelvagem);
          
          fprintf(arqLog,"Sucesso\n\n");
        }else{
          printf("Caçador %s não conseguiu capturar %s selvagem\n", nomeUsuario, nomeSelvagem);

          fprintf(arqLog,"Fracasso\n\n");
        }
        decrementaPokebola(usuario);
        
        fclose(arqLog);
      }else{
        FILE *arqLog = fopen(arqL,"a+");
        verificaAbertura(arqLog);
        fprintf(arqLog,"Tentativa de Fuga\n");
        
        incrementaFuga(usuario);
        int atacou = retornaCondicaoAtaque(usuario);
        int fugas = retornaFugas(usuario);

        if(atacou == 0){
          int aleatoriedade = rand() % 4;
          if(fugas > aleatoriedade){
            setaVidaNegativa(pokemonSelvagem);
            printf("Caçador %s fugiu!\n",nomeUsuario);

            fprintf(arqLog,"Sucesso\n\n");
          }else{
            printf("Fugir não foi efetivo. . .\n");

            fprintf(arqLog,"Fracasso\n\n");
          }
        }else{
          int aleatoriedade = rand() % 16;
          if(fugas > aleatoriedade){
            setaVidaNegativa(pokemonSelvagem);
            printf("Caçador %s fugiu!\n",nomeUsuario);
            
            fprintf(arqLog,"Sucesso\n\n");
          }else{
            printf("Fugir não foi efetivo. . .\n");

            fprintf(arqLog,"Fracasso\n\n");          
          }
        }
        fclose(arqLog);
      }
    }
  }
  quebraLinha();
  system("clear");
}