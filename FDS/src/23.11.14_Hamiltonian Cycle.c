#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 200 /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    int G_mat[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode LGraph;

LGraph ReadG();
int IsHamiltonian(LGraph Graph, int query[], int cnt);

int main()
{
    int i, j, K, cnt;
    LGraph G = ReadG();
    scanf("%d", &K);
    for(i=0; i<K; i++){
        scanf("%d", &cnt);
        int query[cnt];
        for(j=0; j<cnt; j++){
            scanf("%d", &query[j]);
        }
        if(IsHamiltonian(G, query, cnt)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

int IsHamiltonian(LGraph Graph, int query[], int cnt){
    int queue[Graph->Nv], i;
    if(Graph->Nv != cnt-1) return 0;                 //数量不对
    else if(query[0] != query[Graph->Nv]) return 0;  //没构成环
    else{
        for(i=0; i<Graph->Nv; i++){
            queue[i] = 0;                       //初始化每个节点都还没遇到
        }
        for(i=0; i<=Graph->Nv; i++){
            queue[query[i]-1]++;                //记录每个节点出现次数
        }

        for(i=0; i<Graph->Nv; i++){
            if(queue[i] == 0) return 0;         //有一个节点没出现过则不正确
        }
        //判断两个节点之间的边是否存在
        for(i=0; i<Graph->Nv; i++){
            if(Graph->G_mat[query[i]-1][query[i+1]-1] == 0) return 0;
        }
    }
    return 1;
}

LGraph ReadG() {
    int Nv, Ne, i, j;
    scanf("%d %d", &Nv, &Ne);  // 读取顶点数和边数

    LGraph graph = (LGraph)malloc(sizeof(struct GNode));
    graph->Nv = Nv;
    graph->Ne = Ne;

    for(i=0; i<Nv; i++) {
        for(j=0; j<Nv; j++) {
            graph->G_mat[i][j] = 0;
        }
    }

    for(i=0; i<Ne; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);  // 读取边的起点和终点
        graph->G_mat[v1-1][v2-1] = 1;
        graph->G_mat[v2-1][v1-1] = 1;
    }
    return graph;
}