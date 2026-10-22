#include "Prim.h"

int Prim::spanningTree(const Graph& g)
{
    int totalWeight = 0;
    vector<bool> visited(g.V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> edgeQueue;
    edgeQueue.push({ 0,0 });

    while (!edgeQueue.empty())
    {
        int u = edgeQueue.top().second;
        int wt = edgeQueue.top().first;
        edgeQueue.pop();

        if (visited[u]) 
            continue;

        visited[u] = true;
        totalWeight += wt;

        for (Edge e : g.adj[u])
            if (!visited[e.to])
                edgeQueue.push({ e.weight, e.to });  //grana tezine e vodi do cvora (e.to)
    }

    return totalWeight;
}
