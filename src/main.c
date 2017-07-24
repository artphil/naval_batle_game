/*
        Implementacao em C do jogo Batalha Naval
        ArtPhil © 2017
*/
#include "source.h"
#include "game.h"
#include "messages.h"


// Identifica qual sistema esta sendo usado (Linux/Windows/OSX)
void sistema();

int main ()
{
        char continuar = 'n';

        srand(time(NULL));

        set_language ("pt-br");
        sistema ();

        do {
                game();
                // printf("Deseja jogar novamente? (s/n)\n");
                printf("%s\n", txt_perguntas.txt[0]);
                scanf(" %c", &continuar);
        } while (continuar == 's');

        free_textos ();

        return 0;
}

void sistema()
{
        // código para windows
        #if defined(WINDOWS)
        limpa_tela = "cls";
        // código para linux
        #elif defined(LINUX)
        limpa_tela = "clear";
        // código para OS X.
        #elif defined(OSX)
        limpa_tela = "clear";
        #endif
}

void limpa_stdin()
{
        setbuf(stdin, 0);
}
