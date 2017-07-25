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
        int continuar;

        srand(time(NULL));

        set_language ("pt-br");
        sistema ();

        do {
                game();
                // Deseja jogar novamente?
                printf("%s\n %s\n %s\n", \
                txt_perguntas.txt[0], txt_default.txt[6], txt_default.txt[7]);

                while ((continuar = read_char('1','2')) < 0)
                {
                        printf("%s\n", txt_falhas.txt[1]);
                }

        } while (continuar == 0);

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
