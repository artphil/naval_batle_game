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


/* Defincoes */
// Definição do sistema operacional
#if defined(__linux__) || defined(__linux)
#define LINUX
#endif

#if defined(__APPLE__)
#define OSX
#endif

#if defined(__WIN32__) || defined(__NT__)
#define WINDOWS
#endif

char *limpa_tela;

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
#define AGUA  '.'
#define SUJO  '@'
#define DANO  '#'
#define ERRO  'o'
#define NADA  '~'

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

#endif
