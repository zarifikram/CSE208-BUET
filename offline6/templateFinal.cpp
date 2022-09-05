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
    vector<vector<double> > KindOfBellmanFord(vector<vector<double> > distance, vector<vector<double> > weight);
    double BFSHelperForMFEdmondsKarp(int source, int destination, vector< vector<double> > &residualMatrix);
    vector<int> MinCut(int nTeams, int source, int destination, vector< vector<double> > &residualMatrix);


public:
	Graph(int V);
	void addEdge(int u, int v, double weight);
    vector<int> getTopologicalSortedList();

    void unvisit();
    void printGraph();
    vector<int> getIndegrees();
    vector<int> getOutdegrees();
    // This function traverses the graph using BFS and prints the 
    // the vertices
    void BFS(int s);
    bool isBipartite(int src);
    // prints DFS traversal of the complete graph
    void DFS();
	// Function that returns reverse (or transpose) of this graph
    bool hasCycle();
	Graph getTranspose();

    void SSSPDijkstra(int source, int destination);
    void SSSPBellmanFord(int source, int destination);
    void getMSTPrim();
    void getMSTKruskal();
    void APSPFloyedWarshall();
    void APSPPseudoMatrixMultiplication();
    vector<int> MFEdmondsKarp(int nTeams, int source, int destination);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<ii>[V];
    visited.assign(V, UNEXPLORED);
    inDegrees.assign(V, 0);
    outDegrees.assign(V, 0);
}



Graph Graph::getTranspose()
{
	Graph g(V);
	for (int u = 0; u < V; u++)
	{
		// Recur for all the vertices adjacent to this vertex
		for(ii v : adj[u])
		{
			g.adj[v.first].push_back(ii(u, v.second));
		}
	}
	return g;
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

void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    unvisit();
 
    // Create a queue for BFS
    queue<int> bfs_queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    bfs_queue.push(s);
 
    while(!bfs_queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = bfs_queue.front();
        cout << s << " ";
        bfs_queue.pop();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (ii adjecent: adj[s])
        {
            if (!visited[adjecent.first])
            {
                visited[adjecent.first] = true;
                bfs_queue.push(adjecent.first);
            }
        }
    }

}

void Graph::topologicalSortUtil(int vertex, vector<int>& topologicalSortedList){
    visited[vertex] = VISITED;
    for(ii nextVertex : adj[vertex]) if(visited[nextVertex.first] == UNEXPLORED){
        topologicalSortUtil(nextVertex.first, topologicalSortedList);
    }
    
    topologicalSortedList.push_back(vertex);
}

vector<int> Graph::getTopologicalSortedList(){
    vector<int> topologicalSortedList;
    unvisit();

    for(int i = 0; i < V; i++){
        if(visited[i] == UNEXPLORED) topologicalSortUtil(i, topologicalSortedList);
    }

    return topologicalSortedList;
    
}

void Graph::DFSUtil(int v)
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent to this vertex
    for (ii i : adj[v])
        if (!visited[i.first])
            DFSUtil(i.first);
}
 
// The function to do DFS traversal. It uses recursive
// DFSUtil()
void Graph::DFS()
{
    unvisit();
    // Call the recursive helper function to print DFS
    // traversal starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            DFSUtil(i);
}

void Graph::printGraph(){
    for(int i = 0; i < V; i++){
        cout << i << "--->";
        for(ii v : adj[i]) cout << v.first << " " << v.second;
        cout << endl;
    }
}


bool Graph::hasCycle(){
    unvisit();
    vector<int> dfsParent(V, 0);
    for(int i = 0; i < V; i++){
        if(visited[i] == UNEXPLORED and hasCycleUtil(i, dfsParent)) return true;
    }
    return false;
}

bool Graph::hasCycleUtil(int vertex, vector<int>& dfsParent){
    bool isCyclic = false;
    visited[vertex] = EXPLORED;
    for(ii nextVertex : adj[vertex]){
        if(visited[nextVertex.first] == UNEXPLORED) {
            dfsParent[nextVertex.first] = vertex;
            isCyclic = isCyclic | hasCycleUtil(nextVertex.first, dfsParent);
        }
        else if(visited[nextVertex.first] == EXPLORED and dfsParent[vertex] != nextVertex.first) {
            isCyclic |= true;
        }
    }
    visited[vertex] = VISITED;
    return isCyclic;
}

