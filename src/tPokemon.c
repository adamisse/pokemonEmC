#include "../include/tPokemon.h"
#include "../include/tGolpes.h"
#include "../include/tInicializa.h"
#include "../include/tBatalha.h"

struct Pokemon{
  char *nome;
  char tipo;
  int ataque, defesa;
  float hp,hpMax;
  int chamas,paralisado,dormindo[2],protegido,cavando;
  int foiDormido[2];
  fptrAtaque golpe[3];
  tPokemon *next;
};

fptrPokemons fptrPokemonsArray[6];


void preencheVetorFptr(){
  fptrPokemonsArray[0] = preencheAtaquesPikachu;
  fptrPokemonsArray[1] = preencheAtaquesCharizard;
  fptrPokemonsArray[2] = preencheAtaquesVenusaur;
  fptrPokemonsArray[3] = preencheAtaquesBlastoise;
  fptrPokemonsArray[4] = preencheAtaquesStelix;
  fptrPokemonsArray[5] = preencheAtaquesMew;
}

void administraPokemon(tPokemon *pokemon,int cod){
  fptrPokemons aux = fptrPokemonsArray[cod];
  aux(pokemon);
}
void preencheAtaquesPikachu(tPokemon *pokemon){
  pokemon->golpe[0] = choqueDoTrovao;
  pokemon->golpe[1] = ondaDeChoque;
  pokemon->golpe[2] = bater;
}
void preencheAtaquesCharizard(tPokemon *pokemon){
  pokemon->golpe[0] = lancaChamas;
  pokemon->golpe[1] = dormir;
  pokemon->golpe[2] = bater;
}
void preencheAtaquesVenusaur(tPokemon *pokemon){
  pokemon->golpe[0] = poDeSono;
  pokemon->golpe[1] = bombaDeSemente;
  pokemon->golpe[2] = doisGumes;
}
void preencheAtaquesBlastoise(tPokemon *pokemon){
  pokemon->golpe[0] = armaDeAgua;
  pokemon->golpe[1] = proteger;
  pokemon->golpe[2] = bater;
}
void preencheAtaquesMew(tPokemon *pokemon){
  pokemon->golpe[0] = metronomo;
  pokemon->golpe[1] = bater;
  pokemon->golpe[2] = autoDestruir;
}
void preencheAtaquesStelix(tPokemon *pokemon){
  pokemon->golpe[0] = raboDeFerro;
  pokemon->golpe[1] = dormir;
  pokemon->golpe[2] = cavar;
}

tPokemon *alocaPokemon(tPokemon *pokemon){
  pokemon = (tPokemon *)malloc(sizeof(tPokemon));
  
  if(pokemon == NULL){
    printf("Erro na alocação de Pokemon.\n");
    exit(1);
  }
  return pokemon;
}

tPokemon *trocaLiberaPokemon(tPokemon *pokemon){
  tPokemon *proximoPokemon;
  tPokemon *atualPokemon;

  atualPokemon = pokemon;
  printf("Seu %s foi derrotado!\n", atualPokemon->nome);
  proximoPokemon = atualPokemon->next;

  free(atualPokemon->nome);
  free(atualPokemon);

  atualPokemon = proximoPokemon;
  if(atualPokemon != NULL)
    printf("Seu pokemon atual trocou para %s.\n\n",atualPokemon->nome);

  return atualPokemon;
}

void liberaPokemonSelvagem(tPokemon *pokemon){
  free(pokemon->nome);
  free(pokemon);
  pokemon = NULL;
}

void capturaPokemon(tPokemon *pokemon,char *nome){
  tPokemon *atualPokemon = pokemon;
  tPokemon *proximoPokemon = NULL;
  while(1){
    proximoPokemon = atualPokemon->next;
    if(proximoPokemon == NULL){
      proximoPokemon = alocaPokemon(proximoPokemon);
      procuraPokemonArq(proximoPokemon, nome);

      proximoPokemon->next = NULL;
      atualPokemon->next = proximoPokemon;
      break;
    }else{
      atualPokemon = atualPokemon->next;
    }
  }
}

void resetaStatus(tPokemon *pokemon){
  pokemon->foiDormido[0] = OF;
  pokemon->dormindo[0] = OF;
  pokemon->protegido = OF;
  pokemon->paralisado = OF;
  pokemon->chamas = OF;
  pokemon->cavando = OF;

  if(pokemon->hp + 10.0 <= pokemon->hpMax)
    pokemon->hp = pokemon->hp + 10.0;

  else pokemon->hp = pokemon->hpMax;
}

void procuraPokemonArq(tPokemon *pokemon, char *nome){
  FILE *arq = fopen("dir/pokemons.csv","r");
  verificaAbertura(arq);

  char linha[100], *nomeAux;
  int aux=0;
  while(fgets(linha,100,arq)){
    nomeAux = strtok(linha,",");
    if(strcmp(nomeAux,nome) == 0){
      inicializaDados(pokemon, aux);
      break;
    }
    aux++;
  }
  fclose(arq);
}

