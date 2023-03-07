#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> iPair;

static int comparisons = 0;

auto compare = [](iPair a, iPair b){
    return a.first < b.first;
};

void PushArray(vector<iPair>& vec, iPair element){
    int n = vec.size();
    if(n==0)
        vec.push_back(element);
    else{
        vector<iPair>::iterator it = upper_bound(vec.begin(), vec.end(), element, compare);
        vec.insert(it-1, element);
    }
    
}

void PopArray(vector<iPair>& vec){
    vec.erase(vec.begin());
}

class ArrayPriorityQueue{
    int size;
    vector<iPair> container;
    public:
        ArrayPriorityQueue();
        iPair top();
        void push(iPair element);
        void pop();
        bool empty();
};

ArrayPriorityQueue::ArrayPriorityQueue(){
    this->size = 0;
}

iPair ArrayPriorityQueue::top(){
    return this->container[0];
}

void ArrayPriorityQueue::push(iPair element){
    PushArray(this->container, element);
    size++;
}

void ArrayPriorityQueue::pop(){
    PopArray(this->container);
    size--;
}

bool ArrayPriorityQueue::empty(){
    return this->size == 0;
}


class Graph {
    int V;
    int** adj;
    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
};

Graph::Graph(int V){
    this->V = V;
    adj = new int*[V];
    for(int v=0;v<V;v++){
        adj[v] = new int[V];
        memset(adj[v], 0, sizeof(int));
    }
}

void Graph::addEdge(int u, int v, int w){
    adj[u][v] = w;
    adj[v][u] = w;
}

void Graph::shortestPath(int src){
    vector<int> dist(V, INF);
    ArrayPriorityQueue pq;

    pq.push(make_pair(src, 0));
    dist[src] = 0;

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for(int v=0;v<V;v++){
            if(adj[u][v]==0)   continue;
            int weight = adj[u][v];

            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << "Vertex Distance from Source" << endl;
    for(int i=0;i<V;i++)
        cout << i << " \t\t " << dist[i] << endl;
    
}

void makeGraph(Graph& g){
    //addEdge(ini, terminal, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
}

int main(){
    int V;
    cout << "Input the value of V: ";
    cin >> V;
    Graph g(V);
    makeGraph(g);
    g.shortestPath(0);
    cout << comparisons << " comparisons" << endl;
}