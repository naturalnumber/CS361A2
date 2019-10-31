#include <iostream>
//#include <sstream>
#include <string>
#include <algorithm>
//#include <iterator>
#include<bits/stdc++.h>
#include <chrono>
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

void fillTest(t_sort A[], bool mix = false) {
    for (int i = 0; i < test_n; ++i)
        A[i] = std::make_pair((mix && (i / 2 % 2) ? -1 : 1) * test1[i], (mix && (i % 2) ? -1 : 1) * test2[i]);
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(int argc, char*argv[]) {
    int variation = 0;

    if (argc > 1) {
        std::string s = argv[1];
        std::stringstream ss(s);
        ss >> variation;

        cout << "Using variation " << variation << endl;
    }

    bool run = true, run_test = false;
    bool mix = false;

    if (argc > 2) {
        std::string type = argv[2], option = (argc > 3) ? argv[3] : "";

        run_test = type.compare("test") == 0;
        mix = option.compare("mix") == 0;

        run = !run_test;

        cout << "Running type " << type << " " << option << endl;
    }

    if (run) {
        std:
        string line1, line2;
        getline(cin, line1);
        getline(cin, line2);

        std::string prefix = "Array Length is ";
        std::string number = line2.substr(prefix.size());

        std::stringstream ss(number);

        int n;
        ss >> n;

        cout << "Reading " << n << " pairs";

        int per = n / 10, in1, in2, maxin = 0, minin = INT_MAX;
        char c;

        t_sort run_list[n];

        for (int i = 0; i < n; ++i) {
            cin.get(c);
            cin >> in1;
            cin.get(c);
            cin >> in2;
            cin.get(c);
            cin.get(c);
            run_list[i] = std::make_pair(in1, in2);
            if (i % per == per - 1) cout << '.';

            maxin = max(maxin, max(in1, in2));
            minin = min(minin, min(in1, in2));
        }
        cout << " done!" << endl;

        if (!(variation & 8) || (variation & 1024)) {
            pad_length = max(pad_count(minin), pad_count(maxin));
        }

        if (!(variation & 8)) {
            cout << "Run list:" << endl;
            printArray(run_list, n, ", ", 10);
            cout << endl;
        }

        t_sort test[n];

        int reps = (variation & 2) ? 5 : 1;

        if (variation & 4) reps = (reps + 1) / 2;

        if (variation & 16) reps = 1;

        vector<long> times[N_SORTS];

        for (int rep = 0; rep < reps; ++rep)
            for (int i = 0; i < N_SORTS; i++) {
                //cout << "rep: " << rep << " i: " << i << endl;
                //std::copy(std::begin(run_list), std::end(run_list), std::begin(test));
                memcpy(test, run_list, sizeof(t_sort)*n);

                if ((variation & 1024) && i == 0) printArray(run_list, n, ", ", 10);

                cout << "Running: " << NAME[i] << endl;

                if (!(variation & 16)) {
                    auto start = std::chrono::high_resolution_clock::now();
                    (*SORTS[i])(test, n); ///////////////////////////////////////////////count
                    auto stop = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                            stop - start);

                    times[i].push_back(duration.count());

                    cout << "Finished in " << duration.count() << "us" << endl;
                }
                else {
                    clearc();
                    //printc();
                    auto start = std::chrono::high_resolution_clock::now();
                    (*SORTS_C[i])(test, n); ///////////////////////////////////////////////count
                    auto stop = std::chrono::high_resolution_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

                    times[i].push_back(duration.count());

                    cout << "Finished in " << duration.count() << "us" << endl;

                    printch();
                    printc();
                }

                if (variation & 1) printArray(test, n, " < ", 10);
                cout << endl;
            }

        if (reps > 1)
            for (int i = 0; i < N_SORTS; i++) {
                sort(times[i].begin(), times[i].end(), greater <>());
                cout << "Median time for: " << NAME[i] << " is " << times[i][reps/2] << "us" << endl;
            }
    }
    if (run_test) {
        pad_length = 2 + mix;

        for (int i = 0; i < N_SORTS; i++) {
            t_sort test[test_n];
            fillTest(test, mix);

            if (i == 0) {
                cout << "Testing list:" << endl;
                printArray(test, test_n, ",  ", 5);
                cout << endl;
            }

            cout << "Testing: " << NAME[i] << endl;

            (*SORTS[i])(test, test_n);

            printArray(test, test_n, " < ", 5);
            cout << endl;
        }
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