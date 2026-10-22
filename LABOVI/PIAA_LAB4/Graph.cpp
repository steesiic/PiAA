#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = vector<vector<Edge>>(V);
}

void Graph::addEdge(int u, int v, int w) //neusmeren
{
    adj[u].push_back({ v, w });
    adj[v].push_back({ u, w });
}

long long encodeEdge(int u, int v, int N)
{
    if (u > v)
        swap(u, v);

    return (long long)u * N + v;
}

//slucac1
Graph Graph::generateCase1(int N, int k)
{
    Graph g(N);
    unordered_set<long long> edges;

    int center = rand() % N;
    for (int i = 0; i < N; i++)
    {
        if (i == center)
            continue;

        int w = rand() % 100 + 1;
        g.addEdge(center, i, w);
        edges.insert(encodeEdge(center, i, N));
    }

    int maxExtra = N * (N - 1) / 2 - (N - 1);
    if (k > maxExtra)
        k = maxExtra;


    int added = 0;
    while (added < k)
    {
        int u = rand() % N;
        int v = rand() % N;
        if (u == v)
            continue;

        long long edgeId = encodeEdge(u, v, N);
        if (edges.count(edgeId))
            continue;

        int w = rand() % 100 + 1;
        g.addEdge(u, v, w);
        edges.insert(edgeId);
        added++;
    }

    return g;
}

//slucaj2
Graph Graph::generateCase2(int N, int k)
{
    Graph g(N);
    unordered_set<long long> edges;

    for (int i = 0; i < N - 1; i++)
    {
        int w = rand() % 100 + 1;
        g.addEdge(i, i + 1, w);
        edges.insert(encodeEdge(i, i + 1, N));
    }

    int maxExtra = N * (N - 1) / 2 - (N - 1);
    if (k > maxExtra)
        k = maxExtra;

    int added = 0;
    while (added < k)
    {
        int u = rand() % N;
        int v = rand() % N;
        if (u == v)
            continue;

        long long edgeId = encodeEdge(u, v, N);
        if (edges.count(edgeId))
            continue;

        int w = rand() % 100 + 1;
        g.addEdge(u, v, w);
        edges.insert(edgeId);
        added++;
    }

    return g;
}
