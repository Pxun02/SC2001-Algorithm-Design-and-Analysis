#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> iPair;
//{distance, v}

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
    int V;
    list<iPair>* adj;
    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
};

Graph::Graph(int V){
    this->V = V;
    adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int src){
    vector<int> dist(V, INF);
    HeapPriorityQueue pq;

    pq.push(make_pair(src, 0));
    dist[src] = 0;

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        list<iPair>::iterator it;
        for(it=adj[u].begin();it!=adj[u].end();it++){
            int v = (*it).first;
            int weight = (*it).second;

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
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    g.shortestPath(0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    cout << elapsed.count() << " seconds" << endl;
}