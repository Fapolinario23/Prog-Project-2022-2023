# Projeto Programação 2022/2023
#
# Francisco Apolinário, Rodrigo Sereno
#
# To compile prog: make
#----------------------------------------------------------------------

CC = gcc
CFLAGS = -Wall -O3 -g

CNAES: main.o candidatos.o cursos.o entry.o files.o
	$(CC) $(CFLAGS) -o CNAES main.o candidatos.o cursos.o entry.o files.o

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

candidatos.o: candidatos.c candidatos.h defs.h
	$(CC) -c $(CFLAGS) candidatos.c

cursos.o: cursos.c cursos.h defs.h
	$(CC) -c $(CFLAGS) cursos.c

entry.o: entry.c entry.h defs.h
	$(CC) -c $(CFLAGS) entry.c	

files.o: files.c files.h defs.h
	$(CC) -c $(CFLAGS) files.c	

clean:
	rm -f *.o CNAES *~
