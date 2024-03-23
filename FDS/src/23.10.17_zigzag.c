#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode *tree;

void construct(tree t, int in_order[], int post_order[], int n);
void printtree(tree t);

struct TreeNode{
    int element;
    tree left;
    tree right;
};

int main(){
    int n, i;
    scanf("%d", &n);
    int inorder[n], postorder[n];
    for(i=0; i<n; i++){
        scanf("%d", &inorder[i]);
    }
    for(i=0; i<n; i++){
        scanf("%d", &postorder[i]);
    }
    tree t1 = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    construct(t1, inorder, postorder, n);                    //构建一个二叉树
    printtree(t1);
    return 0;
}
void construct(tree t, int in_order[], int post_order[], int n){
    if(n == 0){
        t->left = NULL;
        t->right = NULL;
        return;
    }

    int i, index;
    t->element = post_order[n-1];
    for(i=0; i<n; i++){
        if(in_order[i] == t->element){
            index = i;
            break;
        }
    }
    if(n == 1){        		    //只有一个元素，即叶结点 
    	t->left = NULL;
    	t->right = NULL;
    	return ;
	}
	else if(index == n-1){		//只有左结点 
		t->right = NULL;
	}
    else if(i == n) index = -1;
    int* new_in_left = (int*)malloc(sizeof(int) * index);
    int* new_in_right = (int*)malloc(sizeof(int) * (n-index-1));
    int* new_post_left = (int*)malloc(sizeof(int) * index);
    int* new_post_right = (int*)malloc(sizeof(int) * (n-index-1));

    for(i=0; i<index; i++){
        new_in_left[i] = in_order[i];                   //构建一个左子树中序
        new_post_left[i] = post_order[i];               //构建一个左子树后序
    }
    for(i=index+1; i<n; i++){
        new_in_right[i-index-1] = in_order[i];          //构建一个右子树中序
        new_post_right[i-index-1] = post_order[i-1];    //构建一个右子树后序
    }

    if (index != 0) {                                   //不是叶结点
        t->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        construct(t->left, new_in_left, new_post_left, index);
    }
    if (index != n - 1) {                               //不是最后，即有右结点
        t->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        construct(t->right, new_in_right, new_post_right, n - index - 1);
    }

    free(new_in_left);
    free(new_in_right);
    free(new_post_left);
    free(new_post_right);
}
void printtree(tree t){
    if(t == NULL) return;
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 31);
                                                           //tree的指针队列
    int front = 0, rear = 0, cnt = 1, level = 1, rear_flag = 1;
    int* levelsize = (int*)malloc(sizeof(int) * 31);       //层级中结点的数量
    levelsize[level] = 1;                                  //第一层结点数为1
    queue[rear++] = t;                                     //队列插入第一个根结点
    int flag = 1;
    while(front < rear){
        struct TreeNode* current = queue[--rear_flag];     //进入循环前初始化根结点
        if(flag) {
            printf("%d", queue[front]->element);           //队列输出一个结点
            flag = 0;
        }
        else printf(" %d", queue[front]->element);
        front++;

        if(level%2 == 1){                                  //正序
            if(current->left != NULL){             		   //空节点的时候写入的元素是0
                queue[rear++] = current->left;
                levelsize[level+1]++;
            }
            if(current->right != NULL){
                queue[rear++] = current->right;
                levelsize[level+1]++;
            }
        } 
        else{                                              //逆序
            if(current->right != NULL){
                queue[rear++] = current->right;
                levelsize[level+1]++;
            }
            if(current->left != NULL){
                queue[rear++] = current->left;
                levelsize[level+1]++;
            }
        }

        cnt--; 
        if(cnt == 0){                                      //将本层级的所有结点都输出完后判断下一行
            level++;
            cnt = levelsize[level]; 
            rear_flag = rear;                              //记录最后一个进入队列的值 下一次遍历的标记
        }
    }
    free(levelsize);
    free(queue);
}
