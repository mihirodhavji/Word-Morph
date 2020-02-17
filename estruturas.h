/**Ficheiro estruturas.h para definir estruturas, constantes e macros*/

#define MAX_STR 50 /*no maximo uma palavra tem 27 caracteres*/
#define INF 2501 /*infinito - admitimos max de 50 letras numa palavra*/

#define key(A) (A)
#define exch(A, B) {int t = A; A = B; B = t; }
#define exchpal(A, B) {char *t = A; A = B; B = t; }

/*Definicao de novo tipo Test para guardar a quatidade de testes e as mutacoes maximas*/
typedef struct { int quantidade; int maxmut; } Test;

/*Definicao de novo tipo st_dicionario para guardar o dicionario lido do ficheiro*/
typedef struct _st_dicionario st_dicionario;
struct _st_dicionario {
	char ***palavra;
	int ocorrencias[MAX_STR];
	int ocupado[MAX_STR];
	int ordenado[MAX_STR];
	Test testes[MAX_STR];
};

/*Definicao de novo tipo link para ligacoes entre vertices de um grafo*/
typedef struct node link;
struct node { 
	int index; 
	int custo; 
	link *next; 
};

/*Definicao de novo tipo Graph para definir um grafo*/
typedef struct { 
	int V; 
	int E; 
	link **adj; 
} Graph;

/* Definicao de novo tipo Acervo que representa um acervo*/
typedef struct _Acervo
{
    int n_nos;      /* Numero de nos presentes no acervo*/
    int tamanho;  /* tamanho maximo do acervo*/
    int *posicao_em_acervo; /*importante para saber se um vertice ainda esta no acervo*/  
    int *custos;
    int *father;
    int *fila;
} Acervo;

