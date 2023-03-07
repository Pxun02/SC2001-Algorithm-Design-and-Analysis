#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
#include <queue>
#include <random>
#define INF 0x3f3f3f3f
using namespace std;


typedef pair<int, int> iPair;

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


void PopHeap(vector<iPair>& vec){
    int n = vec.size() - 1;
    vec[0] = vec[n];
    vec.pop_back();

    for(int i=0, j; (j = 2 * i + 1) < n;){
        if((j!=n-1) && (vec[j].first < vec[j+1].first)) j++;
        if(vec[i].first < vec[j].first){
            iPair tmp = vec[j];
            vec[j] = vec[i];
            vec[i] = tmp;
        }
        i = j;
    }
}
void PushHeap(vector<iPair>& vec, iPair element){
    int n = vec.size();
    vec.push_back(element);

    while(n!=0){
        int i = (n - 1) / 2;
        if(vec[n].first > vec[i].first){
            iPair tmp = vec[n];
            vec[n] = vec[i];
            vec[i] = tmp;
        }
        n = i;
    }
}

class HeapPriorityQueue{
    int size;
    vector<iPair> container;
    public:
        HeapPriorityQueue();
        iPair top();
        void push(iPair element);
        void pop();
        bool empty();
};

HeapPriorityQueue::HeapPriorityQueue(){
    size = 0;
}

iPair HeapPriorityQueue::top(){
    return container[0];
}

void HeapPriorityQueue::push(iPair element){
    PushHeap(this->container, element);
    size++;
}

void HeapPriorityQueue::pop(){
    PopHeap(this->container);
    size--;
}

bool HeapPriorityQueue::empty(){
    return size==0;
}


class Graph {
    public:
        int V;
        int** adj;
        list<iPair>* adjL;
        Graph(int V);
        ~Graph(){}
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
        void shortestPathL(int s);
};

Graph::Graph(int V){
    this->V = V;
    adj = new int*[V];
    adjL = new list<iPair>[V];
    for(int v=0;v<V;v++){
        adj[v] = new int[V];
        memset(adj[v], 0, sizeof(int));
    }
}

void Graph::addEdge(int u, int v, int w){
    adj[u][v] = w;
    adj[v][u] = w;
    adjL[u].push_back(make_pair(v, w));
    adjL[v].push_back(make_pair(u, w));
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
}

void Graph::shortestPathL(int src){
    vector<int> dist(V, INF);
    HeapPriorityQueue pq;

    pq.push(make_pair(src, 0));
    dist[src] = 0;

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        list<iPair>::iterator it;
        for(it=adjL[u].begin();it!=adjL[u].end();it++){
            int v = (*it).first;
            int weight = (*it).second;

            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void makeGraph(Graph& g, int E){
    //addEdge(ini, terminal, weight)
    for(int i = 1; i < g.V; i++) {
        g.addEdge(0, i, 1 + rand() % 20);  // Base to make sure graph is fully connected
    }

    //int remainingE = 1000*g.V - (g.V - 1);
    int remainingE = E - g.V;
    for (int i = 0; i < remainingE; i++) {  // If there is remaining edges after creating the base, add random
        int a = 1 + rand() % (g.V - 1);
        int b = rand() % g.V;
        if (a == b || g.adj[a][b] != 0) {  // No self-pointing edge, and no overwriting of edges
            i--;
            continue;
        }
        g.addEdge(a, b, 1 + rand() % 20);
    }
}

int main(){
    int V;
    cout << "Input the value of V: ";
    cin >> V;
    Graph g(V);
    int E = 10000;
    makeGraph(g, E);
    //(a)
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    g.shortestPath(0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    cout << "E: " << E << " ";
    cout << "matrix & array pq: " << elapsed.count() << " seconds" << endl;

    //(b)
    start = std::chrono::steady_clock::now();
    g.shortestPathL(0);
    end = std::chrono::steady_clock::now();
    elapsed = end-start;
    cout << "E: " << E << " ";
    cout << "list & heap pq: " << elapsed.count() << " seconds" << endl;
}