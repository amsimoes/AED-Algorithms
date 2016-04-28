#include <stdio.h>
#include <time.h>

void exB(int N) {
	int i, j, aux;

	/* printf("2\n"); */
	for(i=3;i<N;i++) {	// N-4
		if(i % 2 != 0) {	// 2
			aux = 0;	// 1
			for(j=3; j*j<=i; j+=2) {	// raiz(N-4) = (N-4) elevado a 1/2
				if (i % j == 0) { // 2
					aux++;	// 2
				}
			}
			/*if(aux == 0) { // 1
				printf("%d\n", i); // 1
			}*/
		}
	}
}

int main(int argc, char** argv) {
	clock_t begin, end;
	double time_spent;

	begin = clock();
	int N = atoi(argv[1]);
	exB(N);
	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
}