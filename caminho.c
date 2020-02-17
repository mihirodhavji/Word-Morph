#include "caminho.h"

/***********************************************************************
 * CriaAcervo()
 * 
 * Argumentos:	v - numero do vertice que se quer atribuir ao no do 
 * 					acervo
 * 				cost - custo do no que se cria
 * 
 * Retorna: ponteiro para acervo criado
 * 
 * Cria o acervo 
 * 
 **********************************************************************/ 
Acervo* CriaAcervo(int V)
{
    Acervo* A = (Acervo*) malloc(sizeof( Acervo));
    if(A == NULL) exit (0);
    
    A->n_nos = V;
    A->tamanho = V;
    A->posicao_em_acervo = (int *)malloc(V * sizeof(int));
    if(A->posicao_em_acervo == NULL) exit (0);
    
    A->custos = (int *)malloc(V*sizeof(int));
	if (A->custos == NULL) exit(0);
	
	A->father = (int *)malloc(V*sizeof(int));
	if(A->father == NULL) exit(0);
    
    A->fila = (int*) malloc(V*sizeof(int));
    if(A->fila == NULL) exit (0);
    
    return A;
}

/***********************************************************************
 * initAcervo()
 * 
 * Argumentos:	A - ponteiro para acervo
 * 				V - numero de vertices do grafo do qual se vai achar o 
 * 					caminho
 * 				orig - vertice de origem
 * 
 * Inicia o acervo
 * 
 **********************************************************************/ 
void initAcervo(Acervo *A, int V, int orig)
{
	int i = 0;
    for (i = 0; i < V; i += 1)/*para todos os vertices excepto o de origem*/
    {
		A->posicao_em_acervo[i] = i;
		A->custos[i] = INF;
        A->father[i] = -1;
        A->fila[i] = i;  
    }
    /*para o vertice de origem*/
    A->custos[orig] = 0;    
    A->father[orig] = orig; /*e o seu proprio pai*/  
}

/***********************************************************************
 * FixUp()
 * 
 * Argumentos:	A - ponteiro para acervo
 * 				vertice - vertice do grafo
 * 				cost - custo do caminho do vertice de origem ate ao 
 * 						vertice
 * 
 * Faz FixUp ao acervo para repor a condicao de acervo qd se poe um no
 **********************************************************************/ 
void FixUp(Acervo* A, int vertice)
{
    int Child = A->posicao_em_acervo[vertice]; 
     
    while (Child > 0 && ((A->custos[A->fila[Child]]) < (A->custos[A->fila[(Child-1)/2]]))) /*compara a prioridade do filho com o pai*/
    {
        A->posicao_em_acervo[A->fila[Child]] = (Child-1)/2;
        A->posicao_em_acervo[A->fila[(Child-1)/2]] = Child;
		/*troca o no filho com o no pai*/
        exch(A->fila[Child], A->fila[(Child-1)/2]);
        Child = (Child - 1) / 2; /*nao para enquanto nao chegar a raiz do acervo*/
    }
	return;
}
/***********************************************************************
 * FixDown()
 * 
 * Argumentos:	A - ponteiro para acervo
 * 				idx - indice de um no do acervo
 * 
 *Faz FixDown ao acervo para repor a condicao de acervo qd se tira um no
 **********************************************************************/ 
void FixDown ( Acervo* A, int idx)
{
	int Child = 0;
	
	while(2*idx < (A->n_nos -1))
	{
		Child = 2*idx+1;
		/*Descobre qual o filho com maior prioridade*/
		if(Child < (A->n_nos -1) && (( A->custos[A->fila[Child]] > A->custos[A->fila[Child+1]])))
			Child += 1;					 
		/*Caso a condiçao de acervo esteja satisfeita*/
		if((A->custos[A->fila[idx]] < A->custos[A->fila[Child]])) break;
			
        /*Troca as posiçoes*/
        A->posicao_em_acervo[(A->fila[Child])] = idx;
        A->posicao_em_acervo[(A->fila[idx])] = Child;
 
        /* Troca os nos do acervo */
        exch(A->fila[Child], A->fila[idx]);
		
		idx = Child;
	}
} 

/******************************************************************************
 * AcervoMin()
 * 
 * Argumentos:	A - ponteiro para acervo 
 * 
 * Devolve o vertice mais prioritario
 ******************************************************************************/ 
