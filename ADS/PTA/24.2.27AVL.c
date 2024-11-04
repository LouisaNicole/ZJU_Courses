#include<stdio.h>
// #include<math.h>
typedef struct AVLNode *PtrNode;
struct AVLNode
{
    int element;
    PtrNode left;
    PtrNode right;
    PtrNode parent;
};

int CalculateHeight(PtrNode tree);
void Insert(PtrNode tree, int temp);
void Rotation(PtrNode *tree);
int flag=0;

int main(){
    int N, i, temp_element;
    scanf("%d", &N);
    PtrNode AVLtree = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    for(i=0; i<N; i++){
        scanf("%d", &temp_element);
        if(i==0){
            AVLtree->element = temp_element;
            AVLtree->left = NULL;
            AVLtree->right = NULL;
            AVLtree->parent = NULL;
        }
        else{
            Insert(AVLtree, temp_element);
            Rotation(&AVLtree);
        }
    }
    printf("%d", AVLtree->element);
    return 0;
}

int CalculateHeight(PtrNode tree){
    int left_height=1, right_height=1;
    if(tree == NULL) return 0;
    if(tree->left==NULL && tree->right==NULL){
        return 1;
    }
    if(tree->left != NULL){
        left_height += CalculateHeight(tree->left);
    }
    if(tree->right != NULL){
        right_height += CalculateHeight(tree->right);
    }
    if(left_height < right_height) return right_height;
    else return left_height;
}

void Insert(PtrNode tree, int temp)
{
    if (temp < tree->element)
    {
        if (tree->left == NULL)
        {
            PtrNode TempNode = (struct AVLNode *)malloc(sizeof(struct AVLNode));
            TempNode->element = temp;
            TempNode->left = NULL;
            TempNode->right = NULL;
            TempNode->parent = NULL;
            tree->left = TempNode;
            TempNode->parent = tree;
        }
        else
            Insert(tree->left, temp);
    }
    else if (temp > tree->element)
    {
        if (tree->right == NULL)
        {
            PtrNode TempNode = (struct AVLNode *)malloc(sizeof(struct AVLNode));
            TempNode->element = temp;
            TempNode->left = NULL;
            TempNode->right = NULL;
            TempNode->parent = NULL;
            tree->right = TempNode;
            TempNode->parent = tree;
        }
        else
            Insert(tree->right, temp);
    }
}
// void Insert(PtrNode tree, int temp){
//     PtrNode TempNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
//     if(temp < tree->element){
//         if(tree->left == NULL){
//             tree->left = TempNode;
//             TempNode->left = NULL;
//             TempNode->right = NULL;
//             TempNode->parent = tree;
//         }
//         else Insert(tree->left, temp);
//     }
//     else if(temp > tree->element){
//         if(tree->right == NULL){
//             tree->right = TempNode;
//             TempNode->left = NULL;
//             TempNode->right = NULL;
//             TempNode->parent = tree;
//         }
//         else Insert(tree->right, temp);
//     }
// }

// void Rotation(PtrNode tree){
//     int left_h, right_h;
//     if(tree==NULL || (tree->left==NULL && tree->right==NULL)) return;
//     else{
//         left_h = CalculateHeight(tree->left);
//         right_h = CalculateHeight(tree->right);
//         if(left_h-right_h>1){
//             Rotation(tree->left);
//             flag=1;
//         }
//         else if(left_h-right_h<-1){
//             Rotation(tree->right);
//             flag=2;
//         }
//         else{
//             if(!flag){
//                 Rotation(tree->left);
//                 Rotation(tree->right);
//             }
//             else if(left_h-right_h==1 && flag==1){ //LL
            
//             }
//             else if(left_h-right_h==-1 && flag==1){ //LR

//             }
//             else if(left_h-right_h==1 && flag==2){ //RL

//             }
//             else if(left_h-right_h==-1 && flag==2){ //RR

//             }
//         }
//     }
// }

void RotateLeft(PtrNode* tree)  //henzhongyao!!!!!!!!!!
{
    PtrNode pivot = (*tree)->right;
    (*tree)->right = pivot->left;
    if (pivot->left != NULL)
        pivot->left->parent = (*tree);
    pivot->left = (*tree);
    pivot->parent = (*tree)->parent;
    (*tree)->parent = pivot;
    (*tree) = pivot;  // 这一步更新了tree的指针
}

void RotateRight(PtrNode* tree)
{
    PtrNode pivot = (*tree)->left;
    (*tree)->left = pivot->right;
    if (pivot->right != NULL)
        pivot->right->parent = (*tree);
    pivot->right = (*tree);
    pivot->parent = (*tree)->parent;
    (*tree)->parent = pivot;
    (*tree) = pivot;
}

void Rotation(PtrNode* tree)
{
    if ((*tree) == NULL || ((*tree)->left == NULL && (*tree)->right == NULL))
        return;
    else
    {
        Rotation(&((*tree)->left));
        Rotation(&((*tree)->right));

        int left_h = CalculateHeight((*tree)->left);
        int right_h = CalculateHeight((*tree)->right);
        int balance = left_h - right_h;

        if (balance > 1)
        {
            int left_left_h = CalculateHeight((*tree)->left->left);
            int left_right_h = CalculateHeight((*tree)->left->right);

            if (left_left_h >= left_right_h)   //LL
                RotateRight(tree);
            else                               //LR
            {
                RotateLeft(&((*tree)->left));  //在左旋操作中，我们需要更新左子树的指针，以确保旋转后的树结构正确
                RotateRight(tree); //在右旋操作中不需要更新右子树的指针，因为只涉及到当前根节点和其左子节点的指针变化
            }
        }
        else if (balance < -1)
        {
            int right_left_h = CalculateHeight((*tree)->right->left);
            int right_right_h = CalculateHeight((*tree)->right->right);

            if (right_right_h >= right_left_h) //RR
                RotateLeft(tree);
            else                               //RL
            {
                RotateRight(&((*tree)->right));
                RotateLeft(tree);
            }
        }
    }
}
