#include<stdio.h>
#define max 1000
int main(){
    int M, N, K, i, cnt;
    int stack_in_n, stack_out_m, num; 
    scanf("%d%d%d",&M,&N,&K);
    cnt = 0;
    int stack_in[N],stack_out[M];
    int flag[1000]={0};
    while(cnt++ < K){
        for(i=0; i<N; i++){
            scanf("%d",&stack_in[i]);   //保存N个数
        }

        stack_in_n=0;                   //判断n个
        stack_out_m=-1;                 //栈内index
        num=1;                          //第一个push的是1

        while(stack_in_n<N){
            if(stack_out_m==-1){                //栈为空
                stack_out[++stack_out_m]=num;   //push操作
                num++;
            }
            else{
                if(stack_out[stack_out_m]==stack_in[stack_in_n]){       //需要pop
                    stack_out_m--;
                    stack_in_n++;
                }
                else if(stack_out[stack_out_m]>stack_in[stack_in_n]){   //不可能隔位pop
                    flag[cnt-1]=1;
                    break;
                }
                else{
                    if((stack_out_m+1)==M) {    //超出最大栈空间
                        flag[cnt-1]=1;
                        break;
                    }
                    stack_out[++stack_out_m]=num++;
                }
            }
            if(flag[cnt-1]==1) break;
        }
    }

    for(i=0; i<K; i++){
        if(flag[i]==0) printf("YES\n");
        else printf("NO\n");
    }
    
    return 0;
}


