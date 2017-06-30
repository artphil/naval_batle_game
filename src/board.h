#include "source.h"
#include "target.h"

typedef char** mesa;

void set_size(int t);

mesa new_mesa(char a);
//
void free_board(mesa m);
// Imprime uma tabela com a borda alfabetica
void print_board(mesa matriz);
void print_game(mesa m_a, mesa m_b);
int put_nav(mesa matriz, int barco, alvo a, int dir);
