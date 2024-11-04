#include <stdio.h>
#include <stdlib.h>
#define order 3

// 定义B+树的节点结构
typedef struct Node* BPlusTree;
struct Node {
    int KeysNum;                // 节点键值对数量
    int IsLeaves;               // 是否为叶子节点
    int Keys[order+1];          // 键值对的键数组（多存一个）
    BPlusTree Parent;           // 节点的父亲
    BPlusTree Children[order+1];// 子节点指针数组
    BPlusTree Next;             // 叶子节点的下一个节点指针
};

// 创建一个新的B+树节点
BPlusTree Create() {
    BPlusTree tmp = (struct Node*)malloc(sizeof(struct Node));
    int i;
    tmp->KeysNum = 0;
    tmp->IsLeaves = 0;
    for(i=0; i<order+1; i++){
        tmp->Keys[i] = -1;      // 初始化-1表示没有key值
    }
    for(i=0; i<order+1; i++){
        tmp->Children[i] = NULL;
    }
    tmp->Next = NULL;
    tmp->Parent = NULL;
    return tmp;
}

void Split(BPlusTree* node, int ch_index){
    BPlusTree split = Create();
    BPlusTree tmp = *node;
    int i, pa_index, flag=0; // flag1用来判断是父结点,这样后面不用更新isleaves的值
    int key_index;
    if(tmp->IsLeaves){  // 叶子结点的分裂
        key_index = (order+1)/2;
        for(i=0; i<order+1-key_index; i++){
            split->Keys[i] = tmp->Keys[key_index+i];
            split->KeysNum++;  // 将要分裂的值存入新的节点split
        }        
    }
    else{  //父节点的分裂，只需要索引
        key_index = order/2;
        split->Keys[0] = tmp->Keys[order-1];
        split->KeysNum++;
        flag = 1;
        tmp->Children[2]->Parent = split;  // 这里不要忘记修改tmp->Children的Parent的指向！
        tmp->Children[3]->Parent = split;
        split->Children[0] = tmp->Children[2]; // 可以参考这个网站图示https://blog.nowcoder.net/n/b75730750cc24778bd2ee666f74b0e78?from=nowcoder_improve
        split->Children[1] = tmp->Children[3]; // 根结点变成三个元素后可能出现指向4个children这是不合法的，父节点要分裂
        tmp->Children[2] = NULL;
        tmp->Children[3] = NULL;
    }
    BPlusTree parent = tmp->Parent;
    if(parent != NULL){
        pa_index = 0;
        while(pa_index<parent->KeysNum && tmp->Keys[key_index]>=parent->Keys[pa_index] && parent->Keys[pa_index]!=-1){
            pa_index++;
        }
        // 这里做的是搜索待插入的值与父节点的已存在的值的大小关系，找到正确位置
        for(i=parent->KeysNum; i>pa_index; i--){
            parent->Keys[i] = parent->Keys[i-1];
            parent->Children[i+1] = parent->Children[i];
        }
        parent->Keys[pa_index] = tmp->Keys[key_index];
        parent->KeysNum++;

        split->Parent = parent;
        if(!flag) split->IsLeaves = 1;  // 这就是之前提到的flag的作用
        split->Next = tmp->Next;
        
        parent->Children[pa_index+1] = split;
        for(i=key_index; i<order+1; i++){
            tmp->Keys[i] = -1;  // 原来分裂前的tmp后面的元素要置空（因为放在split里面了）
        }
        tmp->Next = split;
        tmp->KeysNum = key_index;

        if(parent->KeysNum >= order){
            Split(&parent, ch_index);  // 递归进行父节点分裂
            parent = tmp->Parent; // 更新parent指针
        }
        
    } 
    else{ // 创建新的根结点
        BPlusTree new_root = Create();
        new_root->Keys[0] = tmp->Keys[key_index];
        new_root->KeysNum++;
        for(i=key_index; i<order+1; i++){
            tmp->Keys[i] = -1;
        }
        if(!flag){
            split->IsLeaves = 1;
            tmp->IsLeaves = 1;  // 更新原节点为叶子节点
        }
        split->Next = tmp->Next;
        tmp->Next = split;
        tmp->KeysNum = key_index;

        tmp->Parent = new_root;
        split->Parent = new_root;
        
        new_root->Children[0] = tmp;
        new_root->Children[1] = split;
        *node = new_root;
    }
}

BPlusTree Insert(BPlusTree root, int key){
    BPlusTree node = root;
    if(root == NULL){
        root = Create();
        root->Keys[root->KeysNum++] = key;
        root->IsLeaves = 1;
    } 
    else{
        int i, ch_index = 0, key_index = 0;
        while(!node->IsLeaves) {
            ch_index = 0;
            while(ch_index<node->KeysNum && key>=node->Keys[ch_index] && node->Keys[ch_index]!=-1){
                ch_index++;
            }
            node = node->Children[ch_index];
        }
        
        key_index = 0;
        while(key_index<node->KeysNum && key>=node->Keys[key_index] && node->Keys[key_index]!=-1){
            if(key == node->Keys[key_index]){
                printf("Key %d is duplicated\n", key);
                return root;
            }
            key_index++;
        }
        
        for(i=order; i>=key_index+1; i--){
            node->Keys[i] = node->Keys[i-1];
        }
        node->Keys[key_index] = key;
        if(node->KeysNum < order){
            node->KeysNum++;
        } 
        else{
            Split(&node, 0);
            // 判断是否需要更新根节点
            while(node->Parent != NULL){
                node = node->Parent;
            }
            root = node;
        }
    }
    return root;
}

void printBPlusTree(BPlusTree root) {
    if(root == NULL) {
        return;
    }
    int i, j, front = 0, rear = 0, size;
    BPlusTree queue[10001];
    queue[rear++] = root; // 入列
    while(front < rear) {
        size = rear - front;
        for(i=0; i<size; i++) {  // 每一层size固定
            BPlusTree node = queue[front++];  // 出列
            if(node->KeysNum) printf("[");
            for(j = 0; j < node->KeysNum; j++) {
                printf("%d", node->Keys[j]);
                if(j < node->KeysNum - 1) {
                    printf(",");
                }
            }
            printf("]");
            
            if(!node->IsLeaves){ // 保存孩子节点
                for(j=0; j<node->KeysNum+1; j++) {
                    queue[rear++] = node->Children[j];
                }
            }
        }
        printf("\n");
    }
}

int main() {
    BPlusTree root = NULL;
    int n, i, tmp;
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%d", &tmp);
        root = Insert(root, tmp);
    }
    printBPlusTree(root);
    return 0;
}