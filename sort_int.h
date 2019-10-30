//
// Created by allan on 2019-10-29.
//

#include "sort_algorithms_int.h"

#ifndef CS361A2_SORT_H
#define CS361A2_SORT_H

typedef void (*sort)(int[], int);

const int N_SORTS = 6;
const sort SORTS[N_SORTS] = {&insertionSort, &selectionSort,
                             &mergeSort, &quicksort, &heapSort, &IBubbleSort};
enum SORT {
    INSERTION = 0, SELECTION, MERGE, QUICK, HEAP, BUBBLE = 5
};
const string NAME[N_SORTS] = {"Insertion-Sort", "Selection-Sort", "Merge-Sort", "Quick-Sort",
                              "Heap-Sort", "Bubble-Sort"};

#endif //CS361A2_SORT_H
