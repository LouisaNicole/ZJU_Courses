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
    construct(t1, inorder, postorder, n);                    //����һ��������
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
    if(n == 1){        		    //ֻ��һ��Ԫ�أ���Ҷ��� 
    	t->left = NULL;
    	t->right = NULL;
    	return ;
	}
	else if(index == n-1){		//ֻ������ 
		t->right = NULL;
	}
    else if(i == n) index = -1;
    int* new_in_left = (int*)malloc(sizeof(int) * index);
    int* new_in_right = (int*)malloc(sizeof(int) * (n-index-1));
    int* new_post_left = (int*)malloc(sizeof(int) * index);
    int* new_post_right = (int*)malloc(sizeof(int) * (n-index-1));

    for(i=0; i<index; i++){
        new_in_left[i] = in_order[i];                   //����һ������������
        new_post_left[i] = post_order[i];               //����һ������������
    }
    for(i=index+1; i<n; i++){
        new_in_right[i-index-1] = in_order[i];          //����һ������������
        new_post_right[i-index-1] = post_order[i-1];    //����һ������������
    }

    if (index != 0) {                                   //����Ҷ���
        t->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        construct(t->left, new_in_left, new_post_left, index);
    }
    if (index != n - 1) {                               //������󣬼����ҽ��
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
                                                           //tree��ָ�����
    int front = 0, rear = 0, cnt = 1, level = 1, rear_flag = 1;
    int* levelsize = (int*)malloc(sizeof(int) * 31);       //�㼶�н�������
    levelsize[level] = 1;                                  //��һ������Ϊ1
    queue[rear++] = t;                                     //���в����һ�������
    int flag = 1;
    while(front < rear){
        struct TreeNode* current = queue[--rear_flag];     //����ѭ��ǰ��ʼ�������
        if(flag) {
            printf("%d", queue[front]->element);           //�������һ�����
            flag = 0;
        }
        else printf(" %d", queue[front]->element);
        front++;

        if(level%2 == 1){                                  //����
            if(current->left != NULL){             		   //�սڵ��ʱ��д���Ԫ����0
                queue[rear++] = current->left;
                levelsize[level+1]++;
            }
            if(current->right != NULL){
                queue[rear++] = current->right;
                levelsize[level+1]++;
            }
        } 
        else{                                              //����
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
        if(cnt == 0){                                      //�����㼶�����н�㶼�������ж���һ��
            level++;
            cnt = levelsize[level]; 
            rear_flag = rear;                              //��¼���һ��������е�ֵ ��һ�α����ı��
        }
    }
    free(levelsize);
    free(queue);
}
