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

	int *sequencia = (int*) malloc(N*sizeof(int));

	begin = clock();

	flag = 0;
	soma = 0;
	i = 1;
	j = 1;
	while ((soma != V) && (i <= N)) {
		while ((soma < V) && (j <= N)) {
			soma += sequencia[j-1];
			/*if (soma == V) {
				printf("SUBSEQUENCIA NA POSICAO %d\n", i);
				flag = 1;
				break;
			} */
			j++;
		}
		if (flag == 1)
			break;
		soma -= sequencia[i-1];
		/*if(soma == V) {
			printf("SUBSEQUENCIA NA POSICAO %d\n", i+1);
			break;
		} */
		i++;
	}
	/*if(soma != V && flag != 1)
		printf("SUBSEQUENCIA NAO ENCONTRADA\n");*/
	
	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
}