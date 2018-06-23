/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "boat.h"

void turn_boat(barco b)
{
	int aux = b.tamanho.x;
	b.tamanho.x = b.tamanho.y;
	b.tamanho.y = aux;	
}
