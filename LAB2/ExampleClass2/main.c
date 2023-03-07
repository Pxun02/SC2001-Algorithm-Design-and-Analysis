// Imports
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

// Data Structures
// ListNode data structure
typedef struct _listnode {
    int V;
    int w;
    struct _listnode* next;
} ListNode;

// Graph data structure
typedef struct _graph {
    int V;
    int E;
    ListNode** list;
    int** matrix;
} Graph;

// Queue data structure
typedef struct _pqueue {
    int* queue;
    int n;
} PQueue;

// Function Headers
// Function Headers - General graphing
Graph graphInit(int V, int E);
void autoPopulate(Graph* g);
void convertMtoL(Graph* g);
void printGraph(Graph* g);
// Function Headers - Matrix with array queue
void dijkstraMatrix(Graph* g, int source, int* d, int* pi);
int isMatrixQueueEmpty(int* queue, int n);
int extractCheapestMatrix(int* queue, int* priority, int n);
// Function Headers - List with minimising heap
void dijkstraList(Graph* g, int source, int* d, int* pi);
void heapify(PQueue* q, int i, int* d);
void minHeap(PQueue* q, int* d);
void swap(int* arr, int a, int b);
int extractCheapestList(PQueue* q, int* d);
// Function Headers - Results
void printShortestPath(int source, int* d, int *pi, Graph* g);
void drawGraph(int source, int* pi, int n, int depth);

int main() {

    // File operations
    FILE* fptr;
    if ((fptr = fopen("runs.txt", "r")) == NULL) {  // define the number of vertices and edges in runs.txt
        printf("ERROR: Unable to run program because file could not be opened for reading.\n");
        exit(1);
    }

    int V, E;

    // Iterations for every line
    while (fscanf(fptr, "%d %d", &V, &E) == 2) {

        // Setup graph
        Graph g = graphInit(V, E);
        autoPopulate(&g); // random

        // Source node - to change if needed
        int source = 1;  // index 0

        // d and pi arrays
        int* d = (int*)malloc(g.V*sizeof(int));
        int* pi = (int*)malloc(g.V*sizeof(int));

        // Dijkstra Algorithm - Matrix

        dijkstraMatrix(&g, source-1, d, pi);
        // printShortestPath(source-1, d, pi, &g);

        // Dijkstra Algorithm - List

        dijkstraList(&g, source-1, d, pi);
        // printShortestPath(source-1, d, pi, &g);

        // Cleanup
        free(g.list);
        free(g.matrix);
    }

    // For those running exe
    int exit;
    printf("Request for input so that the screen will not close when you use the exe, enter random NUMBER: ");
    scanf("%d", &exit);
    return 0;

}

Graph graphInit(int V, int E) {

    //Start of Init
    printf("Initialising graph...\n");

    // Declare graph
    Graph g;
    g.V = V;
    g.E = E;

    // Allocate space for list
    g.list = (ListNode**)malloc(V*sizeof(ListNode*));
    for (int i = 0; i < V; i++) {
        g.list[i] = NULL;
    }

    // Allocate space for matrix
    g.matrix = (int**)malloc(V*sizeof(int*));
    for (int i = 0; i < V; i++){
        g.matrix[i] = (int*)malloc(V*sizeof(int));
        for (int j = 0; j < V; j++)
            g.matrix[i][j] = 0;
    }

    // End of Init
    printf("Graph initialised.\n\n");
    return g;

}

void autoPopulate(Graph* g) {

    // Start of Pop
    printf("Populating graph...\n");

    // Pseudorandom
    srand(time(NULL));

    // Start from matrix
    for (int i = 1; i < g->V; i++) {
        (g->matrix)[0][i] = 1 + rand() % 20;  // Base to make sure graph is fully connected
    }

    int remainingE = g->E - (g->V - 1);
    for (int i = 0; i < remainingE; i++) {  // If there is remaining edges after creating the base, add random
        int a = 1 + rand() % (g->V - 1);
        int b = rand() % g->V;
        if (a == b || (g->matrix)[a][b] != 0) {  // No self-pointing edge, and no overwriting of edges
            i--;
            continue;
        }
        (g->matrix)[a][b] = 1 + rand() % 20;
    }

    // Convert matrix into list
    convertMtoL(g);

    // End of Pop
    printf("Graph populated.\n\n");
    // printGraph(g);

}

