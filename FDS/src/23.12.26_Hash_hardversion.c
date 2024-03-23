#include <stdio.h>
#include <stdlib.h>

#define N_MAX 1000
#define INF 99999999

struct list{
    int data;
    struct list *next;
};
typedef struct list *LNode;

struct map{
    int size;
    LNode Heads;
};
typedef struct map *HashMap;

int indegree[N_MAX] = {0};

//创造哈希表
HashMap CreateHashMap()
{
    int HashMapSize,i;
    HashMap H;
    scanf("%d",&HashMapSize);
    H = (HashMap)malloc(sizeof(struct map));
    H->size = HashMapSize;
    H->Heads = (LNode)malloc(sizeof(struct list) * H->size);

	//初始化数据
    for(i=0;i< H->size;i++)
    {
        H->Heads[i].data = -1;
        H->Heads[i].next = NULL;
    } 
    return H;
}

//解决入度数组
void FindinDegree(HashMap H)
{
    int i,temp,position,number;
    LNode NewNode;
    for(i=0;i < H->size;i++)
    {
        scanf("%d",&temp);
        
        //忽略掉 -1
        if(temp > 0)
        {
            position = temp % H->size;
			
			//如果哈希表位置不等于本来属于他的位置
            while(i != position)
            {
            	//创造结点就是等于 把这个霸占了原来属于他的位置
            	//霸主的出度给记录下来
                NewNode = (LNode)malloc(sizeof(struct list));
                NewNode->data = temp;
                NewNode->next = H->Heads[position].next;
                H->Heads[position].next = NewNode;

				//这个被霸占的数字出度+1
                indegree[temp]++;
                position++;
                //如果超出当前哈希表最大数 则减去 从头开始
                if(position >= H->size)
                    position -= H->size;
            }
            	//找到属于他的位置 赋值即可
                H->Heads[position].data = temp;
        }
    }
    return;
}

int main()
{
    int i;
    HashMap H;
    int HashMapSize;
    H = CreateHashMap();
    FindinDegree(H);
    int count = 0,min,temp,data;

	//工具人指针 负责确定位置的
    LNode position;
	
	//为了把 -1的数字给排除掉
    int Visit[1000] = {0};
    for(i=0;i < H->size;i++)
    {
        if(H->Heads[i].data < 0 && !Visit[i])
        {
            Visit[i] = 1;
            count++;
        }
    }
    
    while(count != H->size)
    {
        min = INF;
        for(i=0;i < H->size;i++)
        {
            if(!Visit[i])
            {
                if(!indegree[H->Heads[i].data] && H->Heads[i].data < min)
                {
                    min = H->Heads[i].data;
                    temp = i;
                }
            }
        }
        count++;
        Visit[temp] = 1;

		//入度-1
        indegree[min]--;
        position = H->Heads[temp].next;

		//把访问过的结点后面记录入度的链表访问一遍
		//并重新计算入度
        while(position)
        {
            indegree[position->data]--;
            position = position->next;
        }
        if(count==H->size)
            printf("%d",min);
        else
            printf("%d ",min);
    }
    return 0;
}
