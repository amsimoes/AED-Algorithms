#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
 
void exC(int N) {
    long i, j, k;
    int index;

    long *primos = (long*) malloc((N+1) * sizeof(long)); // (N+1)
 
    for(i=0; i<N; i++) {    
        primos[i] = 1;
    }
    
    i = 2;  // 1    
    while(i <= (N/2)) { // (N/2) - 2
        j = 2;  // 1
        while(j <= (N/i)) { // (N/[(N-2)-2])
            index = i * j;
            if (index > N) {
                break;
            } else {
                primos[index] = -1;
            }
            j++;
        }
        i++;
    }

    for(i=2; i<N; i++) {
        /*if(primos[i] != -1) 
            printf("%lu\n", i); */
    }   
}

int main(int argc, char** argv) {
    clock_t begin, end;
    double time_spent;

    begin = clock();

    int N = atoi(argv[1]);
    /*int N;

    scanf("%d", &N); */
    exC(N);
    
    end = clock();

    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    
    return 0;
}