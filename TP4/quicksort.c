#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int array[5];

void swap(int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

int hoarePartition(int first, int last) {
  int pivot, i, j, temp;
  pivot = array[first];
  i = first - 1;
  j = last + 1;
  while(1) {
    do {
      j = j - 1;
    } while (array[j] > pivot);
    do {
      i = i + 1;
    } while (array[i] < pivot);
    if (i < j)
      swap(i, j);
    else
      return j;
  }
}

int hoarePartition2(int first, int last) {
  int pivot, i, j, temp;
  pivot = array[first];
  i = first;
  j = last;
  while(1) {
    while(array[j] > pivot) {
      j = j - 1;
    }
    while(array[i] < pivot) {
      i = i + 1;
    }
    if (i < j)
      swap(i, j);
    else
      return j;
  }
}

void quickSort(int first, int last) {
  int pivot;
  if (first < last) {
    pivot = hoarePartition2(first, last);
    quickSort(first, pivot);
    quickSort(pivot+1, last);
  }
}

int main(int argc, char* argv) {
  int i;

  for(i=0;i<5;i++) {
    scanf("%d", &array[i]);
  }

  printf("Array original:\n");
  for(i=0;i<5;i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  quickSort(0, 5-1);

  printf("Array ordenado:\n");
  for(i=0;i<5;i++) {
    printf("%d ", array[i]);
  }
  printf("\n");

  return 0;
}
