//Write a function to add two polynomials. Do not destroy the input. Use a linked list implementation with a dummy head node.
//Note: The zero polynomial is represented by an empty list with only the dummy head node.
/*①带有头结点的链表，真正存储数据的是下一个结点
②系数和为0的结点跳过，不作为结果链表中的结点
③temp临时结点要在循环内每次重新申请*/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Your function will be put here */

Polynomial Add( Polynomial a, Polynomial b ){
    Polynomial head=(Polynomial)malloc(sizeof(struct Node));
	Polynomial dummy=head,aa,bb;
    aa=a->Next;    //虚拟头结点
    bb=b->Next;
    while(aa&&bb){
        Polynomial temp=(Polynomial)malloc(sizeof(struct Node));
        if(aa->Exponent==bb->Exponent){
            temp->Coefficient=aa->Coefficient+bb->Coefficient;
            temp->Exponent=aa->Exponent;
            aa=aa->Next;
            bb=bb->Next;
            if(temp->Coefficient!=0){
                head->Next=temp;
                head=temp;
            }
        }
        else if(aa->Exponent>bb->Exponent){
            temp->Coefficient=aa->Coefficient;
            temp->Exponent=aa->Exponent;
            aa=aa->Next;
            head->Next=temp;
            head=temp;
        }
        else {
            temp->Coefficient=bb->Coefficient;
            temp->Exponent=bb->Exponent;
            bb=bb->Next;
            head->Next=temp;
            head=temp;
        }
    }
    if(aa) head->Next=aa;
    if(bb) head->Next=bb;
    return dummy;
}