struct node {
	char palavra[40];
	char traducao[100];
	int consultas;
	bool marcador;
	struct node *left;
	struct node *right;
};

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
		printf("Splay - Palavra a inserir = %s\n", palavra);
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
