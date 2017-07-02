#include "source.h"
#include "game.h"

// Identifica qual sistema esta sendo usado (Linux/Windows/OSX)
void sistema();

int main ()
{
        char continuar = 'n';

        srand(time(NULL));
        sistema();

        do {
                game();
                printf("Deseja jogar novamente? (y-n)\n");
                scanf(" %c", &continuar);
        } while (continuar == 'y');

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
