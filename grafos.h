#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caminho.h"

Graph* GRAPHinit(int);

link* NEW(int, link *, int);

void GRAPHinsertE(Graph *, int, int, int );

void FreeGraph (Graph *);

void ProcessaTestes(char *, st_dicionario *);

void CalculaCusto(st_dicionario *, int , int , int, int *);

Graph** AlocaVetorGrafo(void);

void BuildGrafo(Graph * ,st_dicionario *, int );