void inicializaDados(tPokemon *pokemon, int cod){
  FILE *arq = fopen("dir/pokemons.csv", "r");
  verificaAbertura(arq);
  char linha[150], *nomeAux, *hpAux, *atqAux, *defAux, *tipoAux;
  int i=0;
  while(fgets(linha, 150, arq)){
    if(i == cod){
      nomeAux = strtok(linha,",");
      hpAux = strtok(NULL,",");
      atqAux = strtok(NULL,",");
      defAux = strtok(NULL,",");
      tipoAux = strtok(NULL,",");

      pokemon->hp = convertStringInt(hpAux)/1.0;
      pokemon->hpMax = pokemon->hp;
      pokemon->ataque = convertStringInt(atqAux);
      pokemon->defesa = convertStringInt(defAux);
      pokemon->tipo = tipoAux[0];
      resetaStatus(pokemon);
      
      pokemon->nome = alocaString(pokemon->nome,strlen(nomeAux)+1);
      strcpy(pokemon->nome,nomeAux);

      administraPokemon(pokemon, cod);
      break;
    }
    i++;
  }
  fclose(arq);
}

void verificaAbertura(FILE *arq){
  if(arq == NULL){
    printf("Erro na abertura de arquivo.\n");
    exit(1);
  }
}

void printaPokemons(char pokemons[7][30],int tam){
  for(int i=0; i<tam ;i++){
    printf("%d- %s\n",i+1,pokemons[i]);
  }
}

void trocaOrdem(char pokemons[7][30],int escolhido){
  for(int i=0; i<6 ;i++){
    if(i == escolhido){
      strcpy(pokemons[6],pokemons[i]);
    }
    if(i >= escolhido){
      strcpy(pokemons[i],pokemons[i+1]);
    }
  }
}

int capturaEscolha(int limite){
  int escolhido;
  do{
    scanf("%d",&escolhido);
  }while(escolhido > limite || escolhido < 1);
  return escolhido;
}

void escolhePokemon(tUsuario *usuario,tFilaUsuario *referencia, char *arqP, char *arqL){
  printf("Escolha seus 3 iniciais:\n");
  char pokemons[7][30];
  int op;

  tPokemon *pokemon = NULL;
  tPokemon *referenciaPokemon = alocaPokemon(referenciaPokemon);

  strcpy(pokemons[0],"Pikachu");
  strcpy(pokemons[1],"Charizard");
  strcpy(pokemons[2],"Venusaur");
  strcpy(pokemons[3],"Blastoise");
  strcpy(pokemons[4],"Steelix");
  strcpy(pokemons[5],"Mew"); 

  for(int i=6; i>3 ;i--){
    if(i == 5) printf("Mais um:\n");
    else if(i == 4) printf("Agora o último:\n");

    printaPokemons(pokemons, i);
    op = capturaEscolha(i);

    if(i == 6){
      pokemon = referenciaPokemon;
      procuraPokemonArq(pokemon,pokemons[op-1]);
      pokemon->next = NULL;
    }
    else{
      pokemon->next = alocaPokemon(pokemon->next);
      pokemon = pokemon->next;
      procuraPokemonArq(pokemon,pokemons[op-1]); 
      pokemon->next = NULL;
    }

    trocaOrdem(pokemons, op-1);
    system("clear");
  }
  
  iniciaBatalha(usuario,referenciaPokemon,referencia,arqP,arqL);
}

char *nomePokemon(tPokemon *pokemon){
  return pokemon->nome;
}

float porcentagemVida(tPokemon *pokemon){
  float porcentagem = pokemon->hp/pokemon->hpMax;
  return porcentagem * 100;
}

float retornaHpAtual(tPokemon *pokemon){
  return pokemon->hp;
}

float retornaHpMax(tPokemon *pokemon){
  return pokemon->hpMax;
}

void statusQueimando(tPokemon *pokemon){
  if(pokemon->chamas == ON){
    pokemon->hp = pokemon->hp - (pokemon->hpMax/16.0);
    printf("%s tomou %.2f de dano por estar em chamas!\n", pokemon->nome, (pokemon->hpMax/16.0));
    if(pokemon->hp < 0){
      printf("%s morreu queimado!\n", pokemon->nome);
      pokemon->hp = 0.0;
    }
  }
}

