#include "../include/tGolpes.h"

fptrTipoAtacante fptrTipoAtacanteArray[91];
fptrAtaque fptrAtaqueAleatorio[13];


void preencheAtacante(){
  fptrTipoAtacanteArray['E'] = atacanteElectric;
  fptrTipoAtacanteArray['S'] = atacanteSteel;
  fptrTipoAtacanteArray['F'] = atacanteFire;
  fptrTipoAtacanteArray['W'] = atacanteWater;
  fptrTipoAtacanteArray['P'] = atacantePsychic;
  fptrTipoAtacanteArray['G'] = atacanteGrass;
}

float administraTipos(char tAtacante, char tDefensivo){
  fptrTipoAtacante aux = fptrTipoAtacanteArray[tAtacante];

  return aux(tDefensivo);
}

float atacanteElectric(char defesa){
  if(defesa == 'W') return 2;
  else if(defesa == 'G' || defesa == 'E') return 0.5;
  return 1;
}
float atacanteSteel(char defesa){
  if(defesa == 'E' || defesa == 'F' || defesa == 'W' || defesa == 'S') return 0.5;
  return 1;
}
float atacanteFire(char defesa){
  if(defesa == 'F' || defesa == 'W') return 0.5;
  else if(defesa == 'G' || defesa == 'S') return 2;
  return 1;
}
float atacanteWater(char defesa){
  if(defesa == 'F') return 2;
  else if(defesa == 'W' || defesa == 'G') return 0.5;
  return 1;
}
float atacantePsychic(char defesa){
  if(defesa == 'P' || defesa == 'S') return 0.5;
  return 1;
}
float atacanteGrass(char defesa){
  if(defesa == 'F' || defesa == 'G' || defesa == 'S') return 0.5;
  else if(defesa == 'W') return 2;
  return 1;
}

void preencheAtaqueAleatorio(){
  fptrAtaqueAleatorio[0] = choqueDoTrovao;
  fptrAtaqueAleatorio[1] = ondaDeChoque;
  fptrAtaqueAleatorio[2] = bater;
  fptrAtaqueAleatorio[3] = lancaChamas;
  fptrAtaqueAleatorio[4] = dormir;
  fptrAtaqueAleatorio[5] = armaDeAgua;
  fptrAtaqueAleatorio[6] = proteger;
  fptrAtaqueAleatorio[7] = poDeSono;
  fptrAtaqueAleatorio[8] = bombaDeSemente;
  fptrAtaqueAleatorio[9] = doisGumes;
  fptrAtaqueAleatorio[10] = raboDeFerro;
  fptrAtaqueAleatorio[11] = cavar;
  fptrAtaqueAleatorio[12] = autoDestruir;
}

float calculaDano(int poder,int ataque,int defesa,float modificador){
  float dano = ((14*poder*ataque/defesa)/50.0 + 2) * modificador;
  return dano;
}

int sorteiaCritico(){
  int crit = rand() % 24;
  if(crit == 0){
    printf(". . . Um golpe crítico!\n");
    return 2;
  } 
  else return 1;
}

void choqueDoTrovao(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Choque do Trovão.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Choque do Trovão\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    float MT = 1.5;
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);

    if(tipoAtq == 'P') MT = 1.0;

    float modificador = MT*crit*administraTipos(tipoAtq,tipoDef); 
    float dano = calculaDano(40,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);

    paralisia(pokemonDef,10);
  }
  fclose(arqLog);
}

void ondaDeChoque(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Onda de Choque\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Onda de Choque\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if (protegido == ON) {
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else paralisia(pokemonDef,1);
  fclose(arqLog);
}

void bater(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){ 
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Bater.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Bater\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);

    float modificador = 1.0*crit*administraTipos(tipoAtq,tipoDef);
    float dano = calculaDano(40,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);
  }
  fclose(arqLog);
}

void lancaChamas(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);
  char *nomeDefensor = nomePokemon(pokemonDef);

  printf("%s usou Lança Chamas.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Lança Chamas\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    float MT = 1.5;
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);
    if(tipoAtq == 'P') MT = 1.0;

    float modificador = MT*crit*administraTipos(tipoAtq, tipoDef);
    float dano = calculaDano(90,ataque,defesa,modificador);  

    descontaVida(pokemonDef, dano);

    int queimadura = rand() % 10;
    if(queimadura == 0 && tipoDef != 'F'){
      printf("%s está em chamas!\n",nomeDefensor);
      ativaChamas(pokemonDef);
    }
  }
  fclose(arqLog);
}

