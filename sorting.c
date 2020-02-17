#include "sorting.h"

/******************************************************************************
* Quicksort()
*
* Arguments:	dicio - dicionario de palavras
*				l - limite a esquerda 
*				r - limite a direita
* 				tam - tamanho da palavra
* 
* Returns: (none)
* Usa o algoritmo QuickSort para organizar alfabeticamente o dicionario 
*
*****************************************************************************/
void Quicksort(st_dicionario *dicio, int l, int r, int tam)
{

	int i, j, k, p, q;
	char *v = NULL;
 
	if (r <= l) return; /*Quando os limites cruzam*/

	v = dicio->palavra[tam][r]; /*vai buscar o pivot*/
	i = l-1; j = r; p = l-1; q = r;
 
	for (;;) 
	{
		while (strcmp(dicio->palavra[tam][++i], v) < 0) ;
		while (strcmp(v, dicio->palavra[tam][--j]) < 0) if (j == l) break;
		
		if (i >= j) break;
		
		exchpal(dicio->palavra[tam][i], dicio->palavra[tam][j]); /*exchange*/
		
		if(!strcmp(dicio->palavra[tam][i], v)) 
		{
			p++;
			exchpal(dicio->palavra[tam][p], dicio->palavra[tam][i]);/*exchange*/
		}
		
		if(!strcmp(v, dicio->palavra[tam][j]))
		{
			q--;
			exchpal(dicio->palavra[tam][q], dicio->palavra[tam][j]);/*exchange*/
		}
	}

	exchpal(dicio->palavra[tam][i], dicio->palavra[tam][r]); /*exchange*/
	
	j = i-1; i = i+1;
	
	for (k = l ; k < p; k++, j--) 
		exchpal(dicio->palavra[tam][k], dicio->palavra[tam][j]);/*exchange*/
		
	for (k = r-1; k > q; k--, i++) 
		exchpal(dicio->palavra[tam][k], dicio->palavra[tam][i]);/*exchange*/
	
	Quicksort(dicio, l, j, tam); Quicksort(dicio, i, r, tam);

	dicio->ordenado[tam] = 1; /*por a flag a 1 para dizer que esta ordenado*/
}

/******************************************************************************
* InteiroQuicksort()
*
* Arguments:	dicio - dicionario de palavras
* 
* Organiza todos os dicionarios que têm palavras
*
*****************************************************************************/
void InteiroQuicksort(st_dicionario *d)
{
	int i = 0;
	
	for(i = 0; i< MAX_STR ;i++)
		if(d->testes[i].quantidade != 0)
			Quicksort(d, 0,(d->ocorrencias[i] -1), i); 
			
	return;
}

/******************************************************************************
 * IsOrdenado()
 *
 * Arguments: 	dicio - dicionario
 * 				
 * Returns: 1 se ordenado, 0 se nao ordenado
 * 
 * Imprime o dicionario pela ordem em que esta
 *
 *****************************************************************************/
 int IsOrdenado(st_dicionario *dicio, char *palavra)
 {
	 return dicio->ordenado[(strlen(palavra)-1)];	 
 }
 
