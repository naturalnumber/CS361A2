//
//
//

#include <iostream>

using namespace std;

#ifndef CS361A2_SORTS_H
#define CS361A2_SORTS_H

typedef std::pair<int,int> SDATA;

// Helper methods

inline void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

inline void swap(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

inline int parent(int i) {
    return (i - 1) / 2;
}

inline int left(int i) {
    return 2 * i + 1;
}

inline int right(int i) {
    return 2 * i + 2;
}

//Insertion-Sort

void insertionSort(int A[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

//Selection-Sort
void selectionSort(int A[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (A[j] < A[min])
                min = j;
        swap(A, i, min);
    }
}

//Merge-Sort
void merge(int A[], int l, int m, int r) {
    int merged[r - l + 1];
    int i, j, k;
    i = l;
    j = m + 1;
    k = 0;
    while (i <= m && j <= r)
        if (A[i] <= A[j]) { //!
            merged[k] = A[i];
            k++;
            i++;
        } else {
            merged[k] = A[j];
            k++;
            j++;
        }
    while (i <= m) {
        merged[k] = A[i];
        i++;
        k++;
    }
    while (j <= r) {
        merged[k] = A[j];
        j++;
        k++;
    }
    for (i = l; i <= r; i++) A[i] = merged[i - l];
}

void mergeSort(int A[], int first, int last) {
    int middle;
    middle = (first + last) / 2;
    if (first < last) {
        mergeSort(A, first, middle);
        mergeSort(A, middle + 1, last);
        merge(A, first, middle, last);
    }
}

void mergeSort(int A[], int n) {
    mergeSort(A, 0, n-1); //!*
}

//Quick-Sort(dumb)

int partition(int A[], int first, int last) {
    int i, j, pivot;
    pivot = A[first];
    i = first;
    for (j = first + 1; j <= last; j++)
        if (A[j] < pivot) {
            i++;
            swap(A, i, j); //!*
        }
    swap(A, first, i);
    return i;
}

void quicksort(int A[], int first, int last) {
    if (first < last) {
        int middle = partition(A, first, last);
        quicksort(A, first, middle - 1);
        quicksort(A, middle + 1, last);
    }
}

void quicksort(int A[], int n) {
    quicksort(A, 0, n-1); //!*
}

//Heap-Sort
void heapify(int A[], int i, int n) {
    int l, r, largest;
    l = left(i);
    r = right(i);
    if (l < n && A[l] > A[i]) //!
        largest = l;
    else
        largest = i;
    if (r < n && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        swap(A, i, largest);
        heapify(A, largest, n);
    }
}

inline void buildHeap(int A[], int n) {
    for (int i = n / 2; i >= 0; i--) //!*
        heapify(A, i, n);
}

void heapSort(int A[], int n) {
    buildHeap(A, n); //!
    for (int i = n - 1; i >= 1; i--) {
        swap(A, 0, i);
        heapify(A, 0, i);
    }
}

// Bubble-Sorts

void BubbleSort1(int A[], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = n - 1; j > i; j--)
            if (A[j] < A[j - 1]) swap(A, j, j - 1);
}

void BubbleSort2(int A[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (A[j + 1] < A[j]) swap(A, j, j + 1);
}

//Bubble-Sort(improved)?
void IBubbleSort(int A[], int n) {
    int j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n; j++) {
            if (A[j] < A[j - 1]) {
                swap(A, j, j - 1);
                swapped = true;
            }
        }
    }
}

void BetterBubbleSort(int A[], int n) {
    int i = 0, j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n - i; j++) {
            if (A[j] < A[j - 1]) {
                swap(A, j, j - 1);
                swapped = true;
            }
        }
        i++;
    }
}

#endif //CS361A2_SORTS_H