#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
	char* palavra;
	char* traducao;
	int consultas;
	bool marcador;
	struct node* left;
	struct node* right;
} Node;

void destroy_tree(struct node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		free(leaf);
	}
}

int compare(char* palavra1, char* palavra2) {
	return(strcmp(palavra1, palavra2));
}

void printTree(struct node* node) {
	if (node == NULL)
		return;

	if(node->left) {
		printf("left\n");
		printTree(node->left);
	}
	printf("%s %s\n", node->palavra, node->traducao);
	if(node->right) {
		printf("right\n");
		printTree(node->right);
	}
}

void trim(char* line, char* comando, char* p1, char* p2) {
	const char space[2] = " \n";
	char* token;
	int i = 0;

	char **array = (char**)malloc(sizeof(char*)*3);
	for(i=0; i<3; i++) {
		array[i] = (char*)malloc(50*sizeof(char));
	}

	i = 0;
	token = strtok(line, space);
	while(token != NULL) {
		array[i] = token;
		/* printf("%s\n", token); */
		token = strtok(NULL, space);
		i++;
	}

	strcpy(comando, array[0]);
	strcpy(p1, array[1]);
	strcpy(p2, array[2]);
}