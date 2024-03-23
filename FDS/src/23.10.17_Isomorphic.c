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
    if(T1==NULL && T2==NULL) return 1;              //�����Ϊ0
    else if(T1==NULL && T2!=NULL) return 0;         //����㲻ͬ
    else if(T1!=NULL && T2==NULL) return 0;         //����㲻ͬ
    else if(T1->Element!=T2->Element) return 0;     //����㲻ͬ
    else if(T1->Left==NULL && T2->Left==NULL) {
        return Isomorphic(T1->Right, T2->Right);    //�������Ƚ��ҽ��
    }
    else if(T1->Left!=NULL && T2->Left!=NULL) {
        if(T1->Left->Element == T2->Left->Element)  //����Ԫ����ͬ��Ƚ����ҽ��
            return Isomorphic(T1->Right, T2->Right) && Isomorphic(T1->Left, T2->Left);  
        else                                        //����Ԫ�ز�ͬ�򽻲�Ƚ����ҽ��
            return Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left);  
    }
    else if(T1->Left==NULL && T2->Left!=NULL && T1->Right!=NULL && T2->Right==NULL)
        return Isomorphic(T1->Right, T2->Left);     //T2����Ƚ�T1�ҽ��
    else if(T1->Left!=NULL && T2->Left==NULL && T1->Right==NULL && T2->Right!=NULL)
        return Isomorphic(T1->Left, T2->Right);     //T1����Ƚ�T2�ҽ��
    else return 0;
}
