# naval_batle_game
_ArtPhil_ © 2017

# Jogo Batalha Naval desenvolvido para fins acadêmicos
Arthur Phillip Silva ([github](https://artphil7.github.io/)), </br>
graduando em **S**istemas de **I**nformação ([SI](http://dcc.ufmg.br/dcc/?q=pt-br/bsi)) </br>
pelo **D**epartamento de **C**iência da **C**omputação ([DCC](http://dcc.ufmg.br/dcc/)) </br>
da **U**niversidade **F**ederal de **M**inas **G**erais ([UFMG](https://www.ufmg.br/)).

* [Objetivos](#objetivos)
* [Batalha Naval](#batalha-naval)
* [Instalação](#instalação)
* [Desenvolvimento e organização](#desenvolvimento-e-organização)
* [Arquivos](#arquivos)
    * [main](#main)
    * [game](#game)
    * [player](#player)
    * [board](#board)
    * [target](#target)
    * [messages](#messages)
    * [source](#source)
    * [makefile](#makefile)
    * [lang/](#lang)
* [Inteligencia](#inteligencia)
    * [Desafios](#desafios)
    * [Implementação](#implementação)

## Objetivo
O intuito  deste projeto é praticar os conceitos aprendidos durante curso de Sistemas de Informação da [UFMG](https://www.ufmg.br/) e desenvolver um jogo intuitivo e divertido.

## Batalha Naval
Batalha Naval é um jogo para dois jogadores, onde cada jogador que possue um tabuleiro e alguns barcos de tamanhos variados (mesma quantidade e tipo barcos).

Cada jogador posiciona todos seus barcos em seu tabuleiro sem que o adversário veja, e após isso começa a batalha. Os jogadores
deveram acertar os barcos inimigos disparando tiros no tabuleiro adversário, cada um tem direito a um tiro por vez e os barcos só são destruídos se todas as suas partes são aingidas.

O primeiro jogador que eliminar todos os barcos do adversário vence a partida.

## Instalação
Clone o repositório `$ git clone github.com/artphil7/naval_batle_game/` ou faça o [download](https://github.com/artphil7/naval_batle_game/archive/master.zip) do arquivo .zip e extraia-o.

Compile código com o comando `$ make` (ou `$ gcc -o nav_bat.exe main.c game.c board.c player.c target.c` caso não tenha makefile).

Recomendo o GCC, para Windows pode ser obtido através da instalação do  [MinGW](https://sourceforge.net/projects/mingw/files/).

Execute o comando `$ ./nav_bat.exe` e seguir as istruções da tela.  

## Desenvolvimento e organização
Programa desenvolvido na _linguagem C_.</br>
Compilação pelo _GCC_ automatizado por _makefile_.</br>
Sitema de modularização por separação de _TAD's_ em _arquivos_ (.c .h).</br>
Organização do código ataves de principios do _Newspaper Order_.</br>
Nomes de _funções_ e _arquivos_ em inglês, _TAD's_ e _variaveis_ em português.</br>
Padronização de nomes em _snake case_ e chaveamento de funções por _brace style K&R_ (Kernighan & Ritchie)

## Arquivos

### main
Aqui o programa é iniciado as dependências são inicializadas, como a seleção de sistema operacional e lingua utilizada.</br>
[main.c](src/main.c)</br>

### game
Este é a principal parte do programa, onde é definido ou manipulado todo o ferramental necessário para o funcionamento do jogo. </br>
Todas as TADs são acessadas a partir desta e aqui estão as funções que manipulam mais de uma TAD como também as definições dos comportamentos automáticos e inteligência do jogo.</br>
[game.c](src/game.c)</br>
[game.h](src/game.h)</br>

### player
Onde são definidos os atributos de funções necessárias para a manipulação dos jogadores.</br>
[player.c](src/player.c)</br>
[player.h](src/player.h)</br>

### board
Aqui os tabuleiros são definido e manimulados.</br>
[board.c](src/board.c)</br>
[board.h](src/board.h)</br>

### target
Definições dos alvos utilizados pelas TADs _board_ e _player_.</br>
[target.c](src/target.c)</br>
[target.h](src/target.h)</br>

### messages
Todos os textos utilizados no jogo são manupulados por essa TAD, possibilitando o uso de outras linguas na utilização do jogo.</br>
Os textos utilizados aqui encontram-se na pasta _lang/_.</br>
[messages.c](src/messages.c)</br>
[messages.h](src/messages.h)</br>

### source
Arquivo, chamado por todos os outros, reune as variáveis globais do prorama, as definições e as inclusões de bibliotecas utilizadas pelos demais arquivos do programa.</br>
[source.h](src/source.h)</br>

### makefile
Automatização da compilação e organização de arquivos e objetos.</br>
[makefile](makefile)</br>

### lang/
linguas em que são possiveis jogar o Batalha Naval.</br>
Prortuguês : [pt-br](lang/pt-br.dat)</br>

## Inteligencia
A Inteligência do jogo consiste em como dispor os barcos no tabuleiro de forma a não ficarem muito fáceis de achar e em como encontrar o barco inimigo de maneira eficiente.

### Desafios
A disposição dos barcos deve ser de forma não repetitiva e menos agrupada possivel a fim de de não gerar metodos infaliveis de derrotar a máqiuina.

Para o ataque, os alvos devem ser escolhidos de tal forma que possibilite vencer a batalha no menor numero de rodadas, evitando que o inimigo o faça primeiro.

### Implementação
Para evitar repetições previsíveis utilizou-se de aleatoriedade com a função _rand()_ disponivel no _C_ com a semente de aleatoriedade sendo a hora global atual fornecida pela biblioteca _time_.

Para inserir os barcos no tabuleiro optou-se pela simplicidade, escolhendo  a posição e a orientação de forma aleatórias encontrou-se um resultado aceitável para as expectativas iniciais, pois tanto os barcos se configuraram de formas bem distintas a cada partida e como em média se espalhavam pelo tabuleiro de acordo com o esperado.

A Implementação pode ser encontrada na função fill_auto() no arquivo [game.c](src/game.c)

A escolha do alvo de ataque, a principio, é feita de forma aleatória, porém assim não se aproveita o fato das partes do barco ficarem adjascentes, por isso pensou-se em guardar o ultimo alvo com  sucesso, mas se errasse a direção escolhida e o próximo alvo falhasse a busca parava naquele ponto. Para resolver esse problema fez-se uma pilha e a cada sucesso armazenava-se todos os alvos em redor, o que possibilitava atingir o barco inteiro, mas gerava um desperdicio de tiros pois atingia todas as posições ao redor do barco. Por fim decediu-se por fazer uma verificação das casas em redor para selecionar apenas os alvos mais prováveis e chegou-se ao seguinte algoritmo:

> `Se existe alvos na pilha:`
> > `Seleciona proximo alvo.`

> `Senão:`
> > `Escolhe um alvo aleatório.`

> `Efetua o disparo.`

> `Se acertou:`
> > `Se existe alvos na pilha:`
> > > `Para cada direção:`
> > > > `Se acertou posição adjascente:`
> > > > > `Adiciona posição oposta na pilha.`

> `Senão:`
> > `Adiciona todas as pocições adjascentes.`

Com isso, quando um barco é encontrado, este é atingido por completo e só são gastos tiros na adjascencia do alvo inicial.

A Implementação pode ser encontrada na função play_auto() no arquivo [game.c](src/game.c)</br>
