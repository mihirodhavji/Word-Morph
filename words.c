#include "words.h"

/******************************************************************************
 * initD()
 *
 * Argumentos - ponteiro do tipo st_dicionario
 * Inicializa a zero os componentes da variavel deste tipo
 *
 *****************************************************************************/
void initD (st_dicionario *dicio)
{
	int i;
	for(i = 0; i < MAX_STR; i++){
		dicio->ocorrencias[i] = 0;
		dicio->ocupado[i] = 0;
		dicio->ordenado[i] = 0;
		dicio->testes[i].maxmut = 0;
		dicio->testes[i].quantidade = 0;	
	}
	return;
 }
 
/******************************************************************************
 * LePalavra()
 *
 * Argumentos - ponteiro para o ficheiro a ler
 * Retorna uma palavra lida do ficheiro
 *
 *****************************************************************************/

char *LePalavra ( FILE * f )
{
	static char palavra[MAX_STR];
	if ( fscanf ( f, "%s", palavra ) == 1 )
		return (palavra);
	else
		return ((char *) NULL);
}

/******************************************************************************
 * ProcessaFicheiros()
 *
 * Argumentos: 	dic - nome do ficheiro de dicionario
 * 			   	fichpal - nome do ficheiro de teste
 * Retorna: Nada
 *
 *
 * Processa os ficheiros de dicionario e de teste
 *
 ******************************************************************************/
void ProcessaFicheiros(char *dic, char *fichpal, st_dicionario *d)
{
	initD(d);
	LeEntradaMut(fichpal, d); /*Le o maior numero de mutacoes para cada tamanho de palavra no ficheiro .pal*/
	LeTotalDicionario (dic, d); /*Conta o numero total de palavras e o numero de palavras de cada tamanho*/
	PreencheDicionario(dic, d);	/*Preenche tabela de dicionario com as palavras do dicionario*/
	InteiroQuicksort(d);
}

/******************************************************************************
 * LeTotalDicionario()
 *
 * Argumentos: ficheiro - nome do ficheiro a analisar
 * 			   ocorr[] - vetor de inteiros para guardar o numero de palavras
 * 			  de cada tamanho
 * Retorna: Numero total de palavras no dicionario
 *
 * Conta o numero total de palavras e o numero de palavras de cada tamanho
 *
 ******************************************************************************/
void LeTotalDicionario(char *ficheiro, st_dicionario *dicio)
{
	FILE *fdic;
	char *palavra;

	fdic = AbreFicheiro ( ficheiro, "r" ); /*Abre dicionario*/

	while ( ( palavra = LePalavra ( fdic ) ) != NULL )
		if (dicio->testes[strlen(palavra)-1].quantidade != 0)
			dicio->ocorrencias[strlen(palavra)-1] += 1;	/*verifica qtas palavras ha para cada tamanho*/

	fclose ( fdic ); /*fecha o ficheiro de dicionario */
	return;
}

/******************************************************************************
 * PreencheDicionario()
 *
 * Arguments:	ficheiro - ponteiro para string com nome do ficheiro a ler
 *            	dicio - ponteiro para estrutura do dicionario
 * 				tot_pal - numero total de palavras no ficheiro
 * Returns: (none)
 *
 * Aloca memoria para as palavras e copia do ficheiro para a tabela
 *
 *****************************************************************************/
