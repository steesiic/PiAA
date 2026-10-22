#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <cstdio> 
#include "BTree.h"

using namespace std;
using namespace std::chrono;

void runExperiment(int N, int M) 
{
    int t = (M + 1) / 2;
    if (t < 2) 
        t = 2;

    BTree tree(t);
    vector<int> Y;
    for (int i = 1; i <= N; ++i) 
        Y.push_back(i);

    random_device rd;
    mt19937 g(rd());
    shuffle(Y.begin(), Y.end(), g);


    auto startAdd = high_resolution_clock::now();
    for (int val : Y) 
        tree.insert(val);
    auto endAdd = high_resolution_clock::now();


    vector<int> toDelete = Y;
    shuffle(toDelete.begin(), toDelete.end(), g);
    int numDel = N / 10;
    auto startDel = high_resolution_clock::now();
    for (int i = 0; i < numDel; ++i) 
        tree.remove(toDelete[i]);
    auto endDel = high_resolution_clock::now();


    shuffle(Y.begin(), Y.end(), g);
    int X_limit = (3 * N) / 5;
    int found = 0;
    auto startSearch = high_resolution_clock::now();
    for (int i = 0; i < X_limit; ++i)
    {
        if (tree.contains(Y[i]))
        {
            found++;
        }
            
    }
    auto endSearch = high_resolution_clock::now();

    double timeAdd = duration_cast<nanoseconds>(endAdd - startAdd).count() / 1e9;
    double timeDel = duration_cast<nanoseconds>(endDel - startDel).count() / 1e9;
    double timeSearch = duration_cast<nanoseconds>(endSearch - startSearch).count() / 1e9;


    printf(" [%-8d] | M: %-4d | In: %.6fs | De: %.6fs | Se: %.6fs | Cmn: %-6d\n",
        N, M, timeAdd, timeDel, timeSearch, found);
}

int main() 
{
    int N_vals[] = { 100, 1000, 10000, 100000, 1000000 };
    int M_vals[] = { 3, 5, 10, 33, 101, 333, 1001 };

    printf("\n REZULTATI TESTIRANJA B-STABLA\n");
    printf(" %s\n", string(85, '=').c_str());
    printf(" %-10s | %-6s | %-12s | %-12s | %-12s | %-10s\n",
        "N-Elemen.", "Max_K", "T_Insert", "T_Delete", "T_Search", "Presek");
    printf(" %s\n", string(85, '-').c_str());

    for (int n : N_vals)
    {
        for (int m : M_vals) 
        {
            runExperiment(n, m);
        }
        printf(" %s\n", string(85, '.').c_str()); 
    }

    return 0;
}