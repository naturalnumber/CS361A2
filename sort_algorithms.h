//
//
//

#include <iostream>

using namespace std;

#ifndef CS361A2_SORTS_H
#define CS361A2_SORTS_H

typedef std::pair<int, int> t_sort;

const int pad_length = 2;

#define t_sort_print(i) "(" << pad(i.first, pad_length) << i.first << ", " << pad(i.second, pad_length) << i.second << ")"

// Helper methods

string pad(int i, int l) {
    string s = "";

    int il = 1;
    if (i < 0) {
        ++il;
        i = -i;
    }

    while (i >= 10) {
        ++il;
        i /= 10;
    }

    l -= il;

    for (int j = 0; j < l; ++j) s += " ";

    return s;
}

void printArray(t_sort A[], int n, string sep = ", ", int per = 0, string div = "\n") {
    for (int i = 0; i < n; ++i) {
        cout << t_sort_print(A[i]);
        if (i < n - 1) {
            cout << sep;
            if (per > 0 && (i % per) == (per - 1)) cout << div;
        }
    }
    cout << endl;
}

inline void swap(t_sort A[], int i, int j) {
    t_sort temp = A[i];
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

void insertionSort(t_sort A[], int n) {
    t_sort key;
    for (int j, i = 1; i < n; ++i) {
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
void selectionSort(t_sort A[], int n) {
    for (int min, j, i = 0; i < n - 1; ++i) {
        min = i;
        for (j = i + 1; j < n; ++j)
            if (A[j] < A[min])
                min = j;
        swap(A, i, min);
    }
}

//Merge-Sort
void merge(t_sort A[], int l, int m, int r) {
    t_sort merged[r - l + 1];
    int i = l, j = m + 1, k = 0;
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
    for (i = l; i <= r; ++i) A[i] = merged[i - l];
}

void mergeSort(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort(A, first, middle);
        mergeSort(A, middle + 1, last);
        merge(A, first, middle, last);
    }
}

void mergeSort(t_sort A[], int n) {
    mergeSort(A, 0, n - 1);
}

//Quick-Sort(dumb)

int partition(t_sort A[], int first, int last) {
    int i = first;
    t_sort pivot = A[first];
    for (int j = first + 1; j <= last; ++j)
        if (A[j] < pivot) {
            i++;
            swap(A, i, j); //!*
        }
    swap(A, first, i);
    return i;
}

void quicksort(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = partition(A, first, last);
        quicksort(A, first, middle - 1);
        quicksort(A, middle + 1, last);
    }
}

void quicksort(t_sort A[], int n) {
    quicksort(A, 0, n - 1);
}

//Heap-Sort
void heapify(t_sort A[], int i, int n) {
    int l = left(i), r = right(i), largest;
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

inline void buildHeap(t_sort A[], int n) {
    for (int i = n / 2; i >= 0; --i) heapify(A, i, n);
}

void heapSort(t_sort A[], int n) {
    buildHeap(A, n); //!
    for (int i = n - 1; i >= 1; --i) {
        swap(A, 0, i);
        heapify(A, 0, i);
    }
}

// Bubble-Sorts

void BubbleSort1(t_sort A[], int n) {
    for (int j, i = 0; i < n; ++i)
        for (j = n - 1; j > i; --j)
            if (A[j] < A[j - 1]) swap(A, j, j - 1);
}

void BubbleSort2(t_sort A[], int n) {
    for (int j, i = 0; i < n - 1; ++i)
        for (j = 0; j < n - 1 - i; ++j)
            if (A[j + 1] < A[j]) swap(A, j, j + 1);
}

//Bubble-Sort(improved)?
void IBubbleSort(t_sort A[], int n) {
    int j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n; ++j) {
            if (A[j] < A[j - 1]) {
                swap(A, j, j - 1);
                swapped = true;
            }
        }
    }
}

void BetterBubbleSort(t_sort A[], int n) {
    int i = 0, j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n - i; ++j) {
            if (A[j] < A[j - 1]) {
                swap(A, j, j - 1);
                swapped = true;
            }
        }
        ++i;
    }
}

#endif //CS361A2_SORTS_H