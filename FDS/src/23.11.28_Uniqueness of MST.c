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
    int distance[Max_V];           // ���������С�߳���
    int visit[Max_V] = {0};        // ����Ƿ��ѷ���
    int cnt[Max_V];                // ·������
    memset(distance, 1000000, sizeof(distance));
    distance[0] = 0;               // ��һ�����Ǿ���Ϊ0
    cnt[0] = 1;

    for (i = 0; i < Graph->Nv; i++) {
        int u = -1, v, min_dist = dist;
        for (j = 0; j < Graph->Nv; j++) {
            if (!visit[j] && distance[j] < min_dist) {  // �ҵ�����С����ı߲���¼����ڵ�Prim�㷨
                min_dist = distance[j]; 
                u = j;
            }
        }
        if (min_dist == dist) { // ����ͨ�޷�������С������
            *mst_weight = -1;
            break;
        }
        visit[u] = 1;           // ���Դ�ڵ��ѷ���
        *mst_weight += distance[u];
        for (v = 0; v < Graph->Nv; v++) {
            if (!visit[v] && Graph->G[u][v] != 0) {
                if (Graph->G[u][v] < distance[v]) {
                    distance[v] = Graph->G[u][v];  // ���½ڵ����̱߳���
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
            visit[i] = 1;    // ������ͨ����
        }
    }
    for (i = 0; i < Graph->Nv; i++) {
        if (cnt[i] != 1) { // ����������ͬȨ��
            *unique = 0;
            return;
        }
    }
}