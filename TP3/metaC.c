#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

/* #define DEBUG */
#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x - 1)/2

struct node {
	char palavra[40];
	char traducao[100];
	int consultas;
	bool marcador;
	struct node *left;
	struct node *right;
};

struct heapNode {
	char palavra[40];
	char traducao[100];
	int consultas;
	int marcador;
};

struct heapNode heap[200000];
struct heapNode heap_copy[200000];
int heapSize;

int balance_factor(struct node* node);
int node_height(struct node* node);
void trim(char* palavra);
void printMarcadas(struct node* leaf);
void printTree(struct node* leaf);
struct node* balance_tree(struct node* node);
struct node* leftleftRotation(struct node* node);
struct node* rightrightRotation(struct node* node);
struct node* leftrightRotation(struct node* node);
struct node* rightleftRotation(struct node* node);
void printSplay(struct node* root_splay);

void editWord(char* palavra) {
	int i = 0;
	while(palavra[i] != '\0') {
		palavra[i] = tolower(palavra[i]);
		i++;
	}
	trim(palavra);
}

void insert(char* palavra, char* traducao, struct node** leaf) {
	if (*leaf == 0) {
		*leaf = (struct node*) malloc(sizeof(struct node));
		editWord(palavra);
		editWord(traducao);
		strcpy((*leaf)->palavra, palavra);
		strcpy((*leaf)->traducao, traducao);
		(*leaf)->marcador = false;
		(*leaf)->left = 0;
		(*leaf)->right = 0;
	} else if (strcmp(palavra,(*leaf)->palavra) < 0) {
		insert(palavra, traducao, &(*leaf)->left);
	} else if (strcmp(palavra, (*leaf)->palavra) >= 0) {
		insert(palavra, traducao, &(*leaf)->right);
	}
}

struct node* procura(struct node* node, char* palavra, int marca, int print, int heap) {
	if(!node) {
		if (print == 1 || marca == 1)
			printf("PALAVRA NAO EXISTENTE\n");
		return NULL;
	} else {
		if(strcmp(palavra, node->palavra) == 0) {
			if(marca == 1) {
				if(node->marcador == false) {
					node->marcador = true;
					node->consultas += 1;
				}
				/* printf("%s MARCADA\n", palavra); */
			}
			if(print == 1) {
				printf("%s %s\n", node->palavra, node->traducao);
				node->consultas += 1;
			}
			return node;
		} else {
				if(strcmp(palavra, node->palavra) < 0)
					return(procura(node->left, palavra, marca, print, heap));
				else if(strcmp(palavra, node->palavra) > 0)
					return(procura(node->right, palavra, marca, print, heap));
		}
	}
}

void initHeap() {
	heapSize = 0;
}

void printHeap() {
	int i;
	printf("*** HEAP TREE ***\n");
	for(i=1;i < heapSize+1; i++) {
		printf("Palavra %s | Consultas %d\n", heap[i].palavra, heap[i].consultas);
	}
}

int verifyHeap(char* palavra, int marca) {
	int i;
	for(i=1;i < heapSize+1;i++) {
		if(strcmp(heap[i].palavra, palavra) == 0) {
			printf("MARCADA = %d\n", heap[i].marcador);
			if(marca == 1) {
				if(heap[i].marcador == 0) {
					heap[i].marcador = 1;
					heap[i].consultas += 1;
				}
			} else {
				heap[i].consultas += 1;
			}
			return i;
		}
	}
	return 0;
}


void heapEnqueue(char* palavra, int consultas, int marca) {
	int aux = verifyHeap(palavra, marca);
	if(aux == 0) {
		printf("A inserir nova palavra...\n");
		heapSize++;

		heap[heapSize].consultas = consultas;

		int new = heapSize;
		while(heap[new/2].consultas < consultas && new != 1) {
			heap[new] = heap[new/2];
			new = new / 2;
		}
		heap[new].consultas = consultas;
		if(marca == 1)
			heap[new].marcador = 1;
		strcpy(heap[new].palavra, palavra);
		heap[new].marcador = 0;
	} else {
		printf("No a aumentar = %s\n", heap[aux].palavra);
		printf("Pai do no = %s\n", heap[aux/2].palavra);
		while(heap[aux].consultas > heap[aux/2].consultas && aux > 1) {
			struct heapNode temp = heap[aux/2];
			heap[aux/2] = heap[aux];
			heap[aux] = temp;
		}
	}
}

