//Write a function to add two polynomials. Do not destroy the input. Use a linked list implementation with a dummy head node.
//Note: The zero polynomial is represented by an empty list with only the dummy head node.
/*�ٴ���ͷ�������������洢���ݵ�����һ�����
��ϵ����Ϊ0�Ľ������������Ϊ��������еĽ��
��temp��ʱ���Ҫ��ѭ����ÿ����������*/

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
    aa=a->Next;    //����ͷ���
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