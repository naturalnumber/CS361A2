#include <iostream>
//#include "sort_int.h"
#include "sort.h"

using namespace std;

const int test1[20] = {12, 11, 13, 5, 6,
                 7, 10, 7, 8, 9,
                 1, 5, 64, 34, 25,
                 12, 22, 11, 90, 2};
const int test2[20] = {12, 22, 11, 90, 2,
                 12, 11, 13, 5, 6,
                 7, 10, 7, 8, 9,
                 1, 5, 64, 34, 25};
const int test_n = 20;

void fillTest(t_sort A[]) {
    for (int i = 0; i < test_n; ++i) {
        A[i] = std::make_pair(test1[i], test2[i]);
    }
}

int main() {

    for (int i = 0; i < N_SORTS; i++) {
        t_sort test[test_n];
        fillTest(test);

        cout << "Testing: " << NAME[i] << endl;

        (*SORTS[i])(test, test_n);

        printArray(test, test_n, " < ", 5);
    }

    return 0;
}


/*
int test_int() {

    for (int i = 0; i < N_SORTS; i++) {
        int test[20] = {12, 11, 13, 5, 6,
                        7, 10, 7, 8, 9,
                        1, 5, 64, 34, 25,
                        12, 22, 11, 90, 2};

        cout << "Testing: " << NAME[i] << endl;

        (*SORTS[i])(test, 20);

        printArray(test, 20);
    }

    return 0;
}//*/