void PreencheDicionario ( char *ficheiro, st_dicionario *dicio)
{
	FILE *f;
	int i=0, tamanho = 0, pos = 0;
	char *palavra;
	dicio->palavra = (char ***) malloc(MAX_STR*sizeof(char **)); /*aloca memoria para o ponteiro para vetor de ponteiros*/
	if(dicio->palavra == NULL)
		exit(0);
	for(i = 0; i < MAX_STR; i++)
	{
		dicio->palavra[i] =  (char **) malloc ((dicio->ocorrencias[i])*sizeof(char*)); /*aloca memoria p vetor de ponteiros p strings*/
		if ( dicio->palavra[i] == NULL )
			exit (0);
	}
	f = AbreFicheiro ( ficheiro, "r" );
	while ( ( palavra = LePalavra ( f ) ) != NULL )
	{
		tamanho = strlen(palavra)-1;
		if (dicio->testes[tamanho].quantidade != 0)
		{
		    pos = dicio->ocupado[tamanho];
		    dicio->palavra[tamanho][pos] =  (char *) malloc ((tamanho+2)*sizeof(char)); /*aloca memoria para a palavra*/
		    if ( dicio->palavra[tamanho][pos] == NULL )
			     exit (0);

		    strcpy ( dicio->palavra[tamanho][pos], palavra ); /*copia a palavra para a tabela*/
		    dicio->ocupado[tamanho] += 1;
		}
	}
	fclose ( f );
	return;
}

/******************************************************************************
 * LeEntradaMut()
 *
 * Argumentos: ficheiro - nome do ficheiro a analisar
 *
 * Le o ficheiro de entrada e verifica as mutacoes assim como a quantidade de 
 * testes para cada tamanho de palavra
 *  
 ******************************************************************************/
void LeEntradaMut(char *ficheiro, st_dicionario *dicio)
{
	FILE *fpal;
	char p1[MAX_STR] = "\0" , p2[MAX_STR] = "\0";
	int mut = 0, ret = 0, t = 0, c = 0 , i = 0;
	
	fpal = AbreFicheiro ( ficheiro, "r" ); /*Abre ficheiro de entrada*/
	
	while((ret = fscanf(fpal, "%s %s %d", p1, p2, &mut)) == 3) /*le os varios testes do ficheiro*/
	{
		t = (strlen(p1)-1);
		c = 0;
		for(i = 0; i < t+1; i+=1) /*percorre todo os caracteres da string*/
			if(p1[i] != p2[i])
				c += 1; /*quando encontra um caracter diferente na mesma posicao*/
		
		if(c < mut) mut = c; /*se as mutacoes permitidas forem mais do que as necessarias para mudar as palavras num passo*/
		
		if( mut > dicio->testes[t].maxmut )
			dicio->testes[t].maxmut = mut; /*guarda a maior mutacao para cada tamanho de palavra*/
     
		dicio->testes[t].quantidade += 1;/*incrementa para saber qtos testes ha para cada palavra*/
	}
	fclose ( fpal ); /*fecha o ficheiro de entrada */
	return;
}

/******************************************************************************
 * ProcuraBinaria()
 *
 * Argumentos: 	dicio - tabela de dicionario organizado alfabeticamte
 * 				palavra - palavra a descobrir a posicao
 * Retorna: indice da palavra
 * Encontra o indice da palavra na tabela dicionario
 *
 ******************************************************************************/
int ProcuraBinaria(st_dicionario *dicio, char palavra [MAX_STR])
{
	int r, n, ret = 1, l = 0;
	int tam = strlen(palavra)-1;
	r = (dicio->ocorrencias[tam])-1;
	n = (r)/2;

	while((ret = (strcmp(palavra, dicio->palavra[tam][n]))) != 0){
		if(ret < 0) {
			r = n;	n = (l + ((n-l)/2)) - 0.5;
		}
		if(ret > 0)	{
			l = n;	n = r - ((r-n)/2);
		}
	}
	return n;
}

/******************************************************************************
 * FreeDicionario()
 *
 * Arguments:	dicio - dicionario
 * 				total - numero total de palavras do dicionario
 * Returns: (none)
 *
 * Faz free da memoria alocada para os ponteiros para as palavras
 *
 *****************************************************************************/
void FreeDicionario(st_dicionario *dicio)
{
	int i, j;

	for(i=0; i < MAX_STR; i++)
	{
		for(j = 0; j < dicio->ocorrencias[i]; j++)
			free(dicio->palavra[i][j]);

		free(dicio->palavra[i]);
	}

	free(dicio->palavra);
	return;
}
