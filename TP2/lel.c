#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void main() {
	int N, i, j, k, aux;
	clock_t begin, end;
	double time_spent;

	scanf("%d", &N);

	begin = clock();

	int *primos = (int*) malloc((N-2)*sizeof(int));
	int *finais = (int*) malloc((N-2)*sizeof(int));

	for(i=1;i<N;i++) {
		primos[i-1] = i;
		finais[i-1] = i;
	}

	for(i=1;i<N;i++) {
		for(j=i;j<(N-1)/3;j++) {
			aux = primos[i-1] + primos[j-1] + 2*primos[i-1]*primos[j-1];
			if (aux > N) {
				break;
			} else {
				for(k=1;k<N;k++) {
					if(primos[k-1] == aux)
						finais[k-1] = 0;
				}
			}
		}
	}

	printf("2\n");
	for(i=0;i<N/2;i++) {
		if(finais[i-1] != 0) {
			printf("%d\n", (2*finais[i-1] + 1));
		}
	}

	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %f\n", time_spent);
}