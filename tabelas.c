#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tabelas.h"
#include "btree.h"

void menuTabelas(BTree *BTree_Livro, BTree *BTree_Leitor, BTree *BTree_Autor, BTree *BTree_AutorDoLivro, BTree *BTree_Emprestimo) {
	int num;
	printf("Qual tabela você deseja acessar?\n1-Livro\n2-Leitor\n3-Autor\n4-Autor do Livro\n5-Emprestimo\n");
	scanf("%d",&num);
	switch(num){
		case 1:
			arquivoLivro();
			menuCRUD("arquivoLivro.txt", BTree_Livro);
			break;
		case 2:
			arquivoLeitor();
			menuCRUD("arquivoLeitor.txt", BTree_Leitor);
			break;
		case 3:
			arquivoAutor();
			menuCRUD("arquivoAutor.txt", BTree_Autor);
			break;
		case 4:
			arquivoAutorDoLivro();
			menuCRUD("arquivoAutorDoLivro.txt", BTree_AutorDoLivro);
			break;
		case 5:
			arquivoEmprestimo();
			menuCRUD("arquivoEmprestimo.txt", BTree_Emprestimo);
			break;
		default:
			printf("Tabela invalida\n");
			return;
	}
}
void menuCRUD(char *nomeArquivo, BTree *btree){
	int num=0;
	int id;
	while(num != 5){
		printf("Qual operação deseja fazer na tabela?\n1-Criar\n2-Ler\n3-Atualizar\n4-Deletar\n5-Sair\n");
		scanf("%d", &num);
		switch(num){
			case 1:
				insercao(nomeArquivo, btree);
				break;
			case 2:
				printf("Qual id deseja procurar?\n");
				scanf("%d",&id);
				read(nomeArquivo, btree, id);
				break;
			case 3:
				printf("Qual id deseja atualizar?\n");
				scanf("%d",&id);
				update(nomeArquivo,btree,id);
				break;
			case 4:
				printf("Qual id deseja deletar?\n");
				scanf("%d",&id);
				delete(nomeArquivo,btree,id);
				break;
			default:
				printf("Operação invalida\n");
				break;
		}
	}
}
void arquivoLivro(){
	FILE * arquivo;
	if((arquivo = fopen("arquivoLivro.txt", "r")) == NULL) {
		arquivo = fopen("arquivoLivro.txt","w");
		fprintf(arquivo, "0xBADA55\nid i 11 y y\ntitulo c 30 y n\neditora c 30 n n\nisbn c 20 n n\nanoPublicacao i 11 y n\n$\n");
		fclose(arquivo);
	} else { 		// VERIFICA HEX RETORNA 0 SE FALHA
		if(!(verificaHex(arquivo))) {
		arquivo = fopen("arquivoLivro.txt","w");
		fprintf(arquivo, "0xBADA55\nid i 11 y y\ntitulo c 30 y n\neditora c 30 n n\nisbn c 20 n n\nanoPublicacao i 11 y n\n$\n");
		fclose(arquivo);
		}
	}
	
}

void arquivoLeitor() {
	FILE *arquivo;
	if((arquivo = fopen("arquivoLeitor.txt", "r")) == NULL) {
		arquivo = fopen("arquivoLeitor.txt", "w");
		fprintf(arquivo, "0xBADA55\nid i 6 y y\nnome c 30 y n\nfone c 20 y n\nendereco c 40 n n\ncidade c 40 n n\nestado c 2 n n\n$\n");
		fclose(arquivo);
	}else{
		if(!(verificaHex(arquivo))) {
			arquivo = fopen("arquivoLeitor.txt","w");
			fprintf(arquivo, "0xBADA55\nid i 6 y y\nnome c 30 y n\nfone c 20 y n\nendereco c 40 n n\ncidade c 40 n n\nestado c 2 n n\n$\n");
			fclose(arquivo);
		}
	}
}

void arquivoAutor() {
	FILE *arquivo;
	if((arquivo = fopen("arquivoAutor.txt", "r")) == NULL) {
		arquivo = fopen("arquivoAutor.txt", "w");
		fprintf(arquivo, "0xBADA55\nid i 4 y y\nnome c 20 n n\nsobrenome c 20 n n\n$\n");
		fclose(arquivo);
	}else{
		if(!(verificaHex(arquivo))) {
			arquivo = fopen("arquivoAutor.txt", "w");
			fprintf(arquivo, "0xBADA55\nid i 4 y y\nnome c 20 n n\nsobrenome c 20 n n\n$\n");
			fclose(arquivo);
		}
	}
}

