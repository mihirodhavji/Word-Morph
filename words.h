#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fich.h"
#include "sorting.h"

void initD (st_dicionario *);

char *LePalavra ( FILE * );

void ProcessaFicheiros(char *, char *, st_dicionario *);

void LeTotalDicionario(char *, st_dicionario *);

void PreencheDicionario ( char *, st_dicionario *);

void LeEntradaMut(char *, st_dicionario *);

int ProcuraBinaria(st_dicionario *, char [MAX_STR]);

void FreeDicionario(st_dicionario*);
