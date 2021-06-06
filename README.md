##Para jogar o game, basta compilar os arquivos através do "Make", e após digitar o comando de execução do arquivo compilado, você deverá fornecer outras 3 entradas, respectivamente correspondentes a: arquivo de saída dos placares de cada rodada, arquivo de saída do log das batalhas e seed de aleatoriedade do jogo. 

Exemplo de uma execução bem sucedida: 

$ make

$ ./tp2 dir/para/placares.txt dir/para/logs.txt 42

# Função Main

Dando início ao trabalho, apresentamos a função main. Primeiramente vale destacar a passagem de parâmetro para essa função, tais parâmetros correspondentes aos nomes dos arquivos de saída, log e pontuação, e uma string que representa a nossa semente de aleatoriedade. Com a captura de tais elementos, podemos dar início a nossa função, que, num primeiro momento, faz uma verificação da quantidade das strings de parâmetro (evitando assim um possível Segmentation Fault caso o usuário entre com parâmetros indevidos). 

Em sequência inicializamos nossa semente de aleatoriedade e chamamos funções que preencherão nossos vetores de ponteiro de função, garantindo assim que tais ações só ocorrem uma única vez ao decorrer do programa. Após tais acontecimentos, partimos para a inicialização da referência de nossa fila de usuário e finalizamos chamando a função de administração do menu inicial.

# Tipos Abstratos De Dados
	
## tInicializa

Dentre todos os TAD’s, esse foi o menos complexo, sendo responsável apenas pela chamada do menu inicial, realizando alguns controles de entrada e fornecendo ao usuário as três opções iniciais: 1- Jogar; 2- Lista de pontuações dos usuários; 3- Sair do programa. Chamando outras funções (contidas em tUsuario.h) para prosseguimento da lógica nos casos “1” e “2” ou realizando a liberação dos usuários caso o mesmo opte por sair do programa.

## tUsuario

Este TAD ficou responsável por conter as structs tUsuario e tFilaUsuario bem como todas as funções de acesso a elementos de tUsuario, pois vários destes foram utilizados em outros TAD’s de forma recorrente. Além disso, foi em tUsuario.c que fizemos as funções de captura, alocação, impressão e liberação do usuário ativo em nosso programa. Por fim, foi neste mesmo arquivo que realizamos a criação da fila de usuários através de uma lista encadeada, bem como sua lógica de ordenação e impressão, tanto no terminal quanto nos arquivos de saída.

## tPokemon

Foi em tPokemon.c que criamos a struct tPokemon que contém as informações básicas do pokémon, bem como seus atributos, golpes e status de batalha. No decorrer deste TAD foram criadas diversas funções para obter acesso aos elementos presentes dentro da struct (assim como em tUsuario), com o objetivo de trazer o paradigma de estrutura opaca para o nosso código. 

Logo depois das funções de acesso, criamos uma sequência de funções que tiveram por objetivo não apenas a iniciação, alocação, impressão e liberação do pokémon, mas também a lógica da modificação dos vários status presentes em tPokemon antes e durante cada uma das lutas, sendo que estas foram chamadas recorrentemente em tGolpes.c e tBatalha.c. 

Dentre os elementos fundamentais presentes neste TAD podemos citar a criação de fptr’s (ponteiros para funções), estes: fptrAtaque e fptrPokemons. Sendo que fptrAtaque é responsável pelo armazenamento das funções de golpes de cada pokémon dentro de um vetor golpe que contém 3 funções(representando os golpes do pokémon em questão). Enquanto fptrPokemons é responsável por fazer a chamada da função que lida justamente com o preenchimento do array de golpes de cada pokémon, desta forma, fptrPokemons tem por objetivo administrar qual tipo de função seria chamada para preencher fptrAtaque com as funções de golpes.

Por fim, este TAD também conteve funções que lidam com a lógica de escolha dos pokémons iniciais, criando uma lista encadeada dos pokémons selecionados pelo usuário bem como  a adição de novos pokémons capturados pelo usuário para dentro desta fila. 

## tGolpes

Partindo agora para o TAD de tGolpes, como pensamento fundamental, decidimos por criá-lo para armazenar as nossas funções dos ataque de cada pokémon, uma vez com esse pensamento, elaboramos as funções respectivas a cada golpe existente em nosso jogo, tais ataque utilizam por diversas vezes funcionalidades de acesso e modificação dos valores internos contidos nos strusts dos pokémons envolvidos na batalha, tais ferramentas encontram-se no TAD de tPokemon.

Nota-se a utilização da lógica de callBack duas vezes nesse TAD, primeiramente para funções que retornam um float multiplicador a julgar pelo tipo dos pokémons em combate, determinando assim a relação de efetividade dos ataque na hora de calcular o dano de uma habilidade, e em outro momentos, vemos de grande praticidade utilizar essa lógica para a execução do ataque Metrônomo, que por sua vez, executá outro ataque aleatório da lista em questão.


## tBatalha

Decidimos por armazenar nesse TAD as funcionalidades de administração do momento de transição e de combate entre os pokémons, ou seja, toda a lógica de turnos e execução de ações é conduzida nessa estrutura, que por muitas vezes utiliza de funcionalidades presentes nos TAD’s de tUsuario e tPokemon para acessar elementos internos de nossos structs, sendo esses elementos fundamentais para o funcionamento da tomada de decisões lógicas nas batalha.

Vale destacar a presença de uma lógica de callback para a exibição, de maneira apropriada, dos golpes de um respectivo pokémon pertencente ao usuário.	O programa permanece nesse TAD até que o usuário em questão perca a partida, uma vez acontecendo, nosso programa identifica tal acontecimento, cancelando a inicialização de uma nova batalha e parte para uma funcionalidade de adição do jogar em uma respectiva lista de jogadores (essa funcionalidade se encontra presente no TAD tUsuario), a qual poderá ser acessada ao partirmos para o menu inicial, exibindo assim o nome e a quantidade de vitórias de cada caçador.

#### Código elaborado por: Bruno Menegaz Acerbi e Matheus Adami Bernardes Moreira
