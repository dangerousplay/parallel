//
// Created by davi on 22/09/2020.
//

#include <iostream>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/time.h>

//- Prepare o programa para que seja possível ajustar a dimensão do vetor e
//o número de threads (para os paralelos);
//- Prepare o programa para calcular o tempo de processamento.

#include "sort.h"

typedef struct {
  int thread_number;
  int load_factor;
  int* vector;
  int size;
  int* result;
  bool last;
} RankSort;

void* sort(RankSort* rank) {
  int start = rank->load_factor * rank->thread_number;
  int end = rank->load_factor * (rank->thread_number + 1);

  end = end > rank->size ? rank->size : end;

  end = rank->last ? rank->size : end;

  printf("Thread Number %d start %d end %d \n\n", rank->thread_number, start, end);

  rank_sort(rank->vector, rank->size, start, end, rank->result);

  free(rank);

  return NULL;
}



int main() {
  int size = 200000;
  int threads_number = get_nprocs();
  int load_factor = size / threads_number;

  struct timeval start;
  struct timeval end;

  pthread_t* threads = (pthread_t*) calloc(threads_number, sizeof(pthread_t));

  int* vector = (int*) calloc(size, sizeof(int));
  int* result = (int*) calloc(size, sizeof(int));

  for(int i = 0; i < size; i++) {
    vector[i] = rand();
  }

  /*for(int i = 0; i < size; i++) {
    printf("%d ", vector[i]);
  }*/

  printf("\n\n");

  gettimeofday(&start, NULL);
  
  for(int i = 0; i < threads_number; i++) {
    RankSort* arguments = (RankSort*) malloc(sizeof(RankSort));

    arguments->thread_number = i;
    arguments->load_factor = load_factor;
    arguments->vector = vector;
    arguments->size = size;
    arguments->result = result;
    arguments->last = (i+1) >= threads_number;

    int pthread_created = pthread_create(&threads[i], NULL,
                                         reinterpret_cast<void *(*)(void *)>(sort),
                                         arguments
                                         );

    if (pthread_created) {
      printf("failed to create thread: %d \n",pthread_created);

      exit(pthread_created);
    }
  }

  for(int i = 0; i < threads_number; i++) {
    int result = pthread_join(threads[i], NULL);

    if (result) {
      printf("Failed to join thread: %d", result);

      exit(result);
    }
  }

  gettimeofday(&end, NULL);

  long long difference = diffTime(start, end);

  printf("Time elapsed in milliseconds: %lld \n \n", difference);

  /*for(int i = 0; i < size; i++) {
    printf("%d ", result[i]);
  }*/

  return 0;
}
