/*
        Implementacao em C do jogo Batalha Naval
        Codigo para fins academicos
*/

/* Bibliotecas utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* Variaveis globais */
// Naves
#define CORVETA 2
#define SUBMARINO 3
#define FRAGATA 4
#define CRUZADOR 5
#define PORTA_AVIAO 6

#define BARCOS {"Corveta","Submarino","Fragata","Cruzador","Porta Aviões"}

/* Funcoes */
void print_board();

// funcoes antigas
void imprime_matriz();

void imprime_cpu();

void imprime_mascara();

void imprime_jogo();

int isere_barco (int barco, int y, int x, int dir, int matrizInsere[10][10]);

void preenche_barcos();

void preenche_cpu();

int player_joga (int *barcos);

int cpu_joga (int *barcos);

int jogar ();
