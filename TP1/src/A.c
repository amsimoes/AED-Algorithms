#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
	int V, N, i, j, k, soma, aux;
	int flag;

	clock_t begin, end;
	double time_spent;

	N = atoi(argv[1]);
	V = atoi(argv[2]); 

	begin = clock();

	int *sequencia = (int*) malloc(N*sizeof(int));
	for(i=0; i<N; i++) {
		for(j=i; j<N; j++) {
			soma = 0;
			for(k=i; k <= j; k++) {
				soma += sequencia[k];
			}
			/*if (soma == V) {
				printf("SUBSEQUENCIA NA POSICAO %d\n", i+1);
				flag = 1;
			}*/
		}
		if (flag == 1)
			break;
	}
	/* if (flag == 0)
		printf("SUBSEQUENCIA NAO ENCONTRADA\n");*/

	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
}