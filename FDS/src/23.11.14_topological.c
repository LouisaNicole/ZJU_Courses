/*这题是一个有向图的入度构建，用于判断topological排序*/
#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    // getchar();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */
bool IsTopSeq(LGraph Graph, Vertex Seq[]) {
    int queue[Graph->Nv], i;
    for (i = 0; i < Graph->Nv; i++) {
        queue[i] = 0;
    }
    for (i = 0; i < Graph->Nv; i++) {
        PtrToAdjVNode p = Graph->G[i].FirstEdge;
        while (p != NULL) {
            queue[p->AdjV]++;
            p = p->Next;
        }
    }
    for (int i = 0; i < Graph->Nv; i++) {
        if (queue[Seq[i] - 1] == 0) {   // 入度为0
            PtrToAdjVNode q = Graph->G[Seq[i] - 1].FirstEdge;
            while (q != NULL) {               // 子入度-1
                queue[q->AdjV]--;
                q = q->Next;
            }
        } else {
            return false;
        }
    }
    return true;
}

LGraph ReadG() {
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);  // 读取顶点数和边数
    // getchar(); // 清除换行符

    // 创建图
    LGraph graph = (LGraph) malloc(sizeof(struct GNode));
    graph->Nv = Nv;
    graph->Ne = Ne;

    // 初始化邻接表
    for (int i = 0; i < Nv; i++) {
        graph->G[i].FirstEdge = NULL;
    }

    // 读取边的信息并构建邻接表
    for (int i = 0; i < Ne; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);  // 读取边的起点和终点
        // getchar(); // 清除换行符

        // 创建新的邻接点
        PtrToAdjVNode newNode = (PtrToAdjVNode) malloc(sizeof(struct AdjVNode));
        newNode->AdjV = v2-1;
        newNode->Next = NULL;

        // 将新的邻接点插入到起点的邻接表中
        PtrToAdjVNode current = graph->G[v1-1].FirstEdge;
        if (current == NULL) {
            // 如果邻接表为空，直接插入作为第一个节点
            graph->G[v1-1].FirstEdge = newNode;
        } else {
            // 否则找到邻接表的末尾插入新节点
            while (current->Next != NULL) {
                current = current->Next;
            }
            current->Next = newNode;
        }
    }

    return graph;
}