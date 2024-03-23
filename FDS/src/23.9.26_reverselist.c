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
        p=head->Next;   //����L����һ���ڵ�
        head->Next=q;   //��ת
        q=head;
        head=p;         //L��ǰ������һ��
    }
    L->Next=q;          //��һ����ͷ���
    return L;
}