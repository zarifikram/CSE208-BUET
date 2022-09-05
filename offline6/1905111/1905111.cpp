#include <iostream>
#include "BinomialHeap.h"
#include "FibonacciHeap.h"
#include <stack>
#include <vector>
#include <chrono>
#include <queue>

#define ii pair<int, int>
#define ll long long int;
using namespace std;

int V, m;
vector<ii> adj[100005];
int pathLength, pathCost;

int SSSPDijkstra0(int source, int destination)
{
    auto start = chrono::steady_clock::now();
    vector<double> distance(V, 1e9);
    vector<int> parent(V, -1);

    distance[source] = 0;

    priority_queue< pair <double, int>, vector < pair <double, int> > , greater < pair<double, int> > > dijkstraPQ;
    dijkstraPQ.push(ii(0, source));

    while(dijkstraPQ.size()){
        pair <double, int> currentVertex = dijkstraPQ.top();
        dijkstraPQ.pop();
        double w = currentVertex.first;
        int u = currentVertex.second;

        if(w > distance[u]) continue;

        for(ii nextVertex : adj[u]) if(distance[u] + nextVertex.second < distance[nextVertex.first]){
            distance[nextVertex.first] = distance[u] + nextVertex.second;
            parent[nextVertex.first] = u;
            dijkstraPQ.push(ii(distance[nextVertex.first], nextVertex.first));
        }
    }

    // cout << "Shortest Path Cost: " << distance[destination] << endl;
    pathCost = distance[destination];
    stack<int> path;
    for (int u = destination; u != source; u = parent[u])
        path.push(u);
    path.push(source);
    pathLength = path.size();
    // while (path.size())
    // {
    //     cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
    //     path.pop();
    // }
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int SSSPDijkstra1(int source, int destination)
{
    auto start = chrono::steady_clock::now();
    vector<double> distance(V, 1e9);
    vector<int> parent(V, -1);

    distance[source] = 0;

    BinomialHeap<pair<int, int> > dijkstraPQ;

    dijkstraPQ.insert(ii(0, source));

    while (dijkstraPQ.isEmpty() == false)
    {
        pair<int, int> currentVertex = dijkstraPQ.extractMin()->key;

        double w = currentVertex.first;
        int u = currentVertex.second;

        if (w > distance[u])
            continue;

        for (ii nextVertex : adj[u])
            if (distance[u] + nextVertex.second < distance[nextVertex.first])
            {
                distance[nextVertex.first] = distance[u] + nextVertex.second;
                parent[nextVertex.first] = u;
                dijkstraPQ.insert(ii(distance[nextVertex.first], nextVertex.first));
            }
    }

    // cout << "Shortest Path Cost: " << distance[destination] << endl;
    pathCost = distance[destination];
    stack<int> path;
    for (int u = destination; u != source; u = parent[u])
        path.push(u);
    path.push(source);
    pathLength = path.size();
    // while (path.size())
    // {
    //     cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
    //     path.pop();
    // }
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int SSSPDijkstra2(int source, int destination)
{
    auto start = chrono::steady_clock::now();
    vector<double> distance(V, 1e9);
    vector<int> parent(V, -1);

    distance[source] = 0;

    FibonacciHeap<pair<int, int> > dijkstraPQ;

    dijkstraPQ.insert(ii(0, source));

    while (dijkstraPQ.isEmpty() == false)
    {
        pair<int, int> currentVertex = dijkstraPQ.extractMin()->key;

        double w = currentVertex.first;
        int u = currentVertex.second;

        if (w > distance[u])
            continue;

        for (ii nextVertex : adj[u])
            if (distance[u] + nextVertex.second < distance[nextVertex.first])
            {
                distance[nextVertex.first] = distance[u] + nextVertex.second;
                parent[nextVertex.first] = u;
                dijkstraPQ.insert(ii(distance[nextVertex.first], nextVertex.first));
            }
    }

    // cout << "Shortest Path Cost: " << distance[destination] << endl;
    pathCost = distance[destination];
    stack<int> path;
    for (int u = destination; u != source; u = parent[u])
        path.push(u);
    path.push(source);
    pathLength = path.size();
    // while (path.size())
    // {
    //     cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
    //     path.pop();
    // }

    

    auto end = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int main()
{

    freopen("input.in", "r", stdin);
    cin >> V >> m;

    for (size_t i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back(ii(y, w));
        adj[y].push_back(ii(x, w));
    }

    int nInputs;
    cin >> nInputs;
    while (nInputs--)
    {
        int fro, to;
        cin >> fro >> to;

        int timeForBinaryHeap = SSSPDijkstra0(fro, to);
        int timeForBinomialHeap = SSSPDijkstra1(fro, to);
        int timeForFibonacciHeap = SSSPDijkstra2(fro, to);
        cout << pathLength - 1 << " " << pathCost << " " << timeForBinaryHeap << " " << timeForBinomialHeap << " " << timeForFibonacciHeap << endl;
    }
}