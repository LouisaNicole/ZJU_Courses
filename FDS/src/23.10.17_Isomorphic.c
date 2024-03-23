#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

/* Your function will be put here */

int Isomorphic( Tree T1, Tree T2 ){
    if(T1==NULL && T2==NULL) return 1;              //根结点为0
    else if(T1==NULL && T2!=NULL) return 0;         //根结点不同
    else if(T1!=NULL && T2==NULL) return 0;         //根结点不同
    else if(T1->Element!=T2->Element) return 0;     //根结点不同
    else if(T1->Left==NULL && T2->Left==NULL) {
        return Isomorphic(T1->Right, T2->Right);    //左结点空则比较右结点
    }
    else if(T1->Left!=NULL && T2->Left!=NULL) {
        if(T1->Left->Element == T2->Left->Element)  //左结点元素相同则比较左右结点
            return Isomorphic(T1->Right, T2->Right) && Isomorphic(T1->Left, T2->Left);  
        else                                        //左结点元素不同则交叉比较左右结点
            return Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left);  
    }
    else if(T1->Left==NULL && T2->Left!=NULL && T1->Right!=NULL && T2->Right==NULL)
        return Isomorphic(T1->Right, T2->Left);     //T2左结点比较T1右结点
    else if(T1->Left!=NULL && T2->Left==NULL && T1->Right==NULL && T2->Right!=NULL)
        return Isomorphic(T1->Left, T2->Right);     //T1左结点比较T2右结点
    else return 0;
}
