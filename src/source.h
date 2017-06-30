/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/
#ifndef _GLOBAL_
#define _GLOBAL_

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


/* Definicao de ariaveis globais constantes */

/*      Naves
Nome            Tamanho
Corveta         2
Submarino       3
Fragata         4
Cruzador        5
Porta Aviões    6
*/

#define QTD_BARCOS 5
#define NAVE  'H'
#define AGUA  '0'
#define SUJO  '@'
#define DANO  '#'
#define ERRO  'X'
#define NADA  '.'

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

#endif
