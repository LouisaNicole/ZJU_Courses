//Write a nonrecursive procedure to reverse a singly linked list in O(N) time using constant extra space.
//The function Reverse is supposed to return the reverse linked list of L, with a dummy header.

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); 
void Print( List L ); 
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

// Your function will be put here 

List Reverse( List L ){
    if (L->Next==NULL||L->Next->Next==NULL) return L;
    List p,head,q=NULL;
    head=L->Next;
    while(head!=NULL){
        p=head->Next;   //保护L的下一个节点
        head->Next=q;   //翻转
        q=head;
        head=p;         //L往前继续下一个
    }
    L->Next=q;          //有一个虚头结点
    return L;
}