void heapDequeue(struct heapNode* heap2) {
	int child, now;
	struct heapNode max, last;
	int i = 1;
	while(i < heapSize+1) {
		max = heap2[1];
		last = heap2[heapSize--];
		now = 1;
		while(now*2 <= heapSize) {
			child = now*2; /* Left Child */
			if(child != heapSize && heap2[child+1].consultas > heap2[child].consultas) /* Se nao for leaf e encontrar maior dos filhos */
				child++;
			if(last.consultas < heap2[child].consultas) {
				heap2[now] = heap2[child];
			} else if(last.consultas == heap2[child].consultas) {
				if(strcmp(last.palavra, heap2[child].palavra) < 0)
					break;
				else
					heap2[now] = heap2[child];
			} else { /* Esta no devido lugar */
				break;
			}
			now = child;
		}
		heap2[now] = last;
		printf("Palavra: %s | Consultas: %d\n", max.palavra, max.consultas);
	}
}

struct node* rightRotate(struct node *y) {
	struct node* x = y->left;
	y->left = x->right;
	x->right = y;
	return x;
}

struct node* leftRotate(struct node *x) {
	struct node* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

struct node* splay(struct node* root_splay, char* palavra) {
	if (root_splay == NULL || strcmp(root_splay->palavra, palavra) == 0) {
		return root_splay;
	}

	if(strcmp(root_splay->palavra, palavra) > 0) { /* Palavra na arvore da esquerda */
		if(root_splay->left == NULL)
			return root_splay;

		if(strcmp(root_splay->left->palavra, palavra) > 0) {
			root_splay->left->left = splay(root_splay->left->left, palavra);
			root_splay = rightRotate(root_splay);
		} else if (strcmp(root_splay->left->palavra, palavra) < 0) {
			root_splay->left->right = splay(root_splay->left->right, palavra);

			if (root_splay->left->right != NULL)
				root_splay->left = leftRotate(root_splay->left);
		}
		return (root_splay->left == NULL) ? root_splay : rightRotate(root_splay);
	} else { /* Palavra na arvore da direita */
		if (root_splay->right == NULL)
			return root_splay;

		if(strcmp(root_splay->right->palavra, palavra) > 0) {
			root_splay->right->left = splay(root_splay->right->left, palavra);

			if (root_splay->right->left != NULL)
				root_splay->right = rightRotate(root_splay->right);
		} else if (strcmp(root_splay->right->palavra, palavra) < 0) {
			root_splay->right->right = splay(root_splay->right->right, palavra);
			root_splay = leftRotate(root_splay);
		}

		return (root_splay->right == NULL) ? root_splay : leftRotate(root_splay);
	}
}

struct node* search_splay(struct node* root_splay, char* palavra) {
	return splay(root_splay, palavra);
}

struct node* insert_splay(struct node* root_splay, char* palavra, char* traducao) {
	if (root_splay == NULL) {
		struct node* node = (struct node*) malloc(sizeof(struct node));
		/*printf("Splay - Palavra a inserir = %s\n", palavra);*/
		strcpy(node->palavra, palavra);
		strcpy(node->traducao, traducao);
		node->left = NULL;
		node->right = NULL;
		return(node);
	}

	root_splay = splay(root_splay, palavra);

	if (strcmp(root_splay->palavra, palavra) == 0)
		return root_splay;

	struct node* node = (struct node*) malloc(sizeof(struct node));
	strcpy(node->palavra, palavra);
	strcpy(node->traducao, traducao);

