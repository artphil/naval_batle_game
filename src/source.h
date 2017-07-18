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

char   *limpa_tela;
int     tam_tabuleiro;

/* Definicao de variaveis globais constantes */

/*      Naves
Nome            Tamanho
Corveta         2
Submarino       3
Fragata         4
Cruzador        5
Porta Aviões    6
*/

#define QTD_BARCOS 5
// Matriz
#define NAVE  'H'
#define AGUA  '.'
#define SUJO  '@'
// Mascara
#define DANO  '#'
#define ERRO  'x'
#define NADA  '~'

// Cores do terminal
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YLW   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

// Numero mensagens
#define QTD_MSGS_ACERTOU 4
#define QTD_MSGS_ERROU 4

// Simplifacacao de funcoes
#define loop(i,a) for(i=0;i<a;i++)

#endif