int statusParalisiaDormindo(tPokemon *pokemon){
  int passaRodada = 0;
  if(pokemon->paralisado == ON){
    printf("%s está paralisado e não pode se mover!\n\n", pokemon->nome);
    pokemon->paralisado = OF;
    
    passaRodada = 1;
  }
  if(pokemon->dormindo[0] == ON || pokemon->foiDormido[0] == ON){
    if(pokemon->dormindo[0] == ON){
      pokemon->dormindo[1]--;
      if(pokemon->dormindo[1] != 0){
        printf("%s está dormindo. . .\n\n", pokemon->nome);
      }else{
        printf("%s Acordou e regenerou toda a sua vida!\n\n", pokemon->nome);
        pokemon->hp = pokemon->hpMax;
        pokemon->dormindo[0] = OF;
      }
    }

    if(pokemon->foiDormido[0] == ON){
      pokemon->foiDormido[1]--;
      if(pokemon->foiDormido[1] != 0){
        printf("%s não pode agir pois foi desmaiado. . .\n\n", pokemon->nome);
      }else{
        pokemon->foiDormido[0] = OF;
        printf("%s Acordou!\n\n", pokemon->nome);
      }
    }
    passaRodada = 1;
  }

  return passaRodada;
}

void paralisia(tPokemon *pokemon, int divisor){
  int probabilidade = rand() % divisor;
  if(probabilidade == 0){
    pokemon->paralisado = ON;
    printf("%s foi Paralisado\n",pokemon->nome);
  }
}

int danoCavando(tPokemon *pokemonAtq,tPokemon *pokemonDfs){
  int passaRodada = 0;
  if(pokemonAtq->cavando == ON){
    pokemonAtq->cavando = OF;
    passaRodada = 1;
    
    printf("%s saiu da terra!\n\n",pokemonAtq->nome);
    if(pokemonDfs->protegido == ON){
      printf("%s Protegeu-se.\n",pokemonDfs->nome);
      pokemonDfs->protegido = OF;
    }else{
      int crit = sorteiaCritico();
      float modificador = 1.0*crit*administraTipos(pokemonAtq->tipo,pokemonDfs->tipo);
      float dano = calculaDano(80,pokemonAtq->ataque,pokemonDfs->defesa,modificador);
      pokemonDfs->hp = pokemonDfs->hp - dano;
      if(pokemonDfs->hp < 0.0) pokemonDfs->hp = 0.0;
      printf("%s: %.2f%% HP\n", pokemonAtq->nome, porcentagemVida(pokemonAtq));
      printf("%s: %.2f%% HP\n\n", pokemonDfs->nome, porcentagemVida(pokemonDfs));
    }
  }
  return passaRodada;
}

void printaStatus(FILE *arq,tPokemon *pokemon){
  if(pokemon->paralisado == ON){
    fprintf(arq,"(paralisado");
    if(pokemon->dormindo[0]==ON || pokemon->foiDormido[0]==ON){
      fprintf(arq,", dormindo");
    }
    if(pokemon->chamas==ON){
      fprintf(arq,", chamas");
    }
    fprintf(arq,")");
  }else if(pokemon->dormindo[0]==ON || pokemon->foiDormido[0]==ON){
    fprintf(arq,"(dormindo");
    if(pokemon->chamas==ON){
      fprintf(arq,", chamas");
    }
    fprintf(arq,")");
  }else if(pokemon->chamas== ON){
    fprintf(arq,"(chamas)");
  }
  fprintf(arq,"\n");
}

void resetaProtegido(tPokemon *pokemon){
  pokemon->protegido = OF;
}

void ativaProtegido(tPokemon *pokemon){
  pokemon->protegido = ON;
}

int retornaProtegido(tPokemon *pokemon){
  return pokemon->protegido;
}

void executaGolpe(tPokemon *Pokatq, tPokemon *Pokdef,int num,char *arqL){
  Pokatq->golpe[num](Pokatq,Pokdef,arqL);
}

char retornaTipo(tPokemon *pokemon){
  return pokemon->tipo;
}

void setaVidaNegativa(tPokemon *pokemon){
  pokemon->hp = -1.0;
}

void setaVidaZero(tPokemon *pokemon){
  pokemon->hp = 0.0;
}

int retornaAtaque(tPokemon *pokemon){
  return pokemon->ataque;
}

int retornaDefesa(tPokemon *pokemon){
  return pokemon->defesa;
}

void descontaVida(tPokemon *pokemon, float dano){
  pokemon->hp = pokemon->hp - dano;
  if(pokemon->hp < 0.0) pokemon->hp = 0.0;
}

void ativaChamas(tPokemon *pokemon){
  pokemon->chamas = ON;
}

void ativaDormir(tPokemon *pokemon, int condicao, int qtdTurnos){
  if(condicao == 1){
    pokemon->dormindo[0] = ON;
    pokemon->dormindo[1] = 2;
  }else{
    pokemon->foiDormido[0] = ON;
    pokemon->foiDormido[1] = qtdTurnos;
  }
}

void ativaCavar(tPokemon *pokemon){
  pokemon->cavando = ON;
}