int AcervoMin( Acervo *A)
{
	int no_prio = 0;
 
    no_prio = A->fila[0];
	exch(A->fila[0], A->fila[A->n_nos-1]);
    A->posicao_em_acervo[A->fila[0]] = A->n_nos-1; /*Alterar as posicoes da raiz e do ultimo no*/
    A->posicao_em_acervo[A->fila[A->n_nos-1]] = 0;
 
    A->n_nos -= 1; /*Tiramos 1 nos por isso decrementa o tamanho do acervo e faz se fix down */
    FixDown(A, 0);
 
    return no_prio;
}

/******************************************************************************
 * PrintCaminhoLinha()
 * 
 * Imprime a ultima linha com a palavra de destino
 * 
 ******************************************************************************/ 
void printCaminhoLinha(FILE *fout, int u, st_dicionario *dicio, int tam)
{
	fprintf(fout, "%s\n\n", dicio->palavra[tam][u]);
}

/******************************************************************************
 * PrintCaminho()
 * 
 * Imprime o caminho da palavra de origem ate à anterior à de destino
 * Imprime o custo do caminho
 * 
 ******************************************************************************/
void printCaminho(FILE *fout, Acervo *A, int n, st_dicionario *dicio, int tam, int custo_total)
{
	n = A->father[n];
	if (n != A->father[n])
		printCaminho(fout, A, n, dicio, tam, custo_total);
	fprintf(fout, "%s", dicio->palavra[tam][n]);
	if(n == A->father[n]) fprintf(fout, " %d\n", custo_total);
	else fprintf(fout, "\n");
}

/******************************************************************************
 * PrintNenhumLinha()
 * 
 * Imprime para o ficheiro de saida a informaçao de que nao ha caminho
 * 
 ******************************************************************************/
void printNenhumCaminho(FILE *fout, int orig, int dest, st_dicionario *dicio, int tam)
{
	fprintf(fout, "%s -1\n%s\n\n", dicio->palavra[tam][orig], dicio->palavra[tam][dest]);	
}

/******************************************************************************
 * Dijkstra()
 * 
 * Implementacao do algoritmo de Dijkstra
 * Encontra o caminho de menor custo entre as palavras nos vertices orig e 
 * destino do grafo
 * 
 ******************************************************************************/
void Dijkstra( FILE *fout, Graph* g, int orig, int destino, int maxmut, st_dicionario *dicio, int tam)
{
    int flag = 0, no = 0;
	link *aux = NULL;
	Acervo *A = NULL;

	A = CriaAcervo(g->V);	
    initAcervo(A, g->V, orig);
    FixUp(A, orig);

    while (A->n_nos != 0) /*enquanto houver vertices na fila, ie, o acervo na estiver vazio*/
    {					/*se nao houver caminho, vai fazer a SPT completa*/
        no = AcervoMin(A);
		/**Break se encontrar a palavra de destino e estiver a uma distancia que nao infinito**/
		if (no == destino && A->custos[no]!=INF){ flag = 1; break;}
        for(aux = g->adj[no]; aux != NULL; aux = aux->next) /*vai percorrer todos os vertices adjacentes a aux - comeca na palavra de origem pq e a raiz de A*/
        {
            if ((A->posicao_em_acervo[aux->index] < A->n_nos) && aux->custo <= maxmut && A->custos[no] != INF && (((A->custos[no])+(aux->custo)) < (A->custos[aux->index])))
            { /*se ainda nao estiver inserida no caminho e satisfizer as condicoes dos custos*/
			    A->father[aux->index] = no;
                A->custos[aux->index] = aux->custo + A->custos[no];
                FixUp(A, aux->index); /*o custo/prioridade mudou tem que se fazer fix*/
            }
        }
    }
    /*Imprimir o caminho mais curto encontrado*/
    if(flag == 1){
		printCaminho(fout, A, no, dicio, tam, A->custos[no]);
		printCaminhoLinha(fout, no, dicio, tam);
	}
	else { /*se nao for encontrado caminho entre as palavras*/
		printNenhumCaminho(fout, orig, destino, dicio, tam);
	}
    /*free allocated memory*/
    FreeAcervo(A);
}

/******************************************************************************
 * FreeAcervo()
 * 
 * Argumentos:	A - ponteiro para acervo
 * 
 * Desaloca a memoria alocada para o acervo
 * 
 ******************************************************************************/
void FreeAcervo(Acervo *A)
{	
	free(A->custos); /*free do vetor dos custos*/
	free(A->father); /*free do vetor dos vertices pai*/
	free(A->posicao_em_acervo); /*free do vetor de posicoes dos vertices no acervo*/
	free(A->fila); /*free do vetor para a fila*/
	free(A); /*free do ponteiro para acervo*/
	return;
}
