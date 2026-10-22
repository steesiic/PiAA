#include <iostream>
#include <chrono>
#include "Graph.h"
#include "Prim.h"

using namespace std;
using namespace chrono;

int main() 
{
    srand(time(NULL));

    vector<int> niz = {100, 1000, 10000, 100000};

   // for (int N : niz) 
    //{
          int N = 1000;
        vector<int> ks = {2*N, 5*N, 10*N, 20*N, 33*N, 50*N};

        for (int k : ks)
        {
            cout <<"\nN = " << N <<", k = "<< k << endl;

            Graph g1 = Graph::generateCase1(N, k);
            auto start1 = high_resolution_clock::now();
            Prim::spanningTree(g1);
            auto end1 = high_resolution_clock::now();
            cout << "Slucaj 1: "
                << duration_cast<milliseconds>(end1 - start1).count()
                << " ms" << endl;

            Graph g2 = Graph::generateCase2(N, k);
            auto start2 = high_resolution_clock::now();
            Prim::spanningTree(g2);
            auto end2 = high_resolution_clock::now();
            cout << "Slucaj 2: "
                << duration_cast<milliseconds>(end2 - start2).count()
                << " ms" << endl;
        }
   // }

    return 0;
}
