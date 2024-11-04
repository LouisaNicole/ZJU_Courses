#include "head.h"

int dist[MAX]; // Store distances from the source node
int _prev[MAX]; // Store the previous node in the shortest path
bool vis[MAX]; // Track visited nodes

Graph CreateGraph()
{
    Graph G = (Graph)malloc(sizeof(struct _graph));
    for (int i = 0; i < MAX; i++)
        G->adjMatrix[i] = nullptr;
    ifstream input("USA-road-d.CAL.gr");
    input >> G->VerNum >> G->EdgeNum;
    for (int i = 0; i < G->EdgeNum; i++)
    {
        int start, dest, distance;
        char c;
        input >> c >> start >> dest >> distance;
        AdjNodePtr left = new AdjNode();
        left->distance = distance;
        left->dest = dest;
        left->next = G->adjMatrix[start];
        G->adjMatrix[start] = left;
        AdjNodePtr right = new AdjNode();
        right->distance = distance;
        right->dest = start;
        right->next = G->adjMatrix[dest];
        G->adjMatrix[dest] = right;
    }
    input.close();
    return G;
}

void dijkstra(Heap *heap, Graph G, int st)
{
    heap->initial();
    heap->push(st, 0);
    while (!heap->empty())
    {
        pair<int, int> tmp;
        tmp = heap->top();
        heap->pop();
        // If the vertex is not visited
        if (!vis[tmp.first])
        {
            vis[tmp.first] = true; // Mark the vertex as visited
            dist[tmp.first] = tmp.second; // Update the distance to the vertex
            // Get the adjacency list of the vertex
            AdjNodePtr tmpNode = G->adjMatrix[tmp.first];
            // Iterate through the adjacency list
            while (tmpNode)
            {
                int d_tmp = tmpNode->distance + tmp.second; // Calculate the new distance
                // If the new distance is shorter than the current distance
                if (d_tmp < dist[tmpNode->dest])
                {
                    // Update the distance and previous vertex
                    dist[tmpNode->dest] = d_tmp;
                    _prev[tmpNode->dest] = tmp.first;
                    // Push the destination vertex with the new distance into the heap
                    heap->push(tmpNode->dest, dist[tmpNode->dest]);
                }
                tmpNode = tmpNode->next; // Move to the next adjacency node
            }
        }
    }
}
