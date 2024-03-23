#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void Insert(int init[],int N,int part[]);
void PercolateDown(int init[], int i, int N);
void Heap(int init[],int N,int part[]);
int sort_flag = 0;

int main(){
    int N, i;
    int init[MAX], part[MAX], init2[MAX];
    scanf("%d", &N);
    for(i=0; i<N; i++){
        scanf("%d", &init[i]);
        init2[i] = init[i];
    }
    for(i=0; i<N; i++){
        scanf("%d", &part[i]);
    }
    Insert(init, N, part);
    if(!sort_flag) Heap(init2, N, part);
    return 0;
}

void Insert(int init[],int N,int part[]){
    int i, j, temp;
    for(i=1; i<N; i++){
        // 依次寻找排序
        temp = init[i];
        for(j=i; j>0 && init[j-1]>temp; j--){
            init[j] = init[j-1];
        }
        init[j] = temp;
        // 判断此次排序是否满足
        for(j=0; j<N; j++){
            if(init[j] != part[j]) break;
        }
        if(j == N) {
            sort_flag = 1;
            break;
        }
    }
    if(sort_flag){
        printf("Insertion Sort\n");
        // 找下一次排序
        temp = init[++i];
        for(j=i; j>0 && init[j-1]>temp; j--){
            init[j] = init[j-1];
        }
        init[j] = temp;
        // 打印结果
        printf("%d", init[0]);
        for(j=1; j<N; j++){
            printf(" %d", init[j]);
        }
    }
    else return;
}

void Heap(int init[],int N,int part[]){
    int i, j, temp;
    for(i=N/2; i>0; i--){
        PercolateDown(init, i, N);
    }
    for(i=N-1; i>0; i--) {
        // 交换堆顶元素和末尾元素
        temp = init[0];
        init[0] = init[i];
        init[i] = temp;
        // 依次寻找还未做的堆排序
        PercolateDown(init, 1, i);
        // 判断此次排序是否满足
        for(j=0; j<N; j++){
            if(init[j] != part[j]) break;
        }
        if(j == N){
            sort_flag = 1;
            break;
        }
    }
    if(sort_flag){
        printf("Heap Sort\n");
        // 找下一次排序
        i--;
        temp = init[0];
        init[0] = init[i];
        init[i] = temp;
        PercolateDown(init, 1, i);
        // 打印结果
        printf("%d", init[0]);
        for (j = 1; j < N; j++) {
            printf(" %d", init[j]);
        }
    }
    else return;
}

void PercolateDown(int init[], int i, int N){ // 建立最大堆
    int child, parent;
    parent = init[i-1]; // i是从1开始记录的节点标号 但数组从0开始要-1
    while(2*i-1 < N){
        child = 2 * i - 1; // 孩子节点的数组下标
        if(child+1 < N && init[child] < init[child+1]){
            child++;
        }
        if(parent < init[child]){
            init[i-1] = init[child];
        }
        else break;
        i = child + 1;
    }
    init[i-1] = parent;
}