bool Graph::isBipartite(int src){
    vector<int> colors(V, -1);
    
    colors[src] = 1;
    queue <int> q;
    q.push(src);

    while(q.size()){
        int u = q.front();
        q.pop();

        for(ii v : adj[u]){
            if(v.first == u) return false;
            if(colors[v.first] == -1){
                colors[v.first] = 1 - colors[u];
                q.push(v.first);
            }
            else if(colors[v.first] == colors[u]) return false;
        }
    }

    return true;
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

void Graph::getMSTKruskal(){
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

    cout << "Cost of the minimum spanning tree : " << mst_cost << endl;
    cout << "List of edges selected by Kruskal's:{";
    for(int i = 0; i < parent.size(); i++) if(parent[i] != -1) cout << '(' << parent[i] << "," << i << ')' << (i == parent.size() - 1 ? "}\n" : ",");
}   

void Graph::SSSPDijkstra(int source, int destination){
    vector<double> distance(V, 1e9);
    vector< int > parent(V, -1);

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

    cout << "Shortest Path Cost: " << distance[destination] << endl;

    stack<int> path;
    for(int u = destination; u != source; u = parent[u]) path.push(u);
    path.push(source);
    while(path.size()){
        cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
        path.pop();
    }

}

void Graph::SSSPBellmanFord(int source, int destination){
    vector<double> distance(V, 1e9);
    vector< int > parent(V, -1);

    distance[source] = 0;
    for(int i = 0; i < V - 1; i++){
        for(int u = 0; u < V; u++){
            for(ii neighbor : adj[u]){
                if(distance[neighbor.first] > distance[u] + neighbor.second){
                    distance[neighbor.first] = distance[u] + neighbor.second;
                    parent[neighbor.first] = u;
                }
            }
        }
    }


    // Checking negative cycles
    for(int u = 0; u < V; u++){
        for(ii neighbor : adj[u]){
            if(distance[neighbor.first] > distance[u] + neighbor.second){
                // only possible if negative cycles occur
                cout << "The graph contains a negative cycle" << endl;
                return;
            }
        }
    }
    
    cout << "The graph does not contain a negative cycle" << endl;

    cout << "Shortest Path Cost: " << distance[destination] << endl;
    stack<int> path;
    for(int u = destination; u != source; u = parent[u]) path.push(u);
    path.push(source);
    while(path.size()){
        cout << path.top() << (path.size() == 1 ? "\n" : " -> ");
        path.pop();
    }
}
int source, dest;
void Graph::APSPFloyedWarshall(){
    double distance[V][V];

    int parent[V][V];

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++){
            parent[i][j] = i;
        }

    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++) distance[i][j] = (i == j ? 0 : 1e9);

    for(int i = 0; i < V; i++){
        for(ii vertex : adj[i]){
            distance[i][vertex.first] = vertex.second;
        }
    }

    for(int k = 0; k < V; k++)
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                if(distance[i][j] > distance[i][k] + distance[k][j]){
                    parent[i][j] = parent[k][j];
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
    cout << "Shortest Distance Matrix" << endl;           
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << distance[i][j] << " ";
        }
        cout << endl;
    }

    // Uncomment for path printing
    // stack<int> path;
    
    // for(int i = dest; i != source; i = parent[source][i]) {path.push(i);}
    // path.push(source);
    // while(path.size()) {
    //     cout << path.top() + 1 << "->";
    //     path.pop();
    // }
}