void arquivoAutorDoLivro() {
	FILE *arquivo;
	if((arquivo = fopen("arquivoAutorDoLivro.txt", "r")) == NULL) {
		arquivo = fopen("arquivoAutorDoLivro.txt", "w");
		fprintf(arquivo, "0xBADA55\nautorId i 4 y n\nlivroId i 6 y n\nsequencia i 2 y n\n$\n");
		fclose(arquivo);
	}else{
		if(!(verificaHex(arquivo))) {
			arquivo = fopen("arquivoAutorDoLivro.txt", "w");
			fprintf(arquivo, "0xBADA55\nautorId i 4 y n\nlivroId i 6 y n\nsequencia i 2 y n\n$\n");
			fclose(arquivo);
		}
	}
}

void arquivoEmprestimo() {
	FILE *arquivo;
	if((arquivo = fopen("arquivoEmprestimo.txt", "r")) == NULL) {
		arquivo = fopen("arquivoEmprestimo.txt", "w");
		fprintf(arquivo, "0xBADA55\nlivroId i 6 y n\nleitorId i 6 y n\nsequencia i 4 y n\ndataRetirada c 8 y n\ndataPrevistaParaDevolucao c 8 y n\n$\n");
		fclose(arquivo);
	}else{
		if(!(verificaHex(arquivo))) {
			arquivo = fopen("arquivoEmprestimo.txt", "w");
			fprintf(arquivo, "0xBADA55\nlivroId i 6 y n\nleitorId i 6 y n\nsequencia i 4 y n\ndataRetirada c 8 y n\ndataPrevistaParaDevolucao c 8 y n\n$\n");
			fclose(arquivo);
		}
	}
}

void insercao(char *nomeArquivo, BTree *btree){
	FILE * arquivo;
	int comeca=0,cont=0;
	int tam = 0;
	char ch;
	char tamInfo[2];
	int flagTipo = 1, flagNotNull =1, flagAutoIncrement = 1, flagNome = 1, flagTam = 1; // Flags pra ajudar esse parsing loco
	arquivo = fopen(nomeArquivo, "r");
	Info informacao;
	while((ch = fgetc(arquivo)) != '\n'); // ignora o HEX
	while((ch = fgetc(arquivo)) != '$'){

		//printf("%c\n", ch);
		//printf("comeca = %d\n", comeca);

		if(comeca == 0 && flagNome){
			while(ch != ' '){
				//printf("%c\n", ch);
				strcat(informacao.nome, &ch);
				ch = fgetc(arquivo);			
			}		
			flagNome = 0;
		}
		if(comeca == 1 && flagTipo){
			informacao.tipo = ch;
			//printf("informacao.tipo = %c\n", informacao.tipo);
			flagTipo = 0;
		}
		if(comeca == 2 && flagTam){
			while(1){
				tamInfo[0]=ch;	
				ch = fgetc(arquivo);
				if(ch!=' '){
					tamInfo[1]=ch;
					cont=1;
				}
				break;
			}
			if(cont==1){
				tam = ((((int)tamInfo[0])-48)*10)+(((int)tamInfo[1])-48);
			}else{
				tam = (((int)tamInfo[0])-48)*10;
			}
			informacao.tamInfo = tam;
			flagTam = 0;
		}
		if(comeca == 3 && flagNotNull){
			informacao.notNull = ch;
			//printf("info.notNull = %c\n", informacao.notNull);
			flagNotNull = 0;
		}
		if(comeca == 4 && flagAutoIncrement){
			informacao.autoIncrement = ch;
			//printf("informacao.autoIncrement = %c\n", informacao.autoIncrement);
			flagAutoIncrement = 0;

		}
		if(ch == ' '){
			comeca++;
		}
		if(ch=='\n'){
			insereInfoNoArquivo(nomeArquivo, informacao, btree);
			strcpy(informacao.nome, "");
			informacao.tipo = ' ';
			comeca = 0;	
			strcpy(tamInfo, "");
			tam = 0;
			flagTipo = 1;
			flagAutoIncrement = 1;
			flagNotNull = 1;
			flagNome = 1;
			flagTam = 1;		
		}
	}
	fclose(arquivo);
}

