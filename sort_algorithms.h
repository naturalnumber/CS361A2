//
//
//

#include <iostream>

using namespace std;

#ifndef CS361A2_SORTS_H
#define CS361A2_SORTS_H

typedef std::pair<int, int> t_sort;

int pad_length = 3;

#define t_sort_print(i) "(" << pad(i.first, pad_length) << i.first << ", " << pad(i.second, pad_length) << i.second << ")"

// Helper methods

inline string pad(int number, int length) {
    int i = number, j = length + ((number < 0) ? -2 : -1);
    while (i /= 10) --j;
    return (j > 0) ? std::string(j, ' ') : "";
}

inline int pad_count(int number) {
    int i = number, j = ((number < 0) ? 2 : 1);
    while (i /= 10) ++j;
    return j;
}

void printArray(t_sort A[], int n, string sep = ", ", int per = 0, string div = "\n") {
    for (int i = 0; i < n; ++i) {
        cout << t_sort_print(A[i]);
        if (i < n - 1) {
            cout << sep;
            if (per && (i % per) + 1 == per) cout << div;
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
            --j;
        }
        A[j + 1] = key;
    }
}

//Selection-Sort
void selectionSort(t_sort A[], int n) {
    for (int min, j, i = 0; i < n - 1; ++i) {
        min = i;
        for (j = i + 1; j < n; ++j)
            if (A[j] < A[min]) min = j;
        swap(A, i, min);
    }
}

//Merge-Sort
void merge(t_sort A[], int l, int m, int r) {
    t_sort merged[r - l + 1];
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) merged[k++] = (A[i] <= A[j]) ? A[i++] : A[j++];
    while (i <= m) merged[k++] = A[i++];
    while (j <= r) merged[k++] = A[j++];
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
        if (A[j] < pivot) swap(A, ++i, j);
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
    int l = left(i), r = right(i);
    int largest = (l < n && A[l] > A[i]) ? l : i;
    if (r < n && A[r] > A[largest]) largest = r;
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

// merge alt

void merge_(t_sort A[], int l, int m, int r) {
    t_sort merged[r - l + 1];
    int i = l, j = m + 1, k = 0;


    while (i <= m && j <= r) merged[k++] = (A[i] <= A[j]) ? A[i++] : A[j++];
    while (i <= m) merged[k++] = A[i++];
    while (j <= r) merged[k++] = A[j++];
    for (i = l; i <= r; ++i) A[i] = merged[i - l];
}

void mergeSort_(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort(A, first, middle);
        mergeSort(A, middle + 1, last);
        merge(A, first, middle, last);
    }
}

void mergeSort_(t_sort A[], int n) {
    mergeSort(A, 0, n - 1);
}


// radix~

#define PAIR_ULONG(p) ((ulong(long(p.first)+0x80000000) << 32 + p.second)+0x80000000)
#define PAIR_LONG(p) (((long(p.first)) << 32) + p.second)
#define RADIX_v 256
#define RADIX_pdiv(i, e) ( (e < 4) ? (e == 0) ? PAIR_LONG(i) : ((long(i.first) << ((4-e)*8)) | (i.second >> (e*8))) : (long(i.first) >> ((e-4)*8)) )
#define RADIX_div(i, e) ((i) >> (e*8))
#define RADIX_mod(i) ((i) & 0b11111111)
#define RADIX_pdivmod(i, e) ( (e < 4) ? RADIX_mod(long(i.second) >> (e*8)) : RADIX_mod(long(i.first) >> ((e-4)*8)) )
#define RADIX_divmod(i, e) RADIX_mod(RADIX_div(i, e))

t_sort max(t_sort A[], int n) {
    t_sort m = A[0];
    for (int i = 1; i < n; ++i)
        if (A[i] > m)
            m = A[i];
    return m;
}

