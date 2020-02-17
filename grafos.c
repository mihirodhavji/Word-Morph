#include "grafos.h"

/***********************************************************************
* GRAPHinit()
*
* Argumentos: 	V - numero de vertices do grafo
* 			   	
* Retorna: grafo
*
* Inicia um grafo
*
***********************************************************************/
Graph* GRAPHinit(int V) 
{ 
	int i = 0; 
	Graph *G = (Graph*) malloc(sizeof(Graph)); 
	if( G == NULL) exit(0);
	G->V = V; 
	G->E = 0; 
	G->adj = (link **) malloc(V * sizeof(link*)); 
	if( G->adj == NULL)exit(0);
	for (i = 0; i < V; i+=1) G->adj[i] = NULL; 
	return G; 
}

/***********************************************************************
 * NEW()
 *
 * Argumentos: 	v - 
 * 			   	p - 
 * Retorna: aresta
 *
 * Cria uma nova aresta
 *
 **********************************************************************/
link* NEW(int pos, link *next, int c)
{
	link *novo = (link *) malloc(sizeof(struct node));
	novo->index = pos;
	novo->custo = c;
	novo->next = next;
	return novo;
}

/***********************************************************************
* GRAPHinsertE()
*
* Argumentos: 	G - ponteiro para o grafo 
* 			   	e - ponteiro para a aresta
* 				c - custo da aresta
*
* Insere uma nova aresta no grafo
*
***********************************************************************/
void GRAPHinsertE(Graph *G, int v, int w, int cost) 
{ 
	G->adj[v] = NEW(w, G->adj[v], cost); 
	G->adj[w] = NEW(v, G->adj[w], cost); 
	G->E += 1;
}

/***********************************************************************
* FreeGraph()
*
* Argumentos: 	G - ponteiro para o grafo
*
* Desaloca a memoria alocada para o grafo
*
***********************************************************************/
void FreeGraph (Graph *G)
{
	int i = 0;
	link *t = NULL, *aux = NULL;
	if(G == NULL) return;
	for(i = 0; i < G->V; i++)
	{
		t = G->adj[i];
		aux = G->adj[i];
		while(t != NULL)
		{
			t = t->next;
			free(aux);
			aux = t;
		}
	}
	free(G->adj);
	free(G);
	return;
}

/***********************************************************************
* ProcessaTestes()
*
* Argumentos: 	dicio - ponteiro para o dicionario
* 				fichpal - nome do ficheiro de teste
* 
* Funcao que processa o ficheiro de teste
* Analisar as palavras de entrada e as mutacoes primeiro para garantir 
* que nao ha incoerencias com as mutacoes maximas
* Constroi os grafos 1 a 1 a medida que sao necessarios e quando nao 
* precisa mais de um grafo, a memoria e desalocada caso seja precisa 
* alocar mais memoria para outro grafo de outro tamanho.
* Procura o caminho mais curto entre as palavras de origem e destino.
* 
***********************************************************************/
void ProcessaTestes(char *fichpal, st_dicionario *dicio)
{
	FILE *fpal = NULL, *fout = NULL;
	Graph **g = NULL;
	int mut = 0, tam = 0, index_orig = 0, index_destino = 0, c = 0;
	char p_orig[MAX_STR] = "\0", p_dest[MAX_STR] = "\0";
	char *nome_saida = NULL;
	
	g = AlocaVetorGrafo();

	fpal = AbreFicheiro(fichpal, "r");

	nome_saida =  NomeFichSaida (fichpal);
	fout = AbreFicheiro(nome_saida, "w");
	while( (fscanf(fpal, "%s %s %d", p_orig, p_dest, &mut)) == 3)
	{
		
		c = 0; tam = strlen(p_orig)-1;
		
		if(!strcmp(p_orig, p_dest)) { /*se as palavras forem iguais*/
			fprintf(fout, "%s 0\n%s\n\n", p_orig, p_dest);
			dicio->testes[tam].quantidade -= 1;
			if(dicio->testes[tam].quantidade == 0)
				FreeGraph(g[tam]);
			continue;
		}
		/*calcula o custo entre as duas palavras para garantir que as mutacoes nao sao desnecessarias*/
		index_orig = ProcuraBinaria(dicio, p_orig);
		index_destino = ProcuraBinaria(dicio, p_dest);
		CalculaCusto(dicio, tam, index_orig, index_destino, &c);
		if(c < mut) mut = c;
		
		if(c ==1){
			fprintf(fout, "%s 1\n%s\n\n", p_orig, p_dest);/*se as palavras diferirem de 1 caracter*/
			dicio->testes[tam].quantidade -= 1;
			if(dicio->testes[tam].quantidade == 0)
				FreeGraph(g[tam]);
			continue;
		}
		if(g[tam] == NULL)
		{
			/*Criar o grafo se nao existir ja do mesmo tamanho*/
			g[tam] = GRAPHinit(dicio->ocorrencias[tam]);
			BuildGrafo(g[tam], dicio, tam);		
		}
	
		/*fazer a busca do caminho mais curto*/
		Dijkstra(fout ,g[tam], index_orig, index_destino, (mut*mut), dicio, tam);
		dicio->testes[tam].quantidade -= 1;
		if(dicio->testes[tam].quantidade == 0)
			FreeGraph(g[tam]);
	}
	
	
	fclose(fpal);
	fclose(fout);
	free(g);
	free(nome_saida);
	return;
}

