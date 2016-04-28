void selectionSort(int n, int d, int** array) {
  int i, j, k;
  int* temp;

  k = 0;
  while(k <= (n/2)) {
    for(i=0;i<n-1;i++) {
      for(j=0;j<d;j++) {
        if (array[i][j] < array[i+1][j]) {
          break;
        } else if (array[i][j] > array[i+1][j]) {
          temp = array[i+1];
          array[i+1] = array[i];
          array[i] = temp;
          break;
        }
      }
    }
    k++;
  }
}