void bombaDeSemente(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Bomba de Semente.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Bomba de Semente\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){ 
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    float MT = 1.5;
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);
    if(tipoAtq == 'P') MT = 1.0;

    float modificador = MT*crit*administraTipos(tipoAtq,tipoDef);
    float dano = calculaDano(80,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);
  }
  fclose(arqLog);
}

void doisGumes(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){ 
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Dois Gumes.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Dois Gumes\n", nomeAtacante);

  int crit = sorteiaCritico();
  char tipoAtq = retornaTipo(pokemonAtq);
  char tipoDef = retornaTipo(pokemonDef);
  int ataque = retornaAtaque(pokemonAtq);
  int defesa = retornaDefesa(pokemonDef);

  float modificador = 1.0*crit*administraTipos(tipoAtq,tipoDef);
  float dano = calculaDano(120,ataque,defesa,modificador);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
    
    descontaVida(pokemonAtq, dano/3.0);
  }else{
    descontaVida(pokemonDef, dano);
    descontaVida(pokemonAtq, dano/3.0);
  }
  fclose(arqLog);
}

void armaDeAgua(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Arma de Água.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Arma de Água\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    float MT = 1.5;
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);
    if(tipoAtq == 'P') MT = 1.0;

    float modificador = MT*crit*administraTipos(tipoAtq, tipoDef);
    float dano = calculaDano(40,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);
  }
  fclose(arqLog);
}

void raboDeFerro(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Rabo de Ferro.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Rabo de Ferro\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int crit = sorteiaCritico();
    float MT = 1.5;
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);
    if(tipoAtq == 'P') MT = 1.0;

    float modificador = MT*crit*administraTipos(tipoAtq, tipoDef);
    float dano = calculaDano(100,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);
  }
  fclose(arqLog);
}

void autoDestruir(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){ 
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Auto-Destruir.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Auto-Destruir\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
    setaVidaZero(pokemonAtq);
  }else{
    int crit = sorteiaCritico();
    char tipoAtq = retornaTipo(pokemonAtq);
    char tipoDef = retornaTipo(pokemonDef);
    int ataque = retornaAtaque(pokemonAtq);
    int defesa = retornaDefesa(pokemonDef);

    float modificador = 1.0*crit*administraTipos(tipoAtq, tipoDef);
    float dano = calculaDano(200,ataque,defesa,modificador);

    descontaVida(pokemonDef, dano);
    setaVidaZero(pokemonAtq);
  }
  fclose(arqLog);
}

void metronomo(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Metronomo.\n", nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Metronomo\n", nomeAtacante);

  int ataque = rand() % 13;

  fptrAtaque aux = fptrAtaqueAleatorio[ataque];
  aux(pokemonAtq,pokemonDef, arqL);
  fclose(arqLog);
}

void proteger(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Proteger.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Proteger\n", nomeAtacante);

  ativaProtegido(pokemonAtq);
  resetaProtegido(pokemonDef);

  fclose(arqLog);
}

void dormir(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Dormir.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Dormir\n", nomeAtacante);

  ativaDormir(pokemonAtq, 1, 0);

  resetaProtegido(pokemonDef);
  fclose(arqLog);
}

void poDeSono(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Pó de Sono.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Pó de Sono\n", nomeAtacante);

  int protegido = retornaProtegido(pokemonDef);
  if(protegido == ON){
    char *nomeDefensor = nomePokemon(pokemonDef);
    printf("%s Protegeu-se.\n",nomeDefensor);
    resetaProtegido(pokemonDef);
  }else{
    int turnos = rand() % 3;
    ativaDormir(pokemonDef, 2, turnos+1);
  }
  fclose(arqLog);
}

void cavar(tPokemon *pokemonAtq, tPokemon *pokemonDef, char *arqL){ 
  char *nomeAtacante = nomePokemon(pokemonAtq);

  printf("%s usou Cavar.\n",nomeAtacante);
  FILE *arqLog = fopen(arqL, "a+");
  verificaAbertura(arqLog);
  fprintf(arqLog, "%s usa Cavar\n",nomeAtacante);

  ativaProtegido(pokemonAtq);
  resetaProtegido(pokemonDef);
  
  ativaCavar(pokemonAtq);
  fclose(arqLog);
}