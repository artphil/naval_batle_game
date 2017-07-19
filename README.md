# naval_batle_game
© _ArtPhil_ 2017

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
    * [source](#source)
    * [makefile](#makefile)
* [Inteligencia](#inteligencia)
    * [Desafios](#desafios)
    * [Implementação](#implementação)

## Objetivo
O intuito  deste projeto é praticar os conceitos aprendidos durante curso de Sistemas de Informação da [UFMG](https://www.ufmg.br/) e desenvolver um jogo intuitivo e divertido.

## Batalha Naval
Batalha Naval é um jogo para dois jogadores, onde cada jogador que possue um tabuleiro e alguns barcos de tamanhos variados (mesma quantidade e tipo barcos).</br>
Cada jogador posiciona todos seus barcos em seu tabuleiro sem que o adversário veja, e após isso começa a batalha. Os jogadores
deveram acertar os barcos inimigos disparando tiros no tabuleiro adversário, cada um tem direito a um tiro por vez e os barcos só são destruídos se todas as suas partes são aingidas.</br>
O primeiro jogador que eliminar todos os barcos do adversário vence a partida.

## Instalação
Clone o repositório `$ git clone github.com/artphil7/naval_batle_game/` ou faça o [download](https://github.com/artphil7/naval_batle_game/archive/master.zip) do arquivo .zip e extraia-o.</br>
Compile código com o comando `$ make` (ou `$ gcc -o nav_bat.exe main.c game.c board.c player.c target.c` caso não tenha makefile).</br>
Recomendo o GCC, para Windows pode ser obtido através da instalação do  [MinGW](https://sourceforge.net/projects/mingw/files/).</br>
Execute o comando `$ ./nav_bat.exe` e seguir as istruções da tela.  

## Desenvolvimento e organização
Programa desenvolvido na _linguagem C_.</br>
Compilação pelo _GCC_ automatizado por _makefile_.</br>
Sitema de modularização por separação de _TAD's_ em _arquivos_ (.c .h).</br>
Organização do código ataves de principios do _Newspaper Order_.</br>
Nomes de _funções_ e _arquivos_ em inglês, _TAD's_ e _variaveis_ em português.</br>
Padronização de nomes em _snake case_ e chaveamento de funções por _brace style K&R_ (Kernighan & Ritchie)

## Arquivos
TODO: Descrição em alto nivel da implementação
### main
[main.c](src/main.c)
### game
[game.c](src/game.c)</br>
[game.h](src/game.h)
### player
[player.c](src/player.c)</br>
[player.h](src/player.h)
### board
[board.c](src/board.c)</br>
[board.h](src/board.h)
### target
[target.c](src/target.c)</br>
[target.h](src/target.h)
### source
[source.h](src/source.h)
### makefile
[makefile](makefile)

## Inteligencia
TODO: ddiscussão acerca de objetivos e resultados.
### Desafios
### Implementação
