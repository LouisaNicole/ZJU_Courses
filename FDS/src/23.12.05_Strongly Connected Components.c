#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(){
    int numOfVertices, numOfEdges;
    scanf("%d %d", &numOfVertices, &numOfEdges);

    Graph G = (Graph)malloc(sizeof(struct GNode));
    G->NumOfVertices = numOfVertices;
    G->NumOfEdges = numOfEdges;
    G->Array = (PtrToVNode *)malloc(numOfVertices * sizeof(PtrToVNode));

    Vertex V;
    for (V = 0; V < numOfVertices; V++) {
        G->Array[V] = NULL;
    }

    for (int i = 0; i < numOfEdges; i++) {
        Vertex start, end;
        scanf("%d %d", &start, &end);

        PtrToVNode newNode = (PtrToVNode)malloc(sizeof(struct VNode));
        newNode->Vert = end;  // 新节点与当前顶点相连的顶点是end
        newNode->Next = G->Array[start]; // 当前顶点的邻接表的头部
        G->Array[start] = newNode;
    }

    return G;
}


void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    void DFS(int V, Graph G, int visited[], void (*visit)(Vertex V), int num[], int low[], int stack[], int stack_flag[], int *cnt, int *top);
    int visited[MaxVertices] = {0};
    int stack[MaxVertices], stack_flag[MaxVertices] = {0};
    int num[MaxVertices], low[MaxVertices];
    int V;
    int *cnt = (int*)malloc(sizeof(int));
    int *top = (int*)malloc(sizeof(int));
    *cnt = 0; *top = -1;
    for (V = 0; V < G->NumOfVertices; V++) {
        if (!visited[V]) {
            DFS(V, G, visited, visit, num, low, stack, stack_flag, cnt, top);
        }
    }
    free(top);
    free(cnt);
}

void DFS(int V, Graph G, int visited[], void (*visit)(Vertex V), int num[], int low[], int stack[], int stack_flag[], int *cnt, int *top)
{
    PtrToVNode temp_node;
    visited[V] = 1; stack_flag[V] = 1;
    num[V] = low[V] = (*cnt)++;
    stack[++(*top)] = V;
    for (temp_node = G->Array[V]; temp_node != NULL; temp_node = temp_node->Next) {
        if (!visited[temp_node->Vert]) {
            DFS(temp_node->Vert, G, visited, visit, num, low, stack, stack_flag, cnt, top);
            if (low[temp_node->Vert] < low[V]) low[V] = low[temp_node->Vert];
        }
        else if (stack_flag[temp_node->Vert]) { // 还未出栈 在本连通图内更新low[]
            if (num[temp_node->Vert] < low[V]) low[V] = num[temp_node->Vert];
        }
    }
    if (num[V] == low[V]) { // V是一个强连通分量的根节点
        do {
            visit(stack[*top]);
            stack_flag[stack[*top]] = 0;
        } while (stack[(*top)--] != V);
        printf("\n");
    }
}

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

