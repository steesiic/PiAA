#pragma once

#include <vector>
using namespace std;

struct Edge
{
    int to; //indeks suseda
    int weight; 
};
class Graph
{
public:
    int V;
    vector<vector<Edge>> adj;

    Graph(int V);

    void addEdge(int u, int v, int w);

    static Graph generateCase1(int N, int k);
    static Graph generateCase2(int N, int k);
};