void countSort(t_sort A[], int n, int e) {
    t_sort out[n];
    int i, count[RADIX_v] = { };

    for (i = 0; i < n; ++i) count[RADIX_divmod(PAIR_LONG(A[i]), e)]++;

    for (i = 1; i < RADIX_v; ++i) count[i] += count[i - 1];

    for (i = n - 1; i >= 0; --i) {
        out[count[RADIX_pdivmod((A[i]), e)] - 1] = A[i];
        count[RADIX_pdivmod((A[i]), e)]--;
    }

    for (i = 0; i < n; ++i) A[i] = out[i];
}

void radixSort(t_sort A[], int n) {
    long m = PAIR_LONG(max(A, n));

    for (int e = 0; RADIX_div(m, e) > 0; ++e) countSort(A, n, e);
}

void BetterBubbleSortB(list<t_sort> A) {
    if (A.size() < 2) return;
    bool swapped = true;
    std::list<t_sort>::iterator i = A.end(), j, prev;
    while (swapped) {
        swapped = false;
        prev = A.begin(), j = prev++;
        //cout << t_sort_print((*prev)) << " from " << t_sort_print((*j)) << " ... " << t_sort_print((*i)) << endl;
        for (; j != i; j++) {
            //cout << t_sort_print((*j)) << " ? " << t_sort_print((*prev)) << endl;
            if (*j < *prev) {
                //cout << t_sort_print((*j)) << " < " << t_sort_print((*prev)) << endl;
                std::iter_swap(j, prev);
                swapped = true;
            }
            //else cout << t_sort_print((*j)) << " > " << t_sort_print((*prev)) << endl;
            prev = j;
        }
        i = prev;
    }
}

void bucketSort(t_sort A[], int n) {
    long m = PAIR_LONG(max(A, n));

    //vector<t_sort> buckets[n];
    list<t_sort> buckets[n];

    long div = m / n + 1;

    int i;
    for (i=0; i<n; ++i) {
        int bucket = PAIR_LONG(A[i]) / div;
        buckets[bucket].push_back(A[i]);
    }

    for (i=0; i<n; ++i) buckets[i].sort(); //BetterBubbleSortB(buckets[i]); //

    int index = 0;
    for (i = 0; i < n; ++i) for (const t_sort & p : buckets[i]) A[index++] = p;
}

//Quick-Sort(alt)

inline t_sort swap_r(t_sort A[], int i, int j) {
    t_sort temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    return temp;
}

inline void shift_up(t_sort A[], int i, int j, int k) {
    t_sort temp = A[k];
    A[k] = A[j];
    A[j] = A[i];
    A[i] = temp;
}

inline t_sort shift_up_r(t_sort A[], int i, int j, int k) {
    t_sort temp = A[i];
    A[i] = A[k];
    A[k] = A[j];
    A[j] = temp;
    return temp;
}

inline t_sort split(t_sort A[], int i, int j, int k) {
    if (A[i] <= A[j]) { // i < j
        if (A[j] <= A[k]) { // i < j < k
            return A[j];
        }
        else { // k < j
            if (A[i] <= A[k]) { // i < k < j
                return swap_r(A, k, j);
            }
            else { // k < i < j
                return shift_up_r(A, i, j, k);
            }
        }
    }
    else { // j < i
        if (A[i] <= A[k]) { // j < i < k
            return swap_r(A, i, j);
        }
        else { // k < i
            if (A[j] <= A[k]) { // j < k < i
                return shift_up_r(A, k, i, j);
            }
            else { // k < j < i
                swap(A, k, i);
                return A[j];
            }
        }
    }
}

int partition_m_(t_sort A[], int first, int last) {
    int i = (first+last)/2, j;

    t_sort pivot = split(A, first, i, last);

    while (j < i && A[j] < pivot) ++j;

    if (j < i) {
        --last;
        shift_up(A, j, last, i);

        first = i = j++; //**********

        for (; j < last; ++j)
            if (A[j] < pivot) swap(A, i++, j);
        swap(A, first, i);
        return i;
    } else {
        first = i;
        for (++j; j < last; ++j)
            if (A[j] < pivot) swap(A, i++, j);
        swap(A, first, i);
        return i;
    }
}

