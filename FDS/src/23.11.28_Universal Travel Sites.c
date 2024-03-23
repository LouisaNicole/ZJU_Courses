#include <stdio.h>
#include <limits.h>
#include <string.h>
#define MAX_V 1000

typedef struct {
    char name[4];
    int id;
} str_int;

typedef struct {
    str_int nodes[MAX_V];
    int size;
} Table;

// 邻接矩阵图
typedef struct {
    int vertices;
    int capacity[MAX_V][MAX_V];
} Graph;

void insertNode(Table* t, char name[]);
int findNode(Table* t, char name[]);
int BFS(Graph* graph, int sour, int dest, int parent[]);
int MaxFlow(Graph* graph, int sour, int dest);

int main() {
    Table t;
    t.size = 0;
    char sour[4], dest[4];
    int N;
    scanf("%s %s %d", sour, dest, &N);
    // 插入源节点和终点
    insertNode(&t, sour);
    insertNode(&t, dest);
    int sour_id = findNode(&t, sour);
    int dest_id = findNode(&t, dest);
    Graph graph;
    // 邻接矩阵初始化为0
    for (int i = 0; i < MAX_V; i++) {
        for (int j = 0; j < MAX_V; j++) {
            graph.capacity[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        char source[4], destination[4];
        int capacity;
        scanf("%s %s %d", source, destination, &capacity);
        if(findNode(&t, source) == -1) insertNode(&t, source);
        if(findNode(&t, destination) == -1) insertNode(&t, destination);
        int source_id = findNode(&t, source);
        int destination_id = findNode(&t, destination);
        graph.capacity[source_id][destination_id] = capacity;
    }
    graph.vertices = t.size;
    printf("%d\n", MaxFlow(&graph, sour_id, dest_id));
    return 0;
}

// 插入节点
void insertNode(Table* t, char name[]) {
    strcpy(t->nodes[t->size].name, name);
    t->nodes[t->size].id = t->size;
    t->size++;
}
// 检查是否记录节点
int findNode(Table* t, char name[]) {
    for (int i = 0; i < t->size; i++) {
        if (strcmp(t->nodes[i].name, name) == 0) {
            return t->nodes[i].id;
        }
    }
    return -1; 
}

// 广度搜索
int BFS(Graph* graph, int sour, int dest, int parent[]) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;
    queue[rear++] = sour;
    visited[sour] = 1;
    parent[sour] = -1;        // 源节点没有父节点
    while (front != rear) {   
        int current = queue[front++];
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->capacity[current][i] > 0 && !visited[i]) { // 未访问过且具有正容量的邻接节点
                queue[rear++] = i;
                visited[i] = 1;
                parent[i] = current;
            }
        }
    }
    // 从源节点到接收点有一条路径
    return visited[dest];
}

// 找最大流量
int MaxFlow(Graph* graph, int sour, int dest) {
    int maxflow = 0;
    int parent[MAX_V];
    while (BFS(graph, sour, dest, parent)) {
        int pathflow = INT_MAX;
        // 更新 pathflow 为当前路径上的最小剩余容量
        for (int i = dest; i != sour; i = parent[i]) {
            int j = parent[i];
            if (graph->capacity[j][i] < pathflow) pathflow = graph->capacity[j][i];
        }
        // 更新出入的流量
        for (int i = dest; i != sour; i = parent[i]) {
            int j = parent[i];
            graph->capacity[j][i] -= pathflow;
            graph->capacity[i][j] += pathflow;
        }
        maxflow += pathflow;
    }
    return maxflow;
}