/***********************************************************************
* AlocaVetorGrafo()
*
* Argumentos: 	dicio - ponteiro para o dicionario
* 				
* Aloca memoria para o vetor de grafos 
* 
***********************************************************************/
Graph** AlocaVetorGrafo(void)
{
	Graph **g = NULL;
	int i = 0;
	
	g = (Graph **) malloc(MAX_STR*sizeof(Graph *));
	if(g == NULL) exit(0);
	
	for(i = 0; i < MAX_STR; i += 1)
		g[i] = NULL;
	
	return g;
	
}

/***********************************************************************
* CalculaCusto()
*
* Argumentos: 	dicio - ponteiro para o dicionario
* 				tam - tamanho das palavras, para saber que vetor do 
* 					  dicionario usar
* 				v - posicao no dicionario da palavra do vertice v
* 				w - posicao no dicionario da palavra do vertice w
* 
* Retorna: o custo do caminho entre as duas palavras
* 
* Calcula o custo entre as duas palavras
* Se o custo for superior ao numero de mutacoes autorizadas, o custo e 
* infito.
*
***********************************************************************/
void CalculaCusto(st_dicionario *dicio, int tam, int v, int w, int *cost )
{
	int i = 0, mxmt = dicio->testes[tam].maxmut;
	*cost = 0;
	for(i = 0; i < tam+1; i+=1) /*percorre todo os caracteres da string*/
	{
		if(dicio->palavra[tam][v][i] != dicio->palavra[tam][w][i])
		{	
			*cost += 1; /*quando encontra um caracter diferente na mesma posicao*/
			if(*cost > mxmt){ *cost = INF; break;}
		}
	}
	return;

}
/***********************************************************************
* BuildGrafo()
*
* Argumentos: 	g - ponteiro para o grafo a construir
* 				dicio - ponteiro para o dicionario
* 				tam - tamanho das palavras no grafo
* 
* Constroi o grafo para um determinado tamanho tam de palavras
* 
***********************************************************************/
void BuildGrafo(Graph *g ,st_dicionario *dicio, int tam)
{
	int i = 0, j = 0, cost = 0;
	
	for(i = 0; i < dicio->ocorrencias[tam]; i+=1)
	{
		for(j = i+1; j < dicio->ocorrencias[tam]; j+=1)
		{
			CalculaCusto(dicio, tam, i, j, &cost);
			if(cost < INF)
				GRAPHinsertE(g, i, j, (cost*cost));
		}
	}
}
