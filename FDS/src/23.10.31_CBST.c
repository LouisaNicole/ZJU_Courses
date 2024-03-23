#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode *tree;
struct TreeNode {
    int element;
    tree left;
    tree right;
};

void build(tree root, int sorted[], int start, int end)
{
    if(start == end){                       //叶子结点左右为null
        root->element = sorted[start];
        root->left = NULL;
        root->right = NULL;
        return;
    }
    int i, h, cnt, index;
    cnt = end - start + 1;
    h = log2(cnt);
    if((cnt-(pow(2,h)-1)) >= pow(2,h-1)){   //左子树是满树
        index = pow(2,h)-1;
    }
    else{
        index = cnt - (pow(2,h)-1) + (pow(2,h-1)-1);
    }
    root->element = sorted[index];
    if(start <= index-1){                   //继续构造左子树
        root->left = (tree)malloc(sizeof(struct TreeNode));
        int *sorted_left = (int*)malloc(sizeof(int) * (index-start));
        for(i=0; i<index-start; i++){
            sorted_left[i] = sorted[start+i];
        }
        build(root->left, sorted_left, 0, i - 1);
    }
    if(index+1 <= end){
        root->right = (tree)malloc(sizeof(struct TreeNode));
        int *sorted_right = (int*)malloc(sizeof(int) * (end-index));
        for(i=0; i<end-index; i++){
            sorted_right[i] = sorted[index+1+i];
        }
        build(root->right, sorted_right, 0, i - 1);
    }
    return;
}

void print(tree root)
{
    if(root == NULL) return;
    tree queue[1000];                       //顺序遍历需要构造队列
    int front = 0, rear = 0;
    queue[rear++] = root;
    while(front < rear){
        if(front == 0) printf("%d", queue[front]->element);
        else printf(" %d", queue[front]->element);
        if(queue[front]->left != NULL) queue[rear++] = queue[front]->left;
        if(queue[front]->right != NULL) queue[rear++] = queue[front]->right;
        front++;
    }
}

int main()
{
    int i, j, N;
    scanf("%d", &N);
    int sorted[N];                          //需要先对数据排序
    for(i=0; i<N; i++){
        scanf("%d", &sorted[i]);
    }
    for(i=0; i<N-1; i++){
        for(j=0; j<N-i-1; j++){
            if(sorted[j] > sorted[j+1])
            {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    tree root = (tree)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    build(root, sorted, 0, N-1);
    print(root);
    return 0;
}