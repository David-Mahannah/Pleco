
CC = gcc
CFLAGS = -g

pleco: settings.c main.c
	gcc settings.c main.c -o pleco



clean:
	rm -f *.o
	rm -f pleco
