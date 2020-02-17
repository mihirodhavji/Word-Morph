#
#  Makefile para a 1a entrega do projeto de AED
#
#  Usage:
#     1) Para gerar o executavel do programa:
#         $ make wordmorph
#
#     2) Para limpar todos os ficheiros e objetos:
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -O3

#  Sources
SOURCES =  wordmorph.c fich.c words.c sorting.c grafos.c caminho.c estruturas.h

#  Objects
OBJECTS = wordmorph.o fich.o words.o sorting.o grafos.o caminho.o

wordmorph: $(OBJECTS)
	gcc -g -o $@ $(OBJECTS)

fich.o: fich.h fich.c 

words.o: words.h words.c

sorting.o: sorting.h sorting.c

grafos.o: grafos.h grafos.c

caminho.o: caminho.h caminho.c

clean::
	rm -f *.o core a.out wordmorph *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
