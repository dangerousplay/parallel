//
// Created by davi on 22/09/2020.
//

#include <iostream>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <omp.h>

//- Prepare o programa para que seja possível ajustar a dimensão do vetor e
//o número de threads (para os paralelos);
//- Prepare o programa para calcular o tempo de processamento.

#include "sort.h"

int main() {
  int size = 200000;
  int threads_number = omp_get_max_threads();
  int load_factor = size / threads_number;

  struct timeval start;
  struct timeval end;

  int* vector = (int*) calloc(size, sizeof(int));
  int* result = (int*) calloc(size, sizeof(int));

  for(int i = 0; i < size; i++) {
    vector[i] = rand();
  }

  gettimeofday(&start, NULL);

  #pragma omp parallel shared(size, threads_number, load_factor, vector, result) default(none)
  {
    int number = omp_get_thread_num();

    int start = load_factor * number;
    int end = load_factor * (number + 1);

    end = end > size ? size : end;

    end = number == threads_number ? size : end;

    printf("Thread Number %d start %d end %d \n\n", number, start, end);

    rank_sort(vector, size, start, end, result);
  }

  gettimeofday(&end, NULL);

  long long difference = diffTime(start, end);

  printf("Time elapsed in milliseconds: %lld \n \n", difference);

  /*for(int i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }*/

  return 0;

}
