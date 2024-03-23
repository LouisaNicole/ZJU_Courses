#include<stdio.h>

struct queue{
    char operation;
    int element;
};

int main(){
    int N, i, cnt, stack_in, stack_out;
    char ch; 
    scanf("%d", &N);
    ch = getchar();
    int s1[N+1], s2[N+1];
    s1[0] = s2[0] = -1;
    stack_in = 0, stack_out = 0;     //标记空栈
    cnt = 0;
	struct queue queues[N];
    for(i=0; i<N; i++){
//        scanf("%c %d", &queues[i].operation, &queues[i].element);   //初始化
		scanf("%c",&queues[i].operation);
		if(queues[i].operation=='I'){
			scanf("%d",&queues[i].element);
			getchar();
		} 
        else getchar();
    }

    for(i=0; i<N; i++){
        if(queues[i].operation == 'I'){
            s1[stack_in++] = queues[i].element;
            continue;
        }
        else{
            if(s1[0] == -1 && s2[0] == -1){
                printf("ERROR\n");
                continue;
            }
            else if(s2[0] == -1){
                while(stack_in){
                    s2[stack_out++] = s1[--stack_in]; 
                    cnt += 2;
                }
                s1[0] = -1;        //重新将输入s1变成空栈
                cnt ++;
                printf("%d %d\n",s2[--stack_out],cnt);
                cnt = 0;
                if(stack_out == 0) s2[0] = -1;   //重新将输入s2变成空栈
            } 
            else{
                cnt = 1;
                printf("%d %d\n",s2[--stack_out],cnt);
                cnt = 0;
                if(stack_out == 0) s2[0] = -1;  //重新将输入s2变成空栈
            }
        }
    }
    return 0;
}