void quicksort_m_(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = partition_m_(A, first, last);
        quicksort_m_(A, first, middle - 1);
        quicksort_m_(A, middle + 1, last);
    }
}

void quicksort_m_(t_sort A[], int n) {
    quicksort_m_(A, 0, n - 1);
}

int partition_m(t_sort A[], int first, int last) {
    int i = first;
    swap(A, i, (first + last)/2);
    t_sort pivot = A[i];
    for (int j = first + 1; j <= last; ++j)
        if (A[j] < pivot) swap(A, ++i, j);
    swap(A, first, i);
    return i;
}

void quicksort_m(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = partition_m(A, first, last);
        quicksort_m(A, first, middle - 1);
        quicksort_m(A, middle + 1, last);
    }
}

void quicksort_m(t_sort A[], int n) {
    quicksort_m(A, 0, n - 1);
}

int partition_h(t_sort A[], int first, int last) {
    int i = last;
    t_sort pivot = A[last];
    for (int j = last-1; j >= first; --j)
        if (A[j] < pivot) swap(A, --i, j);
    swap(A, last, i);
    return i;

/*
    int i = first;
    t_sort pivot = A[last];
    for (int j = first; j < last; ++j)
        if (A[j] < pivot) swap(A, i++, j);
    swap(A, last, i);
    return i; //*///***************************************
}

void quicksort_h(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = partition_h(A, first, last);
        quicksort_h(A, first, middle - 1);
        quicksort_h(A, middle + 1, last);
    }
}

void quicksort_h(t_sort A[], int n) {
    quicksort_m(A, 0, n - 1);
}


// ***** Counting versions

const int c_n = 24;

union count_{
    ulong data[24] = { };
    struct {
        ulong add, sub, mlt, div, mod, inc, dec, ass;
        ulong and_, or_;
        ulong comp, tern, comp_b;
        ulong if_, loop;
        ulong call, rtrn, pass;
        ulong declr, ref, declr_b, declr_p;
        ulong arr, arl;
    };
} c;

void printc(string prefix = "", string sufix = "") {
    cout << prefix <<
            c.add << "," << c.sub << "," << c.mlt << "," << c.div << "," <<
            c.mod << "," << c.inc << "," << c.dec << "," << c.ass << "," <<
            c.and_ << "," << c.or_ << "," <<
            c.comp << "," << c.tern << "," << c.comp_b << "," <<
            c.if_ << "," << c.loop << "," <<
            c.call << "," << c.rtrn << "," << c.pass << "," <<
            c.declr << "," << c.ref << "," << c.declr_b << "," << c.declr_p << "," <<
            c.arr << "," << c.arl << sufix << endl;
}

void printch(string prefix = "", string sufix = "") {
    cout << prefix <<
         "additions" << "," << "subtractions" << "," << "multiplications" << "," << "divisions" << "," <<
         "modulos" << "," << "increments" << "," << "decrements" << "," << "assignments" << "," <<
         "ands" << "," << "ors" << "," <<
         "comparissons" << "," << "ternaries" << "," << "boolean_checks" << "," <<
         "ifs" << "," << "loops" << "," <<
         "calls" << "," << "returns" << "," << "passed_words" << "," <<
         "declarations_integer" << "," << "array_references" << "," << "declarations_boolean" << "," << "declarations_points" << "," <<
         "declarations_array" << "," << "declarations_array_length" << sufix << endl;
}

void clearc() {
    c.add = 0; c.sub = 0; c.mlt = 0; c.div = 0;
    c.mod = 0; c.inc = 0; c.dec = 0; c.ass = 0;
    c.and_ = 0; c.or_ = 0;
    c.comp = 0; c.tern = 0; c.comp_b = 0;
    c.if_ = 0; c.loop = 0;
    c.call = 0; c.rtrn = 0; c.pass = 0;
    c.declr = 0; c.ref = 0; c.declr_b = 0; c.declr_p = 0;
    c.arr = 0; c.arl = 0;
}