vector<vector<double> >Graph::KindOfBellmanFord(vector<vector<double> > distance, vector<vector<double> > weight){
    // double** distanceNew;
    // distanceNew = new double*[V];
    // for(int i = 0; i < V; i++) distanceNew[V] = new double[V];
    vector<vector<double> > distanceNew;
    distanceNew.assign(V, vector<double>());

    for(int i = 0; i < V; i++){
        distanceNew[i].assign(V, 1e9);
        for(int j = 0; j < V; j++){
            for(int k = 0; k < V; k++) distanceNew[i][j] = min(distanceNew[i][j], distance[i][k] + weight[k][j]);
        } 
    }
    return distanceNew;
}
void Graph::APSPPseudoMatrixMultiplication(){
    vector< vector<double> >distance;
    distance.assign(V, vector<double>());

    for(int i = 0; i < V; i++){
        distance[i].assign(V, 1e9);
        distance[i][i] = 0;
        for(ii vertex : adj[i]){
            distance[i][vertex.first] = vertex.second;
        }
    }
    
    int it = 1;

    while(it < V){
       
        distance = KindOfBellmanFord(distance, distance);
        it *= 2;
    }

    cout << "Shortest Distance Matrix" << endl;           
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << distance[i][j] << " ";
        }
        cout << endl;
    }
    
}

double Graph::BFSHelperForMFEdmondsKarp(int source, int destination, vector< vector<double> > &residualMatrix){
    // Mark all the vertices as not visited
    unvisit();
 
    // Create a queue for BFS
    queue<int> bfs_queue;
 
    // Mark the current node as visited and enqueue it
    visited[source] = true;
    bfs_queue.push(source);

    // we need parent vector to find out path (also for finding bottleneck)
    vector<int> parent(V, -1);

    while(!bfs_queue.empty())
    {
        // Dequeue a vertex from queue 
        int queueFront = bfs_queue.front();
        bfs_queue.pop();
        // cout << queueFront << endl;
        // if dest is found we are done
        if(queueFront == destination) break;

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (ii adjecent: adj[queueFront])
        {
            if (!visited[adjecent.first] and residualMatrix[queueFront][adjecent.first] > 0)
            {
                visited[adjecent.first] = true;
                bfs_queue.push(adjecent.first);
                parent[adjecent.first] = queueFront;
            }
        }
    }

    // need to make sure if destination is found. If not, return Infinity
    if(visited[destination] == false) return 1e9;

    // Find the bottleneck
    double bottleneckValue = 1e9;
    for(int u = destination; u != source; u = parent[u]){
        bottleneckValue = min(bottleneckValue, residualMatrix[parent[u]][u]);
        // cout << u << " ";
    }
    // cout << endl;

    // update the residualMatrix
    for(int u = destination; u != source; u = parent[u]){
        residualMatrix[parent[u]][u] -= bottleneckValue;
        residualMatrix[u][parent[u]] += bottleneckValue;
    }

    // for(int i = 0; i < V; i++){
    //     for(int j = 0; j < V; j++){
    //         cout << residualMatrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    return bottleneckValue;
}

vector<int> Graph::MFEdmondsKarp(int nTeams, int source, int destination){
    
// O(V^3E)
// 1. Create residual matrix from adj list
    vector< vector<double> > residualMatrix;
    residualMatrix.assign(V, vector<double>(V, 0));


    for(int i = 0; i < V; i++){
        for(ii neighbor : adj[i]){
            residualMatrix[i][neighbor.first] = neighbor.second;
            residualMatrix[neighbor.first][i] = neighbor.second;
        }
    }
   
    double maxFlox = 0;
// 2. Run bfs as long as source is reachable
// 2.1 Add bottleneck values to total value
    double bottleneck = BFSHelperForMFEdmondsKarp(source, destination, residualMatrix);

    while(bottleneck != 1e9) {
        maxFlox += bottleneck;
        // cout << bottleneck << endl;
        bottleneck = BFSHelperForMFEdmondsKarp(source, destination, residualMatrix);
        // cout << bottleneck << " bneck" << endl;
  
    }
    
    for(int i = 0; i < V; i++){
        if(residualMatrix[0][i] != 0) {
            return MinCut(nTeams, source, destination, residualMatrix);
        }
    }

    
    return vector<int>();
    // cout << maxFlox << endl;

    
}