void convertMtoL(Graph* g) {

    // Conversion
    for (int i = 0; i < g->V; i++) {
        for (int j = 0; j < g->V; j++) {
            if ((g->matrix)[i][j] == 0) // if no such edge, skip
                continue;
            if ((g->list)[i] == NULL) { // if the vertice in the list has no edge yet
                (g->list)[i] = (ListNode*)malloc(sizeof(ListNode));
                (g->list)[i]->V = j;
                (g->list)[i]->w = (g->matrix)[i][j];
                (g->list)[i]->next = NULL;
            } else { // if the vertice in the list already has an edge
                ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
                temp->V = j;
                temp->w = (g->matrix)[i][j];
                temp->next = (g->list)[i];
                (g->list)[i] = temp;
            }
        }
    }

}

void printGraph(Graph* g) {

    // Start of print
    printf("-----MATRIX INFORMATION-----\n\n");

    // Basic information
    printf("Vertices => %d\nEdges => %d\n\n", g->V, g->E);

    // Matrix
    printf("Matrix:\n\n      ");

    for (int i = 0; i < g->V; i++)
        printf("%-2d ", i+1);
    printf("\n");

    for (int i = 0; i < g->V; i++) {
        printf("%-2d: [ ", i+1);
        for (int j = 0; j < g->V; j++)
            printf("%-2d ", g->matrix[i][j]);
        printf("]\n");
    }

    // List
    printf("\nList:\n\n");

    for (int i = 0; i < g->V; i++) {
        printf("%-2d: ", i+1);
        ListNode* cur = (g->list)[i];
        while (cur != NULL) {
            printf("[v=%d, w=%d], ", (cur->V)+1, cur->w);
            cur = cur->next;
        }
        printf("\n");
    }

    // End of print
    printf("\n----------------------------\n\n");

}

void dijkstraMatrix(Graph* g, int source, int* d, int* pi) {

    // Start of dijkstra
    printf("Performing Dijkstra's Algorithm (Matrix)...\n");

    // Initialise for local use
    int cur;
    int* S = (int*)malloc(g->V*sizeof(int));

    // Reset arrays
    for (int i = 0; i < g->V; i++) {
        d[i] = INT_MAX;
        pi[i] = -1;
        S[i] = 0;
    }

    d[source] = 0;  // The distance from source to source is definitely 0

    // start timer here
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    // Finding shortest path
    while(!isMatrixQueueEmpty(S, g->V)) {  // While there are still unexplored nodes
        cur = extractCheapestMatrix(S, d, g->V);  // Get shortest distance node
        S[cur] = 1;  // Explored

        for (int i = 0; i < g->V; i++) {  // Loop to find
            if ((g->matrix)[cur][i] != 0 && S[i] == 0) {  // Edges whose dest node not explored
                if (d[i] > (d[cur] + (g->matrix)[cur][i])) {  // If the distance is longer
                    d[i] = (d[cur] + (g->matrix)[cur][i]);  // Replace distance
                    pi[i] = cur;  // Replace previous index
                }
            }
        }
    }

    // end timer here
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("Time taken for Dijkstra (Matrix): %f seconds\n", elapsed);

    // End of dijkstra
    printf("Dijkstra is done.\n\n");

}

int isMatrixQueueEmpty(int* queue, int n) {

    // Go through queue array
    for (int i = 0; i < n; i++)
        if (queue[i] == 0)
            return 0; // queue still has something
    return 1; // queue empty

}

int extractCheapestMatrix(int* queue, int* priority, int n) {

    // Base values
    int min = -1;
    int index = 0;

    // Finding the next node with the smallest distance from previous node
    for (int i = 0; i < n; i++) {
        if (queue[i] == 1) // not in queue
            continue;
        if (min == -1 || (priority[i] < min)) {  // Minimum not set or smaller distance
            min = priority[i];  // Replace
            index = i;  // Replace
        }
    }

    // Return the node with smallest distance
    return index;

}

