#ifndef _TABELAS_H
#define _TABELAS_H
#include "btree.h"
#define MAX_KEY 102400

typedef struct{
	char nome[50];
	char tipo;
	int tamInfo;
	char notNull;
	char autoIncrement;
}Info;

void arquivoLivro();
void arquivoLeitor();
void arquivoAutor();
void arquivoAutorDoLivro();
void arquivoEmprestimo();
void insercao(char *nomeArquivo, BTree *btree);
void read(char*nomeArquivo, BTree *btree,int id);
void delete(char *nomeArquivo, BTree *btree,int id);
void update(char *nomeArquivo, BTree *btree,int id);
void insereInfoNoArquivo(char*nomeArquivo, Info informacao, BTree *btree);
int verificaHex(FILE *arquivo);
void menuTabelas(BTree *BTree_Livro, BTree *BTree_Leitor, BTree *BTree_Autor, BTree *BTree_AutorDoLivro, BTree *BTree_Emprestimo);
void menuCRUD(char *nomeArquivo, BTree *btree);
#endif