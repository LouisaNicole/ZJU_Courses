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
            scanf("%d",&stack_in[i]);   //����N����
        }

        stack_in_n=0;                   //�ж�n��
        stack_out_m=-1;                 //ջ��index
        num=1;                          //��һ��push����1

        while(stack_in_n<N){
            if(stack_out_m==-1){                //ջΪ��
                stack_out[++stack_out_m]=num;   //push����
                num++;
            }
            else{
                if(stack_out[stack_out_m]==stack_in[stack_in_n]){       //��Ҫpop
                    stack_out_m--;
                    stack_in_n++;
                }
                else if(stack_out[stack_out_m]>stack_in[stack_in_n]){   //�����ܸ�λpop
                    flag[cnt-1]=1;
                    break;
                }
                else{
                    if((stack_out_m+1)==M) {    //�������ջ�ռ�
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


