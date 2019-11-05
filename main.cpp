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

const string DATA_TAG1 = "CS361A2DATA_1:";
const string DATA_TAG2 = "CS361A2DATA_2:";
const string DATA_TAG3 = "CS361A2DATA_3:";

int main(int argc, char *argv[]) {
    int flags = 0;
    string settingstag = "";

    if (argc > 1) {
        std::string s = argv[1];
        std::stringstream ss(s);
        ss >> flags;

        cout << "Using flags " << flags << endl;

        settingstag.append("flag");
        settingstag.append(std::to_string(flags));
    }

    bool run = true, run_test = false;
    bool mix = false;
    std:
    string option = "";

    if (argc > 2) {
        std::string type = argv[2];
        option += (argc > 3) ? argv[3] : "-1";

        run_test = type.compare("test") == 0;
        mix = option.compare("mix") == 0;

        run = !run_test;

        cout << "Running type " << type << " " << option << endl;
        settingstag.append("opt");
        settingstag.append(option);
    }

    if (run) {
        int doThis;
        std::stringstream sso(option);
        sso >> doThis;

        std::string line1, line2;
        getline(cin, line1);
        getline(cin, line2);

        settingstag.append(" ");
        settingstag.append(line1);//.substr(0, line1.size()-1);

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

        if (!(flags & 8) || (flags & 1024)) {
            pad_length = max(pad_count(minin), pad_count(maxin));
        }

        if ((flags & 8)) {
            cout << "Run list:" << endl;
            printArray(run_list, n, ", ", 10);
            cout << endl;
        }

        t_sort test[n];

        int reps = (flags & 2) ? 5 : 1;

        if (flags & 4) reps = (reps + 1) / 2;

        if (flags & 16) reps = 1;

        vector<long> times[N_SORTS];

        for (int rep = 0; rep < reps; ++rep) {
            if (!(flags & 32)) {
                for (int i = 0; i < N_SORTS; i++) {
                    if (doThis >= 0 && i != doThis) continue;
                    //cout << "rep: " << rep << " i: " << i << endl;
                    //std::copy(std::begin(run_list), std::end(run_list), std::begin(test));
                    memcpy(test, run_list, sizeof(t_sort) * n);

                    if ((flags & 1024) && i == 0) printArray(run_list, n, ", ", 10);

                    cout << "Running: " << NAME[i] << endl;

                    if (!(flags & 64)) {
                        if (!(flags & 16)) {
                            auto start = std::chrono::high_resolution_clock::now();
                            (*SORTS[i])(test, n); ///////////////////////////////////////////////count
                            auto stop = std::chrono::high_resolution_clock::now();

                            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

                            times[i].push_back(duration.count());

                            cout << "Finished in " << duration.count() << "us" << endl;

                            if (reps == 1) {
                                string pre = "";
                                string post = "";

                                pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                                post.append(",;").append(settingstag);
                                cout << pre << duration.count() << "us" << post << endl;
                            }
                        } else {
                            clearc();
                            //printc();
                            auto start = std::chrono::high_resolution_clock::now();
                            (*SORTS_C[i])(test, n); ///////////////////////////////////////////////count
                            auto stop = std::chrono::high_resolution_clock::now();

                            //std::chrono::nanoseconds
                            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

                            times[i].push_back(duration.count());

                            cout << "Finished in " << duration.count() << "us" << endl;

                            string pre = "";
                            string post = "";

                            pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                            post.append(",;").append(settingstag);

                            printch();
                            printc(pre, post);
                        }
                    } else {
                        if (!(flags & 16)) {
                            auto start = std::chrono::high_resolution_clock::now();
                            (*SORTS[i])(test, n); ///////////////////////////////////////////////count
                            auto stop = std::chrono::high_resolution_clock::now();

                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

                            times[i].push_back(duration.count());

                            cout << "Finished in " << duration.count() << "ns" << endl;

                            if (reps == 1) {
                                string pre = "";
                                string post = "";

                                pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                                post.append(",;").append(settingstag);
                                cout << pre << duration.count() << "ns" << post << endl;
                            }
                        } else {
                            clearc();
                            //printc();
                            auto start = std::chrono::high_resolution_clock::now();
                            (*SORTS_C[i])(test, n); ///////////////////////////////////////////////count
                            auto stop = std::chrono::high_resolution_clock::now();

                            //std::chrono::nanoseconds
                            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

                            times[i].push_back(duration.count());

                            cout << "Finished in " << duration.count() << "ns" << endl;

                            string pre = "";
                            string post = "";

                            pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                            post.append(",;").append(settingstag);

                            printch();
                            printc(pre, post);
                        }

                        //for(int j = 0; j < 100; j++) for (int i = 0; i < 10000; ++i);
                    }

                    if (flags & 1) printArray(test, n, " < ", 10);
                    cout << endl;
                } // sorts loop

            } else { // flag 32
                for (int i = 0; i < N_SORTS_I; i++) {
                    if (doThis >= 0 && i != doThis) continue;
                    //if (i == 0) continue;
                    //cout << "rep: " << rep << " i: " << i << endl;
                    //std::copy(std::begin(run_list), std::end(run_list), std::begin(test));
                    memcpy(test, run_list, sizeof(t_sort) * n);

                    cout << "Running: " << NAME_I[i] << endl;

                    if (!(flags & 64)) {
                        auto start = std::chrono::high_resolution_clock::now();
                        (*SORTS_I[i])(test, n); ///////////////////////////////////////////////count
                        auto stop = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

                        times[i].push_back(duration.count());

                        cout << "Finished in " << duration.count() << "us" << endl;

                        if (reps == 1) {
                            string pre = "";
                            string post = "";

                            pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                            post.append(",;").append(settingstag);
                            cout << pre << duration.count() << "us" << post << endl;
                        }
                    }
                    else {
                        auto start = std::chrono::high_resolution_clock::now();
                        (*SORTS_I[i])(test, n); ///////////////////////////////////////////////count
                        auto stop = std::chrono::high_resolution_clock::now();

                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

                        times[i].push_back(duration.count());

                        cout << "Finished in " << duration.count() << "ns" << endl;

                        if (reps == 1) {
                            string pre = "";
                            string post = "";

                            pre.append(DATA_TAG3).append(",").append(NAME[i]).append(",").append(std::to_string(n)).append(",");
                            post.append(",;").append(settingstag);
                            cout << pre << duration.count() << "ns" << post << endl;
                        }

                        //for(int j = 0; j < 100; j++) for (int i = 0; i < 10000; ++i);
                    }

                    if (flags & 1) printArray(test, n, " < ", 10);
                    cout << endl;
                } // sorts_I loop
            }
            //for (int i = 0; i < 100000; ++i);
        } // reps loop

        if (reps > 1) {
            string data = "";
            if (!(flags & 32)) {
                data.append(DATA_TAG1);
                if (!(flags & 64)) {
                    for (int i = 0; i < N_SORTS; i++) {
                        if (doThis >= 0 && i != doThis) continue;
                        sort(times[i].begin(), times[i].end(), greater<>());
                        cout << "Median time for: " << NAME[i] << " is " << times[i][reps / 2] << "us" << endl;
                        data.append(",");
                        data.append(std::to_string(times[i][reps / 2]));
                        data.append("us");
                    }
                } else {
                    for (int i = 0; i < N_SORTS; i++) {
                        if (doThis >= 0 && i != doThis) continue;
                        sort(times[i].begin(), times[i].end(), greater<>());
                        cout << "Median time for: " << NAME[i] << " is " << times[i][reps / 2] << "ns" << endl;
                        data.append(",");
                        data.append(std::to_string(times[i][reps / 2]));
                        data.append("ns");
                    }
                }
            }
            else {
                data.append(DATA_TAG2);
                if (!(flags & 64)) {
                    for (int i = 0; i < N_SORTS_I; i++) {
                        if (doThis >= 0 && i != doThis) continue;
                        sort(times[i].begin(), times[i].end(), greater<>());
                        cout << "Median time for: " << NAME_I[i] << " is " << times[i][reps / 2] << "us" << endl;
                        data.append(",");
                        data.append(std::to_string(times[i][reps / 2]));
                        data.append("us");
                    }
                } else {
                    for (int i = 0; i < N_SORTS_I; i++) {
                        if (doThis >= 0 && i != doThis) continue;
                        sort(times[i].begin(), times[i].end(), greater<>());
                        cout << "Median time for: " << NAME_I[i] << " is " << times[i][reps / 2] << "ns" << endl;
                        data.append(",");
                        data.append(std::to_string(times[i][reps / 2]));
                        data.append("ns");
                    }
                }
            }
            cout << data << ",;" << settingstag << endl;
            //cout.flush();
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

            auto start = std::chrono::high_resolution_clock::now();
            (*SORTS[i])(test, test_n);
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            cout << "Finished in " << duration.count() << "us" << endl;

            printArray(test, test_n, " < ", 5);
            cout << endl;
        }

        for (int i = 0; i < N_SORTS_I; i++) {
            t_sort test[test_n];
            fillTest(test, mix);

            if (i == 0) {
                cout << "Testing list:" << endl;
                printArray(test, test_n, ",  ", 5);
                cout << endl;
            }

            cout << "Testing: " << NAME_I[i] << endl;


            auto start = std::chrono::high_resolution_clock::now();
            (*SORTS_I[i])(test, test_n); ///////////////////////////////////////////////count
            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            cout << "Finished in " << duration.count() << "us" << endl;

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