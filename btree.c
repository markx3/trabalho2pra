#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "btree.h"
#include "tabelas.h"

BTree inicializaBTree(int grau, char *nomeB) {
	BTree *btree = NULL;
	btree = malloc(sizeof(BTree));				// Isto estava causando SegFault! (No caso, isto não existia)
	assert(btree);
	btree->raiz = inicializaBTreeNo(1, grau);
	btree->grau = grau;
	btree->nomeB = malloc(sizeof(nomeB));
	btree->nomeB = nomeB;
	return *btree;
}

BTreeNo *inicializaBTreeNo(int folha, int grau) {
	int i = 0;
	BTreeNo *node = NULL;
	node = malloc(sizeof(BTreeNo)); 			// Isto estava causando SegFault! (No caso, isto não existia)
	assert(node);
	node->folha = folha;
	node->chaves = malloc(sizeof(int)*(2*grau-1));
	while (i <= 2*grau-1) {
		node->chaves[i] = 0;
		i++;
	}
	node->grau = grau;
	node->filhos = malloc(sizeof(BTreeNo*)*(2*grau));
	node->numChaves = 0;
	node->del=malloc(sizeof(char)*(2*grau-1));
	i=0;
	while(i<= 2*grau-1){
		node->del[i] = 'n';
		i++;
	}
	return node;
}

BTreeNo *busca(BTreeNo *node, int k) {					// ATENCAUM
	// Encontrar a primeira chave maior ou igual a k
	int i = 0;
	//encontra a primeira chave maior ou igual a k;
	//printf("%d\n",node->numChaves);
	while ((i < node->numChaves) || (k < node->chaves[i])) {
		if (node->chaves[i] == k) return node;
		//printf("%d\n",node->chaves[i]);
		i++;
	}
    // se encontrar a chave

    // chave nao encontrada nem na folha
    if (node->folha == 1) return NULL;

    // não é folha e não encontramos k!!!
    return busca(node->filhos[i+1], k);
}

int buscaMaiorChave(BTreeNo *node){					// ATENCAUM
	if (node->folha == 1) {
        return node->chaves[node->numChaves-1];
	}
    else {
        return buscaMaiorChave(node->filhos[node->numChaves]);
    }
    
}

void insereChave(BTree *arvore, int k) {
	int i = 0;
	if (arvore->raiz == NULL) {
		arvore->raiz = inicializaBTreeNo(1, arvore->grau);
		arvore->raiz->chaves[arvore->raiz->numChaves] = k;
		arvore->raiz->numChaves++;
	} else {
		if (arvore->raiz->numChaves == arvore->raiz->grau*2-1) { // Está cheia! :-(
			BTreeNo *newNode = inicializaBTreeNo(0, arvore->grau);
			newNode->filhos[0] = arvore->raiz;
			divideNoFilho(0, newNode);
			if (newNode->chaves[0] < k) i++;
			insereNaoCheio(k, newNode->filhos[i]);

			arvore->raiz = newNode;
		}
		else 
            insereNaoCheio(k, arvore->raiz);
	}
}

void insereNaoCheio(int k, BTreeNo *node){
    //i como index da ultima chave
    int i = node->numChaves-1;
    if (node->folha == 1)
    {
        // while:
        // acha onde deve ser inserida a chave
        // move os maiores que ele um espaço pra frente
        while (i >= 0 && node->chaves[i] > k)
        {
           node->chaves[i+1] = node->chaves[i];
            i--;
        }
        // insere chave no lugar encontrado
        node->chaves[i+1] = k;
        node->numChaves++;
    }
    else
    {
        // encontrar no que vai receber a chave
        while (i >= 0 && node->chaves[i] > k){
            i--;
        }
        // verifica se está cheio
        if (node->filhos[i+1]->numChaves == 2*node->filhos[i+1]->grau - 1)
        {
            // divide o filho se estiver cheio
            divideNoFilho(i+1, node);
            // termo médio do filho dividido agora está no pai, verifica se essa chave é
            //menor que a nova chave
            if (node->chaves[i+1] < k)
                i++;
        }
        insereNaoCheio(k, node->filhos[i+1]);
	}
}

