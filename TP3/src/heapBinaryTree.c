#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heapNode {
	int consultas;
	char* palavra;
} hNode;

typedef struct heapTree {
	int size;
	hNode* nodeTree;
} hTree;

void heapEnqueue(hTree* ht, struct node* avl_node) {
  if(ht->size) {
    ht->nodeTree = (hNode*) realloc(ht->nodeTree, (ht->size+1) * sizeof(hNode));
  } else {
    ht->nodeTree = (hNode*) malloc(sizeof(hNode));
  }

  /* preencher novo no */
  hNode* nodeHeap = (hNode*) malloc(sizeof(hNode));
  strcpy(nodeHeap->palavra, avl_node->palavra);
  nodeHeap->consultas = avl_node->consultas;

  /* while element is not in the root and el > parent(el) */
  int i = (ht->size) + 1; /* posicao do novo elemento */
  while(i && nodeHeap->consultas > ht->nodeTree[PARENT(i)].consultas) {
    ht->nodeTree[i] = ht->nodeTree[PARENT(i)];
    i = PARENT(i);
  }
  ht->nodeTree[i] = nodeHeap;
}

int minVerify(hTree* ht, hNode* p) {
  if (p.consultas < ht->nodeTree[RIGHT_CHILD(p)].consultas) {
    return 1;
  }
  if (p.consultas < ht->nodeTree[LEFT_CHILD(p)].consultas) {
    return 1;
  }
  return 0;
}

void swap(hNode *n1, hNode* n2) {
  hNode* temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

int isLeaf(hTree* ht, int i) {
  return (i < ht->size) ? 1 : 0;
}

int isBigger(hNode* n1, hNode* n2) {
  return (n1->consultas > n2->consultas) ? 1 : 0;
}

void dequeue(hTree* ht, int i) {
  int larger = (isLeaf(LCHILD(i)) == 1 && isBigger(ht->nodeTree[LCHILD(i)], ht->nodeTree[i]) == 1) ? LCHILD(i) : i;
  if(isLeaf(RCHILD(i)) == 1 && isBigger(ht->nodeTree[RCHILD(i)], ht->nodeTree[i]) == 1) {
    larger = RCHILD(i);
  }
  if(larger != i) {
    swap(&(ht->nodeTree[i]),&(ht->nodeTree(larger)));
    dequeue(ht, larger);
  }
}

void heapDequeue(hTree* ht) {
  while(ht->size) {
    printf("Maior numero de consultas: %s\n", ht->nodeTree[0].consultas);
    ht->nodeTree[0] = ht->nodeTree[(ht->size)--];
    ht->nodeTree = (hNode*) realloc(ht->nodeTree, ht->size * sizeof(hNode));
    dequeue(ht, 0);
  }
  printf("FIM LISTA ACESSOS\n");
}