void insereInfoNoArquivo(char*nomeArquivo, Info informacao, BTree *btree){
	FILE * arquivo;
	char *inf;
	int i;
	int maxid;
	inf = malloc(sizeof(char)*informacao.tamInfo);
	arquivo = fopen(nomeArquivo,"a");
	//printf(" auto-increment?  %c\n", informacao.autoIncrement);
	if(informacao.autoIncrement == 'y'){
		maxid = buscaMaiorChave(btree->raiz);
		maxid++;
		insereChave(btree, maxid);
		//printf("id = %d\n", maxid);
		sprintf(inf, "%d", maxid);
		FILE *arquivoB = NULL;
		arquivoB = fopen(btree->nomeB, "a");
		//strcat(inf, "\n");								// ???
		//fprintf(arquivoB, "%s\n", inf);
		fputs(inf, arquivoB);
		fclose(arquivoB);
	}else{
		printf("Digite a %s:\n",informacao.nome);
		//fflush(stdin);
		__fpurge(stdin);
		scanf("%s",inf); // ta funfando assim
		//gets(inf);
		//printf("%d\n", informacao.tamInfo);
		while(strlen(inf)<0 && informacao.notNull == 'y'){
			printf("Por favor, a informacao '%s' nao pode ser nula, digite novamente:\n",informacao.nome);
			//fflush(stdin);
			__fpurge(stdin);
			scanf("%s",inf);  // ta funfando assim
			//gets(inf);
		}
	}
	//printf("TAMANHO = %d , %d\n",strlen(inf),informacao.tamInfo);
	if(strlen(inf)<informacao.tamInfo){
		//printf("oi\n");
		for (i = strlen(inf); i < informacao.tamInfo; i++){
			inf[i]= ' ';
		}
		//printf("TAMANHO = %d\n",strlen(inf));
	}else{
		if(strlen(inf)>informacao.tamInfo){
			//printf("INFO MAIOR\n");
			char *inf2;
			inf2 = malloc(sizeof(char)*informacao.tamInfo);
			for (i = 0; i < informacao.tamInfo; ++i){
				inf2[i] = inf[i];
			}
			fprintf(arquivo, "%s\n",inf2);
			fclose(arquivo);
			return;
		}
	}
	//printf("%s\n", inf);
	fprintf(arquivo, "%s\n",inf);
	fclose(arquivo);
}