//int i representa a posição do nó filho a ser dividido e nó é o nó pai que irá receber o novo nó
void divideNoFilho(int i, BTreeNo *node) {
	int j;
    if(node->filhos[i]->folha == 1) node->filhos[i]->folha = 0;
	//cria novo no' para trocar as chaves
	BTreeNo *newNode = inicializaBTreeNo(1, node->grau);
	//novo no' vai receber grau-1 chaves, metade menos o do meio
	newNode->numChaves = node->grau-1;
	//coloca as ultimas chaves depois da central no novo no'
	for(j = 0; j < node->grau-1; j++){
		newNode->chaves[j] = node->filhos[i]->chaves[j+node->filhos[i]->grau];
	}
	//se o no' passado nao for folha, passar os nós filhos maiores para o novo nó
	if(node->filhos[i]->folha == 0){
		for(j = 0; j < node->filhos[i]->grau; j++){
			newNode->filhos[j] = node->filhos[i]->filhos[j+node->filhos[i]->grau];
		}
	}
	//diminui do no' original os filhos tirados
	node->numChaves = node->grau-1;
    //abrir espaço para inserir o novo nó
    for (j = node->numChaves; j >= i+1; j--)
        node->filhos[j+1] = node->filhos[j];
    //colocar o novo nó na posição apropriada
    node->filhos[i+1] = newNode;
    //abrir espaço para inserir nova chave
    for (j = node->numChaves-1; j >= i; j--) {
        node->chaves[j+1] = node->chaves[j];
    //colocar a nova chave na posição apropriada
    node->chaves[i] = node->filhos[i]->chaves[node->filhos[i]->grau-1];
    // ajustar o numero de chaves no nó
    node->numChaves++;
	}
 }

void insereChavesIniciais(BTree *BTree_Livro, BTree *BTree_Leitor, BTree* BTree_Autor, BTree* BTree_AutorDoLivro, BTree* BTree_Emprestimo) {

	insereChavesIniciaisGenerica(BTree_Livro, BTree_Livro->nomeB);
	insereChavesIniciaisGenerica(BTree_Leitor, BTree_Leitor->nomeB);
	insereChavesIniciaisGenerica(BTree_Autor, BTree_Autor->nomeB);
	insereChavesIniciaisGenerica(BTree_AutorDoLivro, BTree_AutorDoLivro->nomeB);
	insereChavesIniciaisGenerica(BTree_Emprestimo, BTree_Emprestimo->nomeB);

}

void insereChavesIniciaisGenerica(BTree *bt, char *nome) {
	FILE *fp = NULL,*fp1;
	int chave;
	char c;
	char d;
	char stream[10];
	printf("%s\n", nome);
	printf("oi?\n");
	if ((fp = fopen(nome, "r")) == NULL) {
		fp1 = fopen(nome, "w");
		insereChave(bt, 0);
		fprintf(fp1, 0);
		fclose(fp1);
	} else {
		printf("oi2312\n");
		//while(!(feof(fp))) {
			printf("feof?\n");
			while((c = fgetc(fp)) != 'n') {
				printf("while c\n");
				strcat(stream, &c);
				//printf("strcat %s\n",stream);
				c = fgetc(fp);
				//printf("%c\n", c);
			}
			chave = atoi(stream);
			printf("chave = %d stream = %s\n",chave,stream);
			insereChave(bt, chave);
			strcpy(stream, "");
		
	}
	fclose(fp);
}

FILE* abreArquivoB(char *nome) {
	FILE *fp = NULL;
	return fp = fopen(nome, "r");
}

void insereIndiceNoArquivoB(FILE *fp, int indice) {
	char *stream;
	sprintf(stream, "%d", indice);
	fprintf(fp, "%s\n", stream);
}

