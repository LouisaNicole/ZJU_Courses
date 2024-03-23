#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N_MAX 100001

typedef struct ListNode *List; 
typedef struct Hash *HashTable; 
struct ListNode{ 
	int Element; 
	List Next; 
};  
struct Hash{ 
	int TableSize; 
	List *Lists; 
}; 

int main(){
    int TableSize, position, num;
    int i, min, index, cnt = 0;
    int search[N_MAX] = {0};
    int Visit[N_MAX] = {0};
    scanf("%d", &TableSize);
    HashTable H;
    H = malloc(sizeof(struct Hash));  
    // if(H == NULL) FatalError("Out of space!"); 
    H->TableSize = TableSize;
    H->Lists = malloc(sizeof(List) * H->TableSize);
    for(i=0; i< H->TableSize; i++){
        H->Lists[i] = malloc(sizeof(struct ListNode));
        H->Lists[i]->Element = -1;
        H->Lists[i]->Next = NULL;
    }

    List NewNode;
    for(i=0; i<H->TableSize; i++){
        scanf("%d", &num);
        if(num > 0){
            position = num % TableSize;
            while(i != position){    // 哈希表位置不等于本来属于他的位置
                NewNode = (List)malloc(sizeof(struct ListNode));
                NewNode->Element = num;
                NewNode->Next = H->Lists[position]->Next;
                H->Lists[position]->Next = NewNode;

                search[num]++;
                position++;
                if(position >= H->TableSize) position -= H->TableSize;
            }
            H->Lists[position]->Element = num;
        }
    }

    for(i=0; i<H->TableSize; i++){
        if(H->Lists[i]->Element < 0 && !Visit[i]){  // 排除负数
            Visit[i] = 1;
            cnt++;
        }
    }
    while(cnt < H->TableSize){
        min = INT_MAX;
        for(i=0; i<H->TableSize; i++){
            if(!Visit[i] && !search[H->Lists[i]->Element] && H->Lists[i]->Element < min){  // 没有处在前面的节点
                min = H->Lists[i]->Element;
                index = i;
            }
        }
        cnt++;
        Visit[index] = 1;

        search[min]--;
        List pos;
        pos = H->Lists[index]->Next;  // 遍历后面的同list的节点
        while(pos != NULL){
            search[pos->Element]--;
            pos = pos->Next;
        }
        if(cnt == H->TableSize) printf("%d", min);
        else printf("%d ", min);
    }
}