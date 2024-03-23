#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL)
    {
        printf("Out of memory!");
        return NULL;
    }

    // 初始化堆的属性
    H->Elements = (ElementType *)malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL)
    {
        printf("Out of memory!");
        free(H);
        return NULL;
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; // 哨兵元素，不使用下标为0的位置

    return H;
}

/* Your function will be put here */
void PercolateUp( int p, PriorityQueue H ){
    int i, Parent, Last; 
    Last = H->Elements[H->Size]; 
    for(i = H->Size; i/2 > 0; i = Parent ) {
        Parent = i/2; 
        if(Last < H->Elements[Parent] )   /* Percolate up */ 
	       H->Elements[i] = H->Elements[Parent]; 
        else break;
    } 
    H->Elements[i] = Last;
}
void PercolateDown( int p, PriorityQueue H ){
    int i, Child, Last; 
    Last = H->Elements[1]; 
    if(H == NULL)  return H->Elements[ 0 ]; 
    for(i = 1; i*2 <= H->Size; i = Child ) {
        Child = i*2; 
        if(Child != H->Size && H->Elements[Child+1] < H->Elements[Child]) 
	        Child++;     
        if(Last > H->Elements[Child] )   /* Percolate down */ 
	       H->Elements[i] = H->Elements[Child]; 
        else break;
    } 
    H->Elements[i] = Last;
}