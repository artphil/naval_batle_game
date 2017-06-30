#include "source.h"
#include "target.h"

// Jogador
struct JOGADOR
{
        char  nome[20]; // Nome do jogador
        int   acertou;  // Se acertou o ultimo tiro
        int   pecas;     // O Tabuleiro desse jogador
        alvo  certos;   // Lista de tiros certos
};
typedef struct JOGADOR *jogador;

jogador new_jogador(char *nome);
void free_jogador(jogador j);