void dijkstraList(Graph* g, int source, int* d, int* pi) {

    // Start of dijkstra
    printf("Performing Dijkstra's Algorithm (List)...\n");

    // Initialise for local use
    int cur;
    ListNode* thisNode;
    int* S = (int*)malloc(g->V*sizeof(int));

    // Reset arrays
    for (int i = 0; i < g->V; i++) {
        d[i] = INT_MAX;
        pi[i] = -1;
        S[i] = 0;
    }

    d[source] = 0;  // The distance from source to source is definitely 0

    // Queue Setup
    PQueue q;
    q.queue = (int*)malloc(g->V*sizeof(int));
    q.n = g->V;

    for (int i = 0; i < g->V; i++) {
        q.queue[i] = i;
    }

    // start timer here
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    // Finding shortest path
    while(q.n != 0) {  // While there is still node in the queue
        cur = extractCheapestList(&q, d);  // Get the first
        S[cur] = 1;  // Explored
        thisNode = (g->list)[cur];  // Pointer to connected vertices

        while (thisNode != NULL) {  // while there is still connected v
            if (S[thisNode->V] == 0 && (d[thisNode->V] > d[cur] + thisNode->w)) {  // if node not explored, and current distance is longer
                d[thisNode->V] = d[cur] + thisNode->w;  // replace distance
                pi[thisNode->V] = cur;  // replace previous index
            }
            thisNode = thisNode->next;
        }
    }

    // end timer here
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    printf("Time taken for Dijkstra (List): %f seconds\n", elapsed);

    // End of dijkstra
    printf("Dijkstra is done.\n\n");

}

void heapify(PQueue* q, int i, int* d) {

    int smallest = i;  // assuming root is smallest
    int left = 2 * i + 1;  // left side
    int right = left + 1;  // right side

    if (left < q->n && d[(q->queue)[left]] < d[(q->queue)[smallest]]) {  // if there is a left node, and left is smaller than smallest
        smallest = left;
    }

    if (right < q->n && d[(q->queue)[right]] < d[(q->queue)[smallest]]) {  // if there is a right node, and right is smaller than smallest
        smallest = right;
    }

    if (smallest != i) { // if the smallest is not at the top of the triangle
        swap(q->queue, smallest, i);  // swap the smallest up
        heapify(q, smallest, d);  // heapify affected side
    }

}

void minHeap(PQueue* q, int* d) {

    // Create minimising heap
    for (int i = (q->n)/2 - 1; i >= 0; i--) {
        heapify(q, i, d);
    }

}

void swap(int* arr, int a, int b) {\

    // Swap
    int cur = arr[a];
    arr[a] = arr[b];
    arr[b] = cur;

}

int extractCheapestList(PQueue* q, int* d) {

    // Arrange in minimising heap
    minHeap(q, d);

    // Get cheapest
    int cheapest = (q->queue)[0];

    // Dequeue
    swap(q->queue, 0, (q->n)-1); // Move to back
    (q->n)--; // -1

    // Return
    return cheapest;

}

void printShortestPath(int source, int* d, int *pi, Graph* g) {

    // Start of print
    printf("------ SHORTEST PATH ------\n\n");

    // Print shortest path information
    printf("Source node => %d\n\n", source+1);
    printf("|From | To   | Distance\n-----------------------\n");

    for (int i = 0; i < g->V; i++)
        printf("|%-4d | %-4d | %-4d\n", source+1, i+1, d[i]);

    printf("\n");
    drawGraph(source, pi, g->V, 0);

    printf("\n---------------------------\n\n");

}

void drawGraph(int source, int* pi, int n, int depth) {

    // Visualise the connection of the nodes, parent -> child etc.
    if (depth == 0) { // base
        printf("%d\n", source+1);
        drawGraph(source, pi, n, depth+1);
    } else { // children
        for (int i = 0; i < n; i++) {
            if (i == source)
                continue;
            if (pi[i] == source) {
                for (int j = 1; j < depth; j++)
                    printf("  ");
                printf("|_%d\n", i+1);
                drawGraph(i, pi, n, depth+1); // check if more children
            }
        }
    }
}
