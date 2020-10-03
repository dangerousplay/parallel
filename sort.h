//
// Created by davi on 22/09/2020.
//

#ifndef PARALLEL_SORT_H
#define PARALLEL_SORT_H

inline int compute_rank(const int* input, int size, int value) {
  int rank = 0;

  for(int i = 0; i < size; i++) {
    if(input[i] > value) {
      rank++;
    }
  }

  return rank;
}

inline void rank_sort(int *input, int size, int start, int end, int *result) {
  for(int i = start; i < end; i++) {
    int value = input[i];
    int rank = compute_rank(input, size, value);

    result[rank] = value;
  }
}


long long timeToMilliseconds(struct timeval tv) {
  return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

long long diffTime(struct timeval start, struct timeval stop)
{
  return timeToMilliseconds(stop) - timeToMilliseconds(start);
}

#endif //PARALLEL_SORT_H
