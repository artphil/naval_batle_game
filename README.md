# naval_batle_game

# Jogo Batalha Naval desenvolvido para fins acadêmicos

* [Objetiivo](#objetivos)
* [Batalha Naval](#batalha-naval)
* [Desenvolvimento](#desenvolvimento)
* [Organização](#organização)
* [Arquivos](#arquivos)
 * [main](#main)
 * [game](#game)
 * [player](#player)
 * [board](#board)
 * [target](#target)
 * [source](#source)
 * [makefile](#makefile)

## Objetivo
O intuito  deste projeto é praticar os conceitos aprendidos durante curso de Sistemas de Informação da [UFMG](https://www.ufmg.br/).

## Batalha Naval
O jogo Batalha Naval consiste em dois tabuleiros e varios barcos de tamanhos variados.</br>
É jogado por dois jogadores que possuem, cada, um tabuleiro e alguns barcos (cada
jogador possue a mesma quantidade e tipo barcos).</br>
Cada jogador posiciona seus barcos em seu tabuleiro sem que o adversário veja, e
após todos os barcos estarem colocados nos tabuleiros começa a batalha. Os jogadores
deveram a certar os barcos inimigos disparando tiros no tabuleiro adversário, cada
um tem direito a um tiro por vez e os barcos só são destruídos se todas as suas
partes são aingidas.</br>
O primeiro jogador que eliminar todos os barcos do adversário vence a partida.

## Desenvolvimento
Programa desenvolvido na linguagem `C`.</br>
Compilação pelo `GCC` automizado por `makefile`.</br>

## Organização
Sitema de modularização por separação de `TAD's` em `arquivos` (`.c .h`).</br>
Organização do código ataves de principios do `Newspaper order`.</br>
Nomes de `funções` e `arquivos` em inglês, `TAD's` e `variaveis` em português.</br>
Padronização de nomes em `snake case` e chaveamento de funações por `brace style K&R` (Kernighan & Ritchie)

## Arquivos

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
