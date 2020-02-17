#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"

Acervo* CriaAcervo(int );

void initAcervo(Acervo *, int, int );

void FixUp(Acervo* , int );

void FixDown ( Acervo* A, int idx);

int AcervoMin( Acervo* );

void printCaminhoLinha(FILE *, int , st_dicionario *, int );

void printCaminho(FILE *, Acervo *, int , st_dicionario *, int, int);

void printNenhumCaminho(FILE *, int , int , st_dicionario *, int );

void Dijkstra(FILE *, Graph* , int, int , int, st_dicionario *, int);

void FreeAcervo(Acervo *A);
