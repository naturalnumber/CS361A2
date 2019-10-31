//
// Created by allan on 2019-10-29.
//

#include "sort_algorithms.h"

#ifndef CS361A2_SORT_H
#define CS361A2_SORT_H

typedef void (*sort_function)(t_sort[], int);

const int N_SORTS = 6;
const sort_function SORTS[N_SORTS] = {&insertionSort, &selectionSort,
                                      &mergeSort, &quicksort, &heapSort, &IBubbleSort};
const sort_function SORTS_C[N_SORTS] = {&insertionSort_c, &selectionSort_c,
                                      &mergeSort_c, &quicksort_c, &heapSort_c, &IBubbleSort_c};
enum SORT {
    INSERTION = 0, SELECTION, MERGE, QUICK, HEAP, BUBBLE = 5
};
const string NAME[N_SORTS] = {"Insertion-Sort", "Selection-Sort", "Merge-Sort", "Quick-Sort",
                              "Heap-Sort", "Bubble-Sort"};

#endif //CS361A2_SORT_H
