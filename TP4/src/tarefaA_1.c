#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void printArray(int n, int d, int** array) {
  int i, j;
  /* printf("** ARRAY [%d][%d] **\n", n, d); */
  for(i=0;i<n;i++) {
    for(j=0;j<d;j++) {
      if(j == d-1)
        printf("%d\n", array[i][j]);
      else
        printf("%d ", array[i][j]);
    }
  }
}

int numVerify(int n) {
  if(n < -999 || n > 999) {
    return 1;
  }
  return 0;
}

void scan(int n, int d, int** array) {
  int i, j, aux;
  char line[50];

  /* Preenchimento do array */
  for(i=0;i<n;i++) {
    fgets(line, 50, stdin);
    if(d == 1) {
      sscanf(line, "%d", &array[i][0]);
    } else if(d == 2) {
      sscanf(line, "%d %d", &array[i][0], &array[i][1]);
    } else if(d == 3) {
      sscanf(line, "%d %d %d", &array[i][0], &array[i][1], &array[i][2]);
    }
    /*for(j=0;j<d;j++) {
      aux = numVerify(array[i][j]);
      if(aux == 1) {
        /* printf("Erro! Numeros tem de ser entre -999 e 999\n");
        return 1;
      }
    }*/
    memset(line, 0, sizeof(line));
  }
}

void insertSort(int n, int d, int** array) {
  int i, j, k;
  int* temp;

  j = 0;
  for(i=1;i<n;i++) { /* percorrer conjuntos */
    k=i;
    while(k>0 && array[k][j] <= array[k-1][j]) {
      while(j<d && array[k][j] == array[k-1][j]) {
        /* printf("Igual!\n"); */
        j++;
      }
      if(array[k][j] < array[k-1][j]) {
        temp = array[k-1];
        array[k-1] = array[k];
        array[k] = temp;
        k--;
      } else {
        j=0;
        break;
      }
      j=0;
    }
  }
}

/* 0 <= n <= 2 000 000 */
/* 1 <= d <= 3 */
int main(int argc, char* argv) {
  int n, d;
  char linha[50];
  int i;

  /* Ler numero de linhas e dimensao */
  fgets(linha, 50, stdin);
  sscanf(linha, "%d %d", &n, &d);

  if((n < 2 || n > 1000000) || (d < 1 || d > 3)) {
    /* printf("Erro! Condicoes: \n2 <= n <= 1000000 | 1 <= d <= 3\n"); */
    return -1;
  }

  /* Alocacao de memoria em array 2d */
  int** array = (int**) malloc(sizeof(int*) * n);
  if(array) {
    for(i=0;i<n;i++) {
      array[i] = (int*) malloc(sizeof(int) * d);
    }
  }

  scan(n, d, array);
  insertSort(n, d, array);
  printArray(n, d, array);

  return 0;
}
