#include <iostream>

//- Prepare o programa para que seja possível ajustar a dimensão do vetor e
//o número de threads (para os paralelos);
//- Prepare o programa para calcular o tempo de processamento.

#include <sys/time.h>
#include "sort.h"

int main() {
  int size = 20;

  struct timeval start;
  struct timeval end;

  int* vector = (int*) calloc(size, sizeof(int));
  int* result = (int*) calloc(size, sizeof(int));

  for(int i = 0; i < size; i++) {
    vector[i] = rand() % 1000;
  }

  for(int i = 0; i < size; i++) {
    printf("%d ", vector[i]);
  }

  printf("\n\n");

  gettimeofday(&start, NULL);

  rank_sort(vector, size, 0, size, result);

  gettimeofday(&end, NULL);

  long long difference = diffTime(start, end);

  printf("Time elapsed in milliseconds: %lld \n \n", difference);

  for(int i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }

  return 0;
}