vector<int> Graph::MinCut(int nTeams, int source, int destination, vector< vector<double> > &residualMatrix){
    vector<int> sourceComponent;

    unvisit();
    queue<int> bfs_queue;
 
    // Mark the current node as visited and enqueue it
    visited[source] = true;
    bfs_queue.push(source);

    while(!bfs_queue.empty())
    {
        // Dequeue a vertex from queue 
        int queueFront = bfs_queue.front();
        if(queueFront > nTeams * nTeams) sourceComponent.push_back(queueFront - nTeams * nTeams - 1);
        bfs_queue.pop();

        for (ii adjecent: adj[queueFront])
        {
            if (!visited[adjecent.first] and residualMatrix[queueFront][adjecent.first] > 0)
            {
                visited[adjecent.first] = true;
                bfs_queue.push(adjecent.first);
            }
        }
    }

    

    return sourceComponent;    
}
// Driver program to test above functions
int main()
{
    freopen("mf.in", "r", stdin);
    int nTeams;
    cin >> nTeams;

    string teamName;
    int win, lose, gamesRemaining;
    vector<int> wins;
    vector<int> loses;
    vector<int> gamesRemainings;
    vector<string> teamNames;
    int gamesRemainingAgainsts[nTeams][nTeams];



    int gamesRemainingAgainst;
    for(int i = 0; i < nTeams; i++){
        cin >> teamName >> win >> lose >> gamesRemaining;
        teamNames.push_back(teamName);
        wins.push_back(win);
        loses.push_back(lose);
        gamesRemainings.push_back(gamesRemaining);

        for(int j = 0; j < nTeams; j++){
            cin >> gamesRemainingAgainsts[i][j];
        }
    }

    int nGameCombinaitions = (nTeams) * (nTeams);
    int nNodes = 2 + nTeams + nGameCombinaitions;

    for(int teamConsidered = 0; teamConsidered < nTeams; teamConsidered++){
        Graph g(nNodes);

        // add source to match and match to teams
        
        for(int i = 0; i < nTeams; i++){
            if(i == teamConsidered) continue;
            for(int j = 0; j < nTeams; j++){
                if(j == teamConsidered) continue;
                int count = i * nTeams + j + 1;
                g.addEdge(0, count, gamesRemainingAgainsts[i][j]);
                g.addEdge(count, nGameCombinaitions + 1 + i, 1e9);
                g.addEdge(count, nGameCombinaitions + 1 + j, 1e9);
            }
            g.addEdge(nGameCombinaitions + 1 + i, nNodes - 1, wins[teamConsidered] + gamesRemainings[teamConsidered] - wins[i]);
        }
        vector<int> sourceComponent = g.MFEdmondsKarp(nTeams, 0, nNodes - 1);
        if(sourceComponent.size()){   
            cout << teamNames[teamConsidered] << " is eliminated" << endl; 
            cout << "They can win at most " << wins[teamConsidered] << " + " << gamesRemainings[teamConsidered]
                << " = " << wins[teamConsidered]  + gamesRemainings[teamConsidered] << " games." << endl;
            
            int totalWinOtherOpponents = 0;
            for(int x : sourceComponent) totalWinOtherOpponents += wins[x];

            for(int i = 0; i < sourceComponent.size(); i++){
                cout << teamNames[sourceComponent[i]] << ((i == sourceComponent.size() - 2) ? " and " : " ");
            }

            cout << "have won a total of " << totalWinOtherOpponents << " games." << endl;

            int totalGameBetween = 0;
            for(int i = 0; i < sourceComponent.size(); i++){
                for(int j = i + 1; j < sourceComponent.size(); j++){
                    totalGameBetween += gamesRemainingAgainsts[sourceComponent[i]][sourceComponent[j]];
                }
            }

            cout << "They play each other " << totalGameBetween << " times. " << endl;
            cout << "So, on average, each of the teams in this group wins " << totalWinOtherOpponents + totalGameBetween
                << "/" << sourceComponent.size() << " = " << (double)(totalWinOtherOpponents+totalGameBetween)/sourceComponent.size() << " games." << endl;;

            cout << endl;
        }
        else{
            cout << teamNames[teamConsidered] << " is not eliminated" << endl << endl;
        }
    }
}


