#ifndef _BTREE_H
#define _BTREE_H

typedef struct no {
	int *chaves;
	struct no **filhos;
	int grau;
	int numChaves; // numero de chaves
	int folha;
	char *del;
} BTreeNo;

typedef struct {
	BTreeNo *raiz;
	int grau; // grau
	char *nomeB;
}BTree;

BTree inicializaBTree(int grau, char *nomeB);
BTreeNo *inicializaBTreeNo(int folha, int grau);
void divideNoFilho(int i, BTreeNo *node);
void insereNaoCheio(int k, BTreeNo *node);
void insereChave(BTree *arvore, int k);
void insercaoInicialBTree(BTree *BTree);
BTreeNo *busca(BTreeNo *node, int k);
int buscaMaiorChave(BTreeNo *node);
void insereChavesIniciais(BTree *BTree_Livro, BTree *BTree_Leitor, BTree* BTree_Autor, BTree* BTree_AutorDoLivro, BTree* BTree_Emprestimo);
void insereChavesIniciaisGenerica(BTree *bt, char *nome);
FILE* abreArquivoB(char *nome);
void insereIndiceNoArquivoB(FILE *fp, int indice);


#endif
