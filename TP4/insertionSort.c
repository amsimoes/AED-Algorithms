/* Double Int Array *
 * n - number of elements *
 * d - number of numbers per element */

void insertSort(int n, int d, int** array) {
  int i, j, k;
  int* temp;

  for(i=1,k=i;i<n;i++) { /* percorrer conjuntos */
    while(k>0 && array[k][j] <= array[k-1][j]) {
      while(j<d && array[k][j] == array[k-1][j])
        j++;
      if(array[k][j] < array[k-1][j]) {
        temp = array[k-1];
        array[k-1] = array[k];
        array[k] = array[k-1];
        k--;
      }
      j=0;
    }
  }
}
