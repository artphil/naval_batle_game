###########################################################
#        Implementacao em C do jogo Batalha Naval         #
#                    ArtPhil © 2017                       #
###########################################################

######################## MAKEFILE #########################

######################### LEGENDA #########################
#$@	Nome da regra.
#$<    	Nome da primeira dependência
#$^     Lista de dependências
#$?     Lista de dependências mais recentes que a regra.
#$*     Nome do arquivo sem sufixo
##########################################################

###################### VARIAAVEIS ########################

CC = gcc
CFLAGS = -Wall
P_SRC = src/
P_OBJ = obj/
SRC = game.c player.c board.c target.c messages.c main.c
OBJ= $(SRC:.c=.o)
EXEC = nav_bat.exe

####################### EXECUCAO #########################

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo "Vendendo ingressos"
	@$(CC) -o $(EXEC) $(P_OBJ)main.o $(P_OBJ)game.o $(P_OBJ)player.o $(P_OBJ)board.o $(P_OBJ)target.o $(P_OBJ)messages.o
	@echo "OK. pode comecar o jogo"

target.o: $(P_SRC)target.c
	@echo "Praticando pontaria"
	@$(CC) -c $(P_SRC)target.c -o $(P_OBJ)target.o $(CFLAGS)

player.o: $(P_SRC)player.c
	@echo "Apresentando jogadores"
	@$(CC) -c $(P_SRC)player.c -o $(P_OBJ)player.o $(CFLAGS)

board.o: $(P_SRC)board.c
	@echo "Retirando os peixes"
	@$(CC) -c $(P_SRC)board.c -o $(P_OBJ)board.o $(CFLAGS)

game.o: $(P_SRC)game.c
	@echo "Distribuindo pecas"
	@$(CC) -c $(P_SRC)game.c -o $(P_OBJ)game.o $(CFLAGS)

messages.o: $(P_SRC)messages.c
	@echo "Contratando narradores"
	@$(CC) -c $(P_SRC)messages.c -o $(P_OBJ)messages.o $(CFLAGS)


main.o: $(P_SRC)main.c
	@echo "Conferindo o sistema"
	@$(CC) -c $(P_SRC)main.c -o $(P_OBJ)main.o $(CFLAGS)

clear:
	@echo "Apagando rastros"
	rm $(P_OBJ)*.o
	rm $(EXEC)
	@echo "Pronto, mas nao conte para ninguem!"
