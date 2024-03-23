/*������һ������ͼ����ȹ����������ж�topological����*/
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
        if (queue[Seq[i] - 1] == 0) {   // ���Ϊ0
            PtrToAdjVNode q = Graph->G[Seq[i] - 1].FirstEdge;
            while (q != NULL) {               // �����-1
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
    scanf("%d %d", &Nv, &Ne);  // ��ȡ�������ͱ���
    // getchar(); // ������з�

    // ����ͼ
    LGraph graph = (LGraph) malloc(sizeof(struct GNode));
    graph->Nv = Nv;
    graph->Ne = Ne;

    // ��ʼ���ڽӱ�
    for (int i = 0; i < Nv; i++) {
        graph->G[i].FirstEdge = NULL;
    }

    // ��ȡ�ߵ���Ϣ�������ڽӱ�
    for (int i = 0; i < Ne; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);  // ��ȡ�ߵ������յ�
        // getchar(); // ������з�

        // �����µ��ڽӵ�
        PtrToAdjVNode newNode = (PtrToAdjVNode) malloc(sizeof(struct AdjVNode));
        newNode->AdjV = v2-1;
        newNode->Next = NULL;

        // ���µ��ڽӵ���뵽�����ڽӱ���
        PtrToAdjVNode current = graph->G[v1-1].FirstEdge;
        if (current == NULL) {
            // ����ڽӱ�Ϊ�գ�ֱ�Ӳ�����Ϊ��һ���ڵ�
            graph->G[v1-1].FirstEdge = newNode;
        } else {
            // �����ҵ��ڽӱ��ĩβ�����½ڵ�
            while (current->Next != NULL) {
                current = current->Next;
            }
            current->Next = newNode;
        }
    }

    return graph;
}