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

// �ڽӾ���ͼ
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
    // ����Դ�ڵ���յ�
    insertNode(&t, sour);
    insertNode(&t, dest);
    int sour_id = findNode(&t, sour);
    int dest_id = findNode(&t, dest);
    Graph graph;
    // �ڽӾ����ʼ��Ϊ0
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

// ����ڵ�
void insertNode(Table* t, char name[]) {
    strcpy(t->nodes[t->size].name, name);
    t->nodes[t->size].id = t->size;
    t->size++;
}
// ����Ƿ��¼�ڵ�
int findNode(Table* t, char name[]) {
    for (int i = 0; i < t->size; i++) {
        if (strcmp(t->nodes[i].name, name) == 0) {
            return t->nodes[i].id;
        }
    }
    return -1; 
}

// �������
int BFS(Graph* graph, int sour, int dest, int parent[]) {
    int visited[MAX_V] = {0};
    int queue[MAX_V];
    int front = 0, rear = 0;
    queue[rear++] = sour;
    visited[sour] = 1;
    parent[sour] = -1;        // Դ�ڵ�û�и��ڵ�
    while (front != rear) {   
        int current = queue[front++];
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->capacity[current][i] > 0 && !visited[i]) { // δ���ʹ��Ҿ������������ڽӽڵ�
                queue[rear++] = i;
                visited[i] = 1;
                parent[i] = current;
            }
        }
    }
    // ��Դ�ڵ㵽���յ���һ��·��
    return visited[dest];
}

// ���������
int MaxFlow(Graph* graph, int sour, int dest) {
    int maxflow = 0;
    int parent[MAX_V];
    while (BFS(graph, sour, dest, parent)) {
        int pathflow = INT_MAX;
        // ���� pathflow Ϊ��ǰ·���ϵ���Сʣ������
        for (int i = dest; i != sour; i = parent[i]) {
            int j = parent[i];
            if (graph->capacity[j][i] < pathflow) pathflow = graph->capacity[j][i];
        }
        // ���³��������
        for (int i = dest; i != sour; i = parent[i]) {
            int j = parent[i];
            graph->capacity[j][i] -= pathflow;
            graph->capacity[i][j] += pathflow;
        }
        maxflow += pathflow;
    }
    return maxflow;
}