int verificaHex(FILE *arquivo) {
	char ch;
	char hex[8] = "0xBADA55";
	int i = 0;
	while((ch=fgetc(arquivo))!= '\n') {
		if (ch != hex[i]) return 0;
		i++;
	}
	return 1;
}
void read(char*nomeArquivo, BTree *btree,int id){
 	//VERIFICAR SE O ID TA NA BTREE
 	BTreeNo *node;
 	int i=0;
 	node = busca(btree->raiz,id);
 	if(node == NULL){
 		printf("cadastro nao encontrado\n");
 		return;
 	}
 	//printf("%p\n",node);
 	while(i<= 2*node->grau-1){
 		//printf("%d %c\n",node->chaves[i],node->del[i]);
 		if(node->chaves[i] == id && node->del[i]=='s'){
 			printf("cadastro ja deletado\n");
 			return;
 		}
 		i++;
 	}
 	int j=0,cont=0, comeca = 0, tamTotal = 0, flagTam = 1;
 	int tam;
 	char ch;
 	char tamInfo[2];
 	FILE * arquivo;
	arquivo = fopen(nomeArquivo, "r");
 	i=0;
 	while((ch = fgetc(arquivo)) != '\n'); // ignora o HEX
 	while((ch = fgetc(arquivo)) != '$'){
 		if(comeca == 2 && flagTam){
			while(1){
				tamInfo[0]=ch;	
				ch = fgetc(arquivo);
				if(ch!=' '){
					tamInfo[1]=ch;
					cont=1;
				}
				break;
			}
			if(cont==1){
				tam = ((((int)tamInfo[0])-48)*10)+(((int)tamInfo[1])-48);
			}else{
				tam = (((int)tamInfo[0])-48)*10;
			}
			tamTotal+=tam;
			i++;
			
			flagTam = 0;
		}
		if(ch == '\n'){
			comeca = 0;
			memset(tamInfo,0,strlen(tamInfo));
			flagTam = 1;
		}
		if(ch == ' '){
			comeca++;
		}
	}
	ch=fgetc(arquivo);
	fseek(arquivo,((tamTotal+i+1)*(id-1)),SEEK_CUR);
	while(i>=j){
		ch = fgetc(arquivo);
		if(ch == '\n'){
			j++;
		}
		printf("%c",ch);
	}
	fclose(arquivo);
 }





 void delete(char *nomeArquivo, BTree *btree,int id){
 	BTreeNo *node;
 	int i=0;
 	node = busca(btree->raiz,id);
 	//printf("%p\n",node);
 	while(i<= 2*node->grau-1){
 		//printf("%d %c\n",node->chaves[i],node->del[i]);
 		if(node->chaves[i] == id){
 			node->del[i]='s';
 		}
 		i++;
 	}

}
 void update(char *nomeArquivo, BTree *btree,int id){
 	//VERIFICAR SE O ID TA NA BTREE
 	BTreeNo *node;
 	int i=0;
 	node = busca(btree->raiz,id);
 	if(node == NULL){
 		printf("cadastro nao encontrado\n");
 		return;
 	}
 	//printf("%p\n",node);
 	while(i<= 2*node->grau-1){
 		//printf("%d %c\n",node->chaves[i],node->del[i]);
 		if(node->chaves[i] == id && node->del[i]=='s'){
 			printf("cadastro ja deletado\n");
 			return;
 		}
 		i++;
 	}
 	int j=0,cont=0, comeca = 0, tamTotal = 0, flagTam = 1,tamanhoInfo=0;
 	int tam;
 	char ch;
 	char tamInfo[2];
 	FILE * arquivo;
	arquivo = fopen(nomeArquivo, "r");
 	while((ch = fgetc(arquivo)) != '\n'); // ignora o HEX
 	while((ch = fgetc(arquivo)) != '$'){
 		if(comeca == 2 && flagTam){
			while(1){
				tamInfo[0]=ch;	
				ch = fgetc(arquivo);
				if(ch!=' '){
					tamInfo[1]=ch;
					cont=1;
				}
				break;
			}
			if(cont==1){
				tam = ((((int)tamInfo[0])-48)*10)+(((int)tamInfo[1])-48);
			}else{
				tam = (((int)tamInfo[0])-48)*10;
			}
			tamTotal+=tam;
			i++;
			
			flagTam = 0;
		}
		if(ch == '\n'){
			comeca = 0;
			memset(tamInfo,0,strlen(tamInfo));
			flagTam = 1;
		}
		if(ch == ' '){
			comeca++;
		}
	}
	char *str;
	str = (char*) malloc(sizeof(char)*tamTotal+i-1);
	int totalDeInfo=i,k=0;
	for (j = 0; j < tamTotal+i-1; j++){
		str[j]=' ';
	}
	fclose(arquivo);
	tamTotal=0;
	char* info;
 	FILE * arquivo1;
	arquivo1 = fopen(nomeArquivo, "r+");
	while((ch = fgetc(arquivo1)) != '\n'); // ignora o HEX
 	while((ch = fgetc(arquivo1)) != '$'){
 		if(comeca == 2 && flagTam){
			while(1){
				tamInfo[0]=ch;	
				ch = fgetc(arquivo1);
				if(ch!=' '){
					tamInfo[1]=ch;
					cont=1;
				}
				break;
			}
			if(cont==1){
				tam = ((((int)tamInfo[0])-48)*10)+(((int)tamInfo[1])-48);
			}else{
				tam = (((int)tamInfo[0])-48)*10;
			}
			info=(char*)malloc(sizeof(char)*tam);
			scanf("%s",info);
			tamanhoInfo= strlen(info);
			if(tamanhoInfo>tam){
				char*info2;
				for (i = 0; i < tam; i++){
					info2[i]=info[i];
				}
				if(k+1<totalDeInfo){
					info[i]='\n';	
					j=0;
					for (i = tamTotal; i < (tamTotal+tam+1); i++){
						if(info2[j]!= '\0'){
							str[i]=info2[j];
							j++;
						}
					}
				}else{
					j=0;
					for (i = tamTotal; i < (tamTotal+tam+1); i++){
						if(info2[j]!= '\0'){
							str[i]=info2[j];
							j++;
						}
					}
				}
			}else{
				for(i=tamanhoInfo;i<tam;i++){
					info[i]=' ';
				}
				if(k+1<totalDeInfo){
					info[i]='\n';	
					j=0;
					for (i = tamTotal; i < (tamTotal+tam+1); i++){
						if(info[j]!= '\0'){
							str[i]=info[j];
							j++;
						}
					}
				}else{
					j=0;
					for (i = tamTotal; i < (tamTotal+tam+1); i++){
						if(info[j]!= '\0'){
							str[i]=info[j];
							j++;
						}
					}
				}
			}
			tamTotal+=tam+1;
			k++;
			flagTam = 0;
		}
		if(ch == '\n'){
			comeca = 0;
			memset(tamInfo,0,strlen(tamInfo));
			flagTam = 1;
		}
		if(ch == ' '){
			comeca++;
		}
	}
	//printf("string = %s",str);
	//printf("%d",strlen(str) );
	ch=fgetc(arquivo1);
	fseek(arquivo1,((tamTotal-1)*(id-1)),SEEK_CUR);
	/*for (i = 0; i < tamTotal+j; i++){
		if(str[i]=='.'){
			fprintf(arquivo1,"\n");
		}else{
			fprintf(arquivo1,"%c",  str[i]);
		}
	}*/
	fprintf(arquivo1, "%s", str);
	//fprintf(arquivo1,"\n");
	fclose(arquivo1);
 }
