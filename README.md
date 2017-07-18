# naval_batle_game

# Jogo Batalha Naval desenvolvido para fins acadêmicos

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
Para utilizar o programa é necessário compilar código utilizando o `GCC` (para Windows recomenda-se a instalação do  [MinGW](https://sourceforge.net/projects/mingw/files/)), que pode ser feito com o comando `$ make` (ou `gcc -o nav_bat.exe main.c game.c board.c player.c target.c` no Windows).</br>
Para rodar o jogo basta colocar o comando no terminal `$ ./nav_bat.exe` e seguir as istruções da tela.  

## Desenvolvimento e organização
Programa desenvolvido na `linguagem C`.</br>
Compilação pelo `GCC` automatizado por `makefile`.</br>
Sitema de modularização por separação de `TAD's` em `arquivos` (`.c .h`).</br>
Organização do código ataves de principios do `Newspaper order`.</br>
Nomes de `funções` e `arquivos` em inglês, `TAD's` e `variaveis` em português.</br>
Padronização de nomes em `snake case` e chaveamento de funções por `brace style K&R` (Kernighan & Ritchie)

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
