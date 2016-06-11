#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelas.h"
#include "btree.h"

/***********************************O QUE ARRUMAR?***********************************
*																					*
*	Oi! Saca só. Agora toda BTree guarda também o nome de seu arquivo de índices.	*
*	(Como é possível observar logo abaixo quando inicializo as BTrees).				*
*																					*
*	A função insereChavesIniciais tá bugando. É só comentar ela pra funcionar o res-*
*   to. O objetivo dela é ler os IDs existentes dos arquivos de índice e inserir na *
*	BTree, com o objetivo de restaurar ela depois que o programa parou.				*
*																					*
*	Como ela não está funcionando, os IDs resetam quando paramos o programa.		*
*	Sim. Isso ainda é um problema na ~inserção~. Então, tá foda. O interessante é 	*
*	que a BTree está (aparentemente) funcionando (valeu Willian! :).				*
*																					*
*	Enfim, quase 05:00 aqui. Acho que vou dormir e tals. :/ Se não amanhã fode né.	*
*	Vou nessa.																		*
*																		- Marcos	*
*************************************************************************************/





int main(){
	char op;

	/* Inicializa BTrees */
	BTree BTree_Livro = inicializaBTree(5, "arquivoLivroB.txt");
	BTree BTree_Leitor = inicializaBTree(5, "arquivoLeitorB.txt");
	BTree BTree_Autor = inicializaBTree(5, "arquivoAutorB.txt");
	BTree BTree_AutorDoLivro = inicializaBTree(5, "arquivoAutorDoLivroB.txt");
	BTree BTree_Emprestimo = inicializaBTree(5, "arquivoEmprestimoB.txt");

	//insereChavesIniciais(&BTree_Livro, &BTree_Leitor, &BTree_Autor, &BTree_AutorDoLivro, &BTree_Emprestimo);

	/* Temporário: se a BTree começa sem chaves, dá bug na hora de buscar
	 * O que queremos: ler o arquivo de indice da btree e adicionar todos
	 * os ids iniciais, pra evitar isso. 
	 * 												Mas assim funciona <3
	*/
/*
	insereChave(&BTree_Livro, 0);
	insereChave(&BTree_Leitor, 0);
	insereChave(&BTree_Autor, 0);
	insereChave(&BTree_AutorDoLivro, 0);
	insereChave(&BTree_Emprestimo, 0);
*/	
	/* Insere chaves existentes nos arquivos nas BTrees */
	/*insercaoInicialBTree(BTree_Livro);
	insercaoInicialBTree(BTree_Leitor);
	insercaoInicialBTree(BTree_Autor);
	insercaoInicialBTree(BTree_AutorDoLivro);
	insercaoInicialBTree(BTree_Emprestimo);*/

	/* Loop do BD */
	while(op != 's'){	
		menuTabelas(&BTree_Livro, &BTree_Leitor, &BTree_Autor, &BTree_AutorDoLivro, &BTree_Emprestimo);
		printf("Deseja fazer outro acesso?\n");
		scanf("%c",&op);
	}

	return 0;
}