############ MAKEFILE #############
######## LEGENDA #########
#$@	Nome da regra.
#$<    	Nome da primeira dependência
#$^     Lista de dependências
#$?     Lista de dependências mais recentes que a regra.
#$*     Nome do arquivo sem sufixo
##########################################################



CC = gcc
CFLAGS = -Wall
P_SRC = src/
P_OBJ = obj/
SRC = game.c player.c board.c target.c main.c
OBJ= $(SRC:.c=.o)
EXEC = nav_bat.exe


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(P_OBJ)main.o $(P_OBJ)game.o $(P_OBJ)player.o $(P_OBJ)board.o $(P_OBJ)target.o -o nav_bat.exe $(CFLAGS)

target.o: $(P_SRC)target.c
	$(CC) -c $(P_SRC)target.c -o $(P_OBJ)target.o $(CFLAGS)

player.o: $(P_SRC)player.c
	$(CC) -c $(P_SRC)player.c -o $(P_OBJ)player.o $(CFLAGS)

board.o: $(P_SRC)board.c
	$(CC) -c $(P_SRC)board.c -o $(P_OBJ)board.o $(CFLAGS)

game.o: $(P_SRC)game.c
	$(CC) -c $(P_SRC)game.c -o $(P_OBJ)game.o $(CFLAGS)

main.o: $(P_SRC)main.c
	$(CC) -c $(P_SRC)main.c -o $(P_OBJ)main.o $(CFLAGS)

clear:
	rm $(P_OBJ)*.o  $(EXEC)
