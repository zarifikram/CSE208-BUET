// C++ Implementation of graph ds
#include <iostream>
#include <vector>
#include <stack>
#include<queue>
using namespace std;

#define ii pair<int, double>
#define vi vector<int>
#define vii vector<ii>
#define UNEXPLORED 0
#define EXPLORED 1
#define VISITED 2

class UnionFind
{
private:
    vi p, rank;
    int numSets;

public:
    UnionFind(int N)
    {
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
        numSets = N;
    }
    void reset(int N)
    {
        rank.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        { // if from different set
            int x = findSet(i), y = findSet(j);
            numSets--;
            if (rank[x] > rank[y])
                p[y] = x; // rank keeps the tree short
            else
            {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};

class Graph
{
	int V; // No. of vertices
	vector<ii> *adj; // An array of adjacency lists
    vector<int> visited; 
    vector<int> inDegrees;
    vector<int> outDegrees;
	// Fills Stack with vertices (in increasing order of finishing
	// times). The top element of stack has the maximum finishing
	// time
	void fillOrder(int v, bool visited[], stack<int> &Stack); 
    void topologicalSortUtil(int vertex, vector<int>& topologicalSortedList);

	
     // A function used by DFS
    void DFSUtil(int v);
    bool hasCycleUtil(int vertex, vector<int>& dfsParent);
public:
	Graph(int V);
	void addEdge(int u, int v, double weight);


    void unvisit();
    void printGraph();
    vector<int> getIndegrees();
    vector<int> getOutdegrees();


    void SSSPDijkstra(int source, int destination);

};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<ii>[V];
    visited.assign(V, UNEXPLORED);
    inDegrees.assign(V, 0);
    outDegrees.assign(V, 0);
}




void Graph::addEdge(int u, int v, double weight = 0)
{
	adj[u].push_back(ii(v, weight)); // Add w to v’s list.
    inDegrees[v]++;
    outDegrees[u]++;

// uncomment for bidirecional graph
    // adj[v].push_back(ii(u, weight)); // Add w to v’s list.
    // inDegrees[u]++;
    // outDegrees[v]++;
}


void Graph::unvisit(){
    visited.assign(V, UNEXPLORED);
}

void Graph::SSSPDijkstra(int source, int destination){
    vector<double> distance(V, 0);
    vector< int > parent(V, -1);

    distance[source] = 1;
    priority_queue< pair <double, int>, vector < pair <double, int> > , greater < pair<double, int> > > dijkstraPQ;
    dijkstraPQ.push(ii(1, source));

    while(dijkstraPQ.size()){
        
        pair <double, int> currentVertex = dijkstraPQ.top();
        dijkstraPQ.pop();
        double w = currentVertex.first;
        int u = currentVertex.second;

        if(w < distance[u]) continue;
        

        for(ii nextVertex : adj[u]) if(distance[u] * nextVertex.second > distance[nextVertex.first]){
            distance[nextVertex.first] = distance[u] * nextVertex.second;

            parent[nextVertex.first] = u;
            dijkstraPQ.push(make_pair(distance[nextVertex.first], nextVertex.first));
        }
        
    }

    cout << "Shortest Path Cost: " << distance[destination] << endl;

    stack<int> path;
    for(int u = destination; u != source; u = parent[u]) path.push(u);
    path.push(source);
    while(path.size()){
        cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
        path.pop();
    }

}


// Driver program to test above functions
int main()
{
    freopen("sssp.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    Graph g(n);

    int u, v;
    double w;

    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    
    int source, destination;
    cin >> source >> destination;

    // g.SSSPBellmanFord(source, destination);
    g.SSSPDijkstra(source, destination);

}