	if (strcmp(root_splay->palavra, palavra) > 0) {
		node->right = root_splay;
		node->left = root_splay->left;
		root_splay->left = NULL;
	} else {
		node->left = root_splay;
		node->right = root_splay->right;
		root_splay->right = NULL;
	}
	return node;
}

void printSplay(struct node* root_splay) {
	if (root_splay != NULL) {
		printf("%s\n", root_splay->palavra);
		printSplay(root_splay->left);
		printSplay(root_splay->right);
	}
}

int main(int argc, char** argv) {
	struct node *root_avl = NULL;
	struct node *root_splay = NULL;
	struct node *aux = NULL;
	struct node *aux_heap = NULL;

	initHeap();

	char* fname = argv[1];
	char* op = argv[2];
	/* printf("fname = %s\n", fname); */

	char comando[20];
	char line[180];
	char palavra[40], traducao[100];
	char linha[150];
	clock_t begin, end;
	double time_spent;
	int i;

	double tempo_pesquisas = 0;
	int n_pesquisas = 0;

	while(fgets(line, 180, stdin) != NULL && line[0] != '\n') {
		sscanf(line, "%s %s %100[^\n]s", comando, palavra, traducao);

		aux = NULL;

		if(!isalpha(palavra[0]))
			memset(palavra, 0, sizeof(palavra));
		else
			trim(palavra);
		if(!isalpha(traducao[0]))
			memset(traducao, 0, sizeof(traducao));
		else
			trim(traducao);

		if(strcmp(comando, "CARREGA") == 0) {
			FILE *fp = fopen(fname, "r");
			begin = clock();
			memset(linha, 0, sizeof(linha));
			fgets(linha, 150, fp);
			sscanf(linha, "%s %100[^\n]s", palavra, traducao);
			while(strcmp(palavra, "fim$dicionario") != 0) {
				if(procura(root_avl, palavra, 0, 0, 0) != NULL) {
						/* printf("PALAVRA JA EXISTENTE %s\n", palavra); */
				} else {
						insert(palavra, traducao, &root_avl);
				}
				fgets(linha, 150, fp);
				sscanf(linha, "%s %100[^\n]s", palavra, traducao);
			}
			root_avl = balance_tree(root_avl);
			end = clock();
			fclose(fp);
			time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
			printf("Time Carrega = %f\n", time_spent);
			printf("DICIONARIO CARREGADO\n");
			/* printf("Root AVL = %s\n", root_avl->palavra); */
		} else if (strcmp(comando, "ACRESCENTA") == 0 && verify(palavra) != 0 && verify(traducao) != 0) {
			if (procura(root_avl, palavra, 0, 0, 0) != NULL) {
				printf("PALAVRA JA EXISTENTE\n");
			} else {
				insert(palavra, traducao, &root_avl);
				root_avl = balance_tree(root_avl); /* META B - AVL */
				printf("PALAVRA ACRESCENTADA\n");
			}
		} else if (strcmp(comando, "PESQUISA") == 0 && verify(palavra) != 0) {
				begin = clock();
			  aux = procura(root_splay, palavra, 0, 0, 0);
				/*heapEnqueue(aux->palavra, aux->consultas, 0);
				printHeap();*/
				root_splay = insert_splay(root_splay, palavra, aux->traducao);
				/*printf("*** SPLAY TREE ***\n");
				printSplay(root_splay);*/
				end = clock();
				time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
				n_pesquisas++;
				if (n_pesquisas < 10000) {
					tempo_pesquisas += time_spent;
				} else {
					printf("Tempo de %d pesquisas = %f\n", n_pesquisas, tempo_pesquisas);
				}
		} else if (strcmp(comando, "MARCA") == 0 && verify(palavra) != 0) {
				aux = procura(root_avl, palavra, 1, 0, 0);
				if(aux != NULL) {
					/* heapEnqueue(aux->palavra, aux->consultas, 1); */
					root_splay = insert_splay(root_splay, palavra, aux->traducao);
					/*printf("*** SPLAY TREE ***\n");
					printSplay(root_splay);*/
				}
		} else if (strcmp(comando, "LISTA_ALFANUM") == 0) {
				begin = clock();
				printTree(root_avl);
				end = clock();
				time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
				printf("Time LISTA = %f\n", time_spent);
				printf("FIM LISTA\n");
		} else if (strcmp(comando, "LISTA_MARCADAS") == 0) {
				printMarcadas(root_avl);
				printf("FIM MARCADAS\n");
		} else if (strcmp(comando, "LISTA_MAIS_ACESSOS") == 0) {
				heapDequeue(heap);
				printf("FIM LISTA ACESSOS\n");
		} else if (strcmp(comando, "\n") == 0) {
				exit(0);
		}

		memset(palavra, 0, sizeof(palavra));
		memset(traducao, 0, sizeof(traducao));
	}
	return 0;
}

void printMaisAcessos(struct node* leaf) {
	if (!leaf)
		return;
}

void printTree(struct node* leaf) {
	if(!leaf)
		return;

	printTree(leaf->left);
	/* printf("%s\n", leaf->palavra); */
	printTree(leaf->right);
}

void printMarcadas(struct node* leaf) {
	if(!leaf)
		return;

	printMarcadas(leaf->left);
	if(leaf->marcador) {
		printf("%s\n", leaf->palavra);
	}
	printMarcadas(leaf->right);
}

void trimTabs(char* palavra) {
	int i;
	for(i=0;palavra[i] != '\0';i++) {
		if(palavra[i] == '\t') {
			palavra[i] = ' ';
		}
	}
}

void trim(char* palavra) {
	trimTabs(palavra);
	char *dest = palavra;

	while(*palavra != '\0') {
		while(*palavra == ' ' && *(palavra + 1) == ' ')
			palavra++;
		*dest++ = *palavra++;
	}

	*dest = '\0';
	if(*(dest-1) == ' ')
		*(dest-1) = '\0';
}

int verify(char* palavra) {
	int i;
	for(i=0; palavra[i] != '\0'; i++) {
		if(!isalpha(palavra[i]))
			return 0;
	}
	return 1;
}

/* * * *
 * AVL *
 * * * */

int node_height(struct node* node) {
	int h_left = 0;
	int h_right = 0;

	if (node->left)
		h_left = node_height(node->left);
	if (node->right)
		h_right = node_height(node->right);

	return h_right > h_left ? ++h_right : ++h_left;
}

int balance_factor(struct node* node) {
	int balance = 0;

	/* printf("node a calcular balanco = %s\n", node->palavra); */

	if (node->left) {
		balance += node_height(node->left);
	}
	if (node->right) {
		/* printf("node->right->palavra = %s\n", node->right->palavra); */
		balance -= node_height(node->right);
	}

	/* printf("factor = %d\n", balance); */
	return balance;
}

struct node* leftleftRotation(struct node* node) {
	struct node* a = node;
	struct node* b = a->left;
	struct node* c = b->left;

