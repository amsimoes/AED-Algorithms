struct heapNode {
	char palavra[40];
	char traducao[100];
	int consultas;
};

struct heapNode heap[200000];
int heapSize;

void initHeap() {
	heapSize = 0;
}

void printHeap() {
	int i;
	printf("*** HEAP TREE ***\n");
	for(i = 1;i < heapSize+1; i++) {
		printf("Palavra %s | Consultas %d\n", heap[i].palavra, heap[i].consultas);
	}
}

int verifyHeap(char* palavra, int marca) {
	int i;
	for(i=1;i < heapSize+1;i++) {
		if(strcmp(heap[i].palavra, palavra) == 0) {
			if(marca != 1) {
				heap[i].consultas += 1;
				return i;
			} else {
				if(heap[i].marcador == 0) {
					heap[i].consultas += 1;
					return i;
				}
			}
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

if (strcmp(comando, "LISTA_MAIS_ACESSOS") == 0) {
		heapDequeue(heap);
		printf("FIM LISTA ACESSOS\n");
