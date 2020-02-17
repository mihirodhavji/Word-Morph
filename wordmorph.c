/********************************************************************
 * WORDMORPH - Projeto de AED - Entrega Final						*
 * Prof. Carlos Bispo												*
 * Alunos:	Gil Serrano		No. 84060								*
 *			Mihir Odahvji	No. 84151								*
 * Data de ultima modificacao: 08/12/2016							*
 *																	*
 * Descricao do programa:											*
 * -> Ler um dicionario de palavras com diferentes tamanhos e um 	*
 * ficheiro com palavras a testar. 									*
 * -> Le e organiza alfabeticamente as palavras do dicionario.		*
 * -> Faz os grafos que tem as palavras como vertices e arestas com *
 * custo igual ao quadrado da diferenca de letras entra as palavras.*
 * -> Encontra o caminho mais "barato" entre duas palavras lidas do	*
 * ficheiro de teste, consoante o numero maximo de mutacoes 		*
 * permitidas para cada teste.										*
 * -> Escreve para um ficheiro .path o caminho mais barato entre as *
 * duas palavras e indica qual o custo desse caminho.				*
 * 																	*
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafos.h"


/** MAIN **/
int main (int argc, char* argv[])
{
	st_dicionario d;
	Verificacao(argv[1], argv[2]);	/*Verificar se os argumentos estao bem*/
	ProcessaFicheiros(argv[1], argv[2], &d); /*Processa o ficheiro de dicionario e minimamente o de teste*/
	ProcessaTestes(argv[2], &d); /*Processa os varios testes do ficheiro pal*/
	FreeDicionario(&d);	/*Desalocar memoria do dicionario*/
	return 0;
}
