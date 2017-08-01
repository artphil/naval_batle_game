#!/bin/bash

gcc -c src/game.c -o obj/game.o -Wall
gcc -c src/player.c -o obj/player.o -Wall
gcc -c src/board.c -o obj/board.o -Wall
gcc -c src/target.c -o obj/target.o -Wall
gcc -c src/messages.c -o obj/messages.o -Wall
gcc -c src/main.c -o obj/main.o -Wall

gcc -o nav_bat.exe obj/main.o obj/game.o obj/player.o obj/board.o obj/target.o obj/messages.o
