#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

#define INF 0x7fffffff  // Infinity
#define MAX 100000000  // Maximum value for certain operations

using namespace std;

typedef struct AdjNode
{
    int dest;             // Destination vertex
    int distance;         // Distance to the destination
    struct AdjNode *next; // Pointer to the next adjacent node
} *AdjNodePtr;

typedef struct _graph
{
    int VerNum;                 // Number of vertices
    int EdgeNum;                // Number of edges
    AdjNodePtr adjMatrix[MAX];  // Adjacency matrix
} *Graph;

typedef pair<int, int> GNode;   // Pair of (vertex, distance)

class Heap
{
public:
    virtual void initial() = 0;                      // Initialize the heap
    virtual void push(int vertex, int distance) = 0; // Insert a vertex with its distance into the heap
    virtual void pop() = 0;                          // Remove the minimum element from the heap
    virtual pair<int, int> top() = 0;                // Get the minimum element from the heap
    virtual bool empty() = 0;                        // Check if the heap is empty
};

Graph CreateGraph();                            // Create a new graph
void dijkstra(Heap *heap, Graph G, int st);     // Dijkstra's algorithm for finding shortest paths