	a->left = b->right;
	b->right = a;

	return b;
}

struct node* rightrightRotation(struct node* node) {
	struct node* a = node;
	struct node* b = a->right;
	struct node* c = b->right;

	a->right = b->left;
	b->left = a;

	return b;
}

struct node* leftrightRotation(struct node* node) {
	struct node* a = node;
	struct node* b = a->left;
	struct node* c = b->right;

	b->right = c->left;
	a->left = c->right;
	c->right = a;
	c->left = b;

	return c;
}

struct node* leftrightRotation2(struct node* node) {
	struct node* a = node;
	struct node* b = a->left;
	struct node* c = b->right;
	/* printf("ola\n"); */

	a->left = c;
	c->left = b;
	b->right = c->left;
	/* return(leftleftRotation(a)); */
}

struct node* rightleftRotation(struct node* node) {
	struct node* a = node;
	struct node* b = a->right;
	struct node* c = b->left;

	a->right = c->left;
	b->left = c->right;
	c->left = a;
	c->right = b;

	return c;
}

struct node* balance_tree(struct node* node) {
	struct node* newroot_avl = NULL;

	#ifdef DEBUG
	printf("node a entrar na funcao: %s\n", node->palavra);
	#endif

	if (node->left) {
		#ifdef DEBUG
		printf("Going left...\n");
		#endif
		node->left = balance_tree(node->left);
	}
	if (node->right) {
		#ifdef DEBUG
		printf("Going right...\n");
		#endif
		node->right = balance_tree(node->right);
	}

	int balance = balance_factor(node);

	if (balance > 1) {
		#ifdef DEBUG
		printf("Node %s left heavy\n", node->palavra);
		#endif
		if (balance_factor(node->left) <= -1) {
			#ifdef DEBUG
			printf("Performing LeftRight rotation on node %s\n", node->palavra);
			#endif
			newroot_avl = leftrightRotation(node);
		} else {
			#ifdef DEBUG
			printf("Performing LeftLeft Rotation on node %s\n", node->palavra);
			#endif
			newroot_avl = leftleftRotation(node);
		}
	} else if (balance < -1) {
		#ifdef DEBUG
		printf("Node %s right heavy\n", node->palavra);
		#endif
		if (balance_factor(node->right) >= 1) {
			#ifdef DEBUG
			printf("Performing RightLeft rotation on node %s\n", node->palavra);
			#endif
			newroot_avl = rightleftRotation(node);
		}
		else {
			newroot_avl = rightrightRotation(node);
		}
	} else {
		#ifdef DEBUG
		printf("Node %s Balanced\n", node->palavra);
		#endif
		newroot_avl = node;
	}

	#ifdef DEBUG
	printf("new root_avl = %s\n", newroot_avl->palavra);
	#endif

	return newroot_avl;
}
