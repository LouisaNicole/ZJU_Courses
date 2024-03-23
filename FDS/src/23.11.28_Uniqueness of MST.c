#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_V 500  

typedef struct GNode {  
	int Nv;                  
	int Ne;                 
	int G[Max_V][Max_V]; 
}*PtrToGNode;
typedef PtrToGNode RGraph;

void IsMST(RGraph Graph, int* mst_weight, int* component, int*unique);   
RGraph ReadG();                           

int main() {
    RGraph Graph = ReadG();
    int mst_weight = 0, component = 1, unique = 1;
    IsMST(Graph, &mst_weight, &component, &unique);
    if (mst_weight == -1) {
        printf("No MST\n");
        printf("%d\n", component);
    }
    else {
        printf("%d\n", mst_weight);
        if (unique) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}

RGraph ReadG() {
    int Nv, Ne, i, j;
    scanf("%d %d", &Nv, &Ne); 
    RGraph graph = (RGraph)malloc(sizeof(struct GNode));
    graph->Nv = Nv;
    graph->Ne = Ne;

    for (i=0; i<Nv; i++) {
        for(j=0; j<Nv; j++) {
            graph->G[i][j] = 0; 
        }
    }
    for (i=0; i<Ne; i++) {
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);  
        graph->G[v1-1][v2-1] = weight;
        graph->G[v2-1][v1-1] = weight;
    }
    return graph;
}

void IsMST(RGraph Graph, int* mst_weight, int* component, int* unique) {
    int dist = 1000000;         
    int i, j;
    int distance[Max_V];           // 各顶点的最小边长度
    int visit[Max_V] = {0};        // 标记是否已访问
    int cnt[Max_V];                // 路径数量
    memset(distance, 1000000, sizeof(distance));
    distance[0] = 0;               // 第一个点是距离为0
    cnt[0] = 1;

    for (i = 0; i < Graph->Nv; i++) {
        int u = -1, v, min_dist = dist;
        for (j = 0; j < Graph->Nv; j++) {
            if (!visit[j] && distance[j] < min_dist) {  // 找到的最小距离的边并记录这个节点Prim算法
                min_dist = distance[j]; 
                u = j;
            }
        }
        if (min_dist == dist) { // 不连通无法构成最小生成树
            *mst_weight = -1;
            break;
        }
        visit[u] = 1;           // 标记源节点已访问
        *mst_weight += distance[u];
        for (v = 0; v < Graph->Nv; v++) {
            if (!visit[v] && Graph->G[u][v] != 0) {
                if (Graph->G[u][v] < distance[v]) {
                    distance[v] = Graph->G[u][v];  // 更新节点的最短边长度
                    cnt[v] = cnt[u];
                }
                else if (Graph->G[u][v] == distance[v]) {
                    cnt[v] += cnt[u];
                }
            }
        }
    }
    for (i = 0; i < Graph->Nv; i++) {
        if (!visit[i]) {
            (*component)++;
            visit[i] = 1;    // 遍历连通分量
        }
    }
    for (i = 0; i < Graph->Nv; i++) {
        if (cnt[i] != 1) { // 存在两条相同权重
            *unique = 0;
            return;
        }
    }
}