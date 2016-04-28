#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void exD(int N) {
	long i, j, k, aux;
	long index;

	long *primos = (long*) malloc((N+1)*sizeof(long));

	for(i=0; i<N/2; i++) {
		primos[i] = 1;
	}

	for(i=1; i<=N/2; i++) {
		for(j=i; j<((N-1)/3); j++) {
			index = (i+j+2*i*j);
			if (index > N) {
				break;
			} else {
				primos[index] = -1;
			}
		}
	}
	
	/* printf("2\n"); */
	for(i=1; i <= N; i++) {
	    if(primos[i] != -1) {
			/* if((2*i + 1) < N)
				printf("%lu\n", (2*i+1)); */
		} 
	}
}

int main(int argc, char** argv) {
	clock_t begin, end;
	double time_spent;

	begin = clock();

	/*int N;
	
	scanf("%d", &N); */
	int N = atoi(argv[1]);
	exD(N);

	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
	
	return 0;
}