// Helper methods

inline void swap_c(t_sort A[], int i, int j) {
    t_sort temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    c.declr_p++;
    c.ass += 3;
    c.ref += 4;
}

inline int parent_c(int i) {
    c.sub++;
    c.div++;
    return (i - 1) / 2;
}

inline int left_c(int i) {
    c.mlt++;
    c.add++;
    return 2 * i + 1;
}

inline int right_c(int i) {
    c.mlt++;
    c.add++;
    return 2 * i + 2;
}

//Insertion-Sort

void insertionSort_c(t_sort A[], int n) {
    t_sort key;
    for (int j, i = 1; i < n; ++i) {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            --j;

            c.comp += 2;
            c.and_++;
            c.ass++;
            c.ref += 3;
            c.add++;
            c.dec++;
            c.loop++;
        }
        A[j + 1] = key;

        c.comp += 3;
        c.and_++;
        c.inc++;
        c.ass += 3;
        c.ref += 3;
        c.add++;
        c.sub++;
        c.loop += 2;
    }

    c.call++;
    c.declr += 2;
    c.declr_p++;
    c.comp++;
    c.loop++;
    c.pass += 2;
}

//Selection-Sort
void selectionSort_c(t_sort A[], int n) {
    for (int min, j, i = 0; i < n - 1; ++i) {
        min = i;
        for (j = i + 1; j < n; ++j) {
            if (A[j] < A[min]) {
                min = j;
                c.ass++;
            }

            c.comp += 2;
            c.ref += 2;
            c.inc++;
            c.if_++;
            c.loop++;
        }
        swap_c(A, i, min);

        c.comp += 2;
        c.inc++;
        c.add++;
        c.ass += 2;
        c.loop += 2;
    }

    c.call++;
    c.declr += 3;
    c.ass++;
    c.comp++;
    c.sub++; //assuming compiler is sensible
    c.loop++;
    c.pass += 2;
}

//Merge-Sort
void merge_c(t_sort A[], int l, int m, int r) {
    t_sort merged[r - l + 1];
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        merged[k++] = (A[i] <= A[j]) ? A[i++] : A[j++];

        c.loop++;
        c.comp += 3;
        c.and_++;
        c.ass++;
        c.ref += 4;
        c.tern++;
        c.inc += 2;
    }
    while (i <= m) {
        merged[k++] = A[i++];

        c.loop++;
        c.comp++;
        c.inc += 2;
        c.ref += 2;
        c.ass++;
    }
    while (j <= r) {
        merged[k++] = A[j++];

        c.loop++;
        c.comp++;
        c.inc += 2;
        c.ref += 2;
        c.ass++;
    }
    for (i = l; i <= r; ++i) {
        A[i] = merged[i - l];

        c.loop++;
        c.comp++;
        c.inc += 2;
        c.ref++;
        c.ass++;
        c.sub++;
    }

    c.call++;
    c.declr += 3;
    c.sub++;
    c.add += 2;
    c.ass += 4;
    c.arr++;
    c.arl += r - l + 1;
    c.loop += 4;
    c.comp += 5;
    c.and_++;
    c.pass += 4;
}

void mergeSort_c(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort_c(A, first, middle);
        mergeSort_c(A, middle + 1, last);
        merge_c(A, first, middle, last);

        c.declr++;
        c.add += 2;
        c.div++;
        c.ass++;
    }

    c.call++;
    c.if_++;
    c.comp++;
    c.pass += 3;
}

void mergeSort_c(t_sort A[], int n) {
    mergeSort_c(A, 0, n - 1);
}

//Quick-Sort(dumb)

int partition_c(t_sort A[], int first, int last) {
    int i = first;
    t_sort pivot = A[first];
    for (int j = first + 1; j <= last; ++j) {
        if (A[j] < pivot) {
            swap_c(A, ++i, j);

            c.inc++;
        }

        c.loop++;
        c.comp += 2;
        c.if_++;
        c.inc++;
        c.ref++;
    }
    swap_c(A, first, i);

    c.call++;
    c.rtrn++;
    c.declr += 2;
    c.declr_p++;
    c.ass += 3;
    c.ref++;
    c.add++;
    c.loop++;
    c.comp++;
    c.pass += 3;

    return i;
}

void quicksort_c(t_sort A[], int first, int last) {
    if (first < last) {
        int middle = partition_c(A, first, last);
        quicksort_c(A, first, middle - 1);
        quicksort_c(A, middle + 1, last);

        c.declr++;
        c.add++;
        c.sub++;
    }

    c.call++;
    c.if_++;
    c.comp++;
    c.pass += 3;
}

void quicksort_c(t_sort A[], int n) {
    quicksort_c(A, 0, n - 1);
}

//Heap-Sort
void heapify_c(t_sort A[], int i, int n) {
    int l = left_c(i), r = right_c(i);
    int largest = (l < n && A[l] > A[i]) ? l : i;
    if (r < n && A[r] > A[largest]) {
        largest = r;

        c.ass++;
    }
    if (largest != i) {
        swap_c(A, i, largest);
        heapify_c(A, largest, n);
    }

    c.call++;
    c.declr += 3;
    c.ass += 3;
    c.tern++;
    c.comp += 5;
    c.if_ += 2;
    c.and_ += 2;
    c.ref += 4;
    c.pass += 3;
}

inline void buildHeap_c(t_sort A[], int n) {
    for (int i = n / 2; i >= 0; --i) {
        heapify_c(A, i, n);

        c.loop++;
        c.comp++;
        c.dec++;
    }

    c.declr++;
    c.ass++;
    c.div++;
    c.comp++;
    c.loop++;
}

void heapSort_c(t_sort A[], int n) {
    buildHeap_c(A, n); //!
    for (int i = n - 1; i >= 1; --i) {
        swap_c(A, 0, i);
        heapify_c(A, 0, i);

        c.loop++;
        c.comp++;
        c.dec++;
    }

    c.call++;
    c.loop++;
    c.comp++;
    c.declr++;
    c.ass++;
    c.sub++;
    c.pass += 2;
}

// Bubble-Sorts

void BubbleSort1_(t_sort A[], int n) {
    for (int j, i = 0; i < n; ++i)
        for (j = n - 1; j > i; --j)
            if (A[j] < A[j - 1]) swap_c(A, j, j - 1);
}

void BubbleSort2_(t_sort A[], int n) {
    for (int j, i = 0; i < n - 1; ++i)
        for (j = 0; j < n - 1 - i; ++j)
            if (A[j + 1] < A[j]) swap_c(A, j, j + 1);
}

//Bubble-Sort(improved)?
void IBubbleSort_c(t_sort A[], int n) {
    int j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n; ++j) {
            if (A[j] < A[j - 1]) {
                swap_c(A, j, j - 1);
                swapped = true;

                c.sub++;
                c.ass++;
            }

            c.loop++;
            c.comp++;
            c.inc++;
            c.if_++;
            c.ref += 2;
            c.sub++;
        }

        c.loop += 2;
        c.ass += 2;
        c.comp++;
        c.comp_b++;
    }

    c.call++;
    c.declr++;
    c.declr_b++;
    c.ass++;
    c.loop++;
    c.comp_b++;
    c.pass += 2;
}

void BetterBubbleSort_(t_sort A[], int n) {
    int i = 0, j;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (j = 1; j < n - i; ++j) {
            if (A[j] < A[j - 1]) {
                swap_c(A, j, j - 1);
                swapped = true;
            }
        }
        ++i;
    }
}

#endif //CS361A2_SORTS_H