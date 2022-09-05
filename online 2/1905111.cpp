#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include<set>
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


public:
	Graph(int V);
	void addEdge(int u, int v, double weight);
    void unvisit();
    void printGraph();
    vector<pair<int, int> > getMSTKruskalEdges();
    void getMSTPrim();
    bool isConnected();
    void DFSUtil(int v);
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
    adj[v].push_back(ii(u, weight)); // Add w to v’s list.
    inDegrees[u]++;
    outDegrees[v]++;
}


void Graph::unvisit(){
    visited.assign(V, UNEXPLORED);
}


void Graph::printGraph(){
    for(int i = 0; i < V; i++){
        cout << i << "--->";
        for(ii v : adj[i]) cout << v.first << " " << v.second << "      ";
        cout << endl;
    }
}


void Graph::getMSTPrim(){
    unvisit();
    

    vi parent(V);
    priority_queue<pair<double, pair<int, int> >, vector<pair<double, pair<int, int> > >, greater<pair<double, pair<int, int> > > > mstHeap;

    Graph mst(V);
    
    for(ii v : adj[0]) mstHeap.push(make_pair(v.second, ii(0, v.first)));
    visited[0] = VISITED;

    int u, v;
    double w, mst_cost = 0;;

    while(mstHeap.size()){
        pair<double, ii > leastCostVertex = mstHeap.top();
        mstHeap.pop();

        w = leastCostVertex.first;
        u = leastCostVertex.second.first;
        v = leastCostVertex.second.second;
        
        if(!visited[v]){
            mst_cost += w;
            parent[v] = u;
            
            for(ii nextVertex : adj[v]) if(!visited[nextVertex.first]) mstHeap.push(make_pair(nextVertex.second, ii(v, nextVertex.first)));
            visited[v] = VISITED;
        }
    }

    cout << "Cost of the minimum spanning tree : " << mst_cost << endl;

    cout << "List of edges selected by Prim’s:{";
    for(int i = 1; i < parent.size(); i++) cout << '(' << parent[i] << "," << i << ')' << (i == parent.size() - 1 ? "}\n" : ",");
}

vector<pair<int, int> > Graph::getMSTKruskalEdges(){
    vector<pair<double, pair<int, int> > > edges;
    vi parent(V, -1);

    for(int u = 0; u < V; u++){
        for(ii nextVertex : adj[u]){
            edges.push_back(make_pair(nextVertex.second, ii(u, nextVertex.first)));
        }
    }
    
    double mst_cost = 0;

    sort(edges.begin(), edges.end());
    UnionFind UF(V);

    for(pair<double, ii> edge : edges){
        if(!UF.isSameSet(edge.second.first, edge.second.second)){
            mst_cost += edge.first;
            if(parent[edge.second.second] == -1) parent[edge.second.second] = edge.second.first;
            else parent[edge.second.first] = edge.second.second;
            UF.unionSet(edge.second.first, edge.second.second);
        }
    }

    // cout << "Cost of the minimum spanning tree : " << mst_cost << endl;
    // cout << "List of edges selected by Kruskal's:{";
    vector<pair<int, int> > mstEdges;
    for(int i = 0; i < parent.size(); i++) if(parent[i] != -1)  {

        if(i < parent[i]) mstEdges.push_back(ii(i, parent[i]));
        else mstEdges.push_back(ii( parent[i], i));
    }
    return mstEdges;
}   

void Graph::DFSUtil(int v)
{
    // Mark the current node as visited and print it
    visited[v] = true;

 
    // Recur for all the vertices adjacent to this vertex
    
    for (ii nextVertex : adj[v])
        if (!visited[nextVertex.first])
            DFSUtil(nextVertex.first);
}
 
// The function to do DFS traversal. It uses recursive
// DFSUtil()
bool Graph::isConnected()
{
    unvisit();
    // Call the recursive helper function to print DFS
    // traversal starting from all vertices one by one
    bool started = false;
    for (int i = 0; i < V; i++)
        if (visited[i] == false and started == false){
            started = true;
            DFSUtil(i);
        }
        else if(visited[i] == false and started == true)
            return false;
        
    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;
    Graph menRoads(n);
    Graph womenRoads(n);
    int u, v, roadType;
    for(int i = 0; i < m; i++){
        cin >> u >> v >> roadType;
        u--, v--;
        if(roadType == 3){
            menRoads.addEdge(u, v, 1);
            womenRoads.addEdge(u, v, 1);
        }
        else if(roadType == 2){
            womenRoads.addEdge(u, v, 10);
        }
        else if(roadType == 1){
            menRoads.addEdge(u, v, 10);
        }
    }

    if(menRoads.isConnected() and womenRoads.isConnected()){
        vector< pair<int, int> > menEdges = menRoads.getMSTKruskalEdges();
        vector< pair<int, int> > womenEdges = womenRoads.getMSTKruskalEdges();
    

        set< pair<int, int> > goodEdges;
        for (pair <int, int>  edge: menEdges){
            goodEdges.insert(edge);
        }


        for (pair <int, int> edge: womenEdges){
            goodEdges.insert(edge);
        }
        cout << m - goodEdges.size() << endl;
    }
    else cout << -1 << endl;


}


// 5 7
// 1 2 3
// 2 3 3
// 3 4 3
// 5 3 2
// 5 4 1
// 5 2 2
// 1 5 1