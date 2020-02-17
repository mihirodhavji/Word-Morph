#include "fich.h"

/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - ponteiro para string com o nome do ficheiro a abrir
 *            mode - ponteiro para string com o modo de abertura do ficheiro
 * Returns: ponteiro para ficheiro aberto
 * Side-Effects: sai se o ficheiro nao poder ser aberto
 *
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f;
  
  f = fopen ( nome, mode );
  if ( f == NULL) {
    exit (0);
  }
  return (f);
}

/******************************************************************************
 * NomeFichSaida()
 *
 * Argumentos: ficheiro - ponteiro para string com o nome do ficheiro de entrada
 *           
 * Retorna: ponteiro ponteiro para nome de ficheiro de saida
 * 
 * Copia e concatena o nome do ficheiro da entrada com a string '.stat'
 *
 ******************************************************************************/

char * NomeFichSaida (char *ficheiro)
{
	char *saida;
	saida = (char *) malloc((strlen(ficheiro)+2)*sizeof(char));
	ficheiro[strlen(ficheiro)-4] = '\0';
	strcpy ( saida, ficheiro);
	strcat ( saida, ".path" );
	return saida; 
}

/******************************************************************************
 * Verificacao()
 *
 * Argumentos: dicionario - ponteiro para string com o nome do dicionario
 * 			   pal - ponteiro para string com o nome do ficheiro de palavras
 *           
 * Side effects: sai do programa se houver problemas com a terminaçao dos 
 * 				ficheiros
 *
 ******************************************************************************/
void Verificacao (char *dicionario, char *pal)
{
	if(strstr(dicionario, ".dic") == NULL || strstr(pal, ".pal") == NULL)
		exit(0);	
}
