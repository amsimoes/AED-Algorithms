#include <stdio.h>
#include <time.h>

void exA(int N) {
	int i, j; // 2
	int x;	// 1

	for(i=2;i<N;i++) { // N-3
		x = 1;	// (N-3)(1)
		for(j=2;j<i;j++) {	// (N-3)(N-3)
			if(i % j == 0) {	// (N-3)(2)
				x = 0;	// (N-3)(1)
				break;
			}
		}
		/*if (x == 1) {
			printf("%d\n", i);
		}*/
	}
}	

int main(int argc, char** argv) {
	clock_t begin, end;
	double time_spent;

	begin = clock();
	int N = atoi(argv[1]);
	exA(N);
	end = clock();

	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
}