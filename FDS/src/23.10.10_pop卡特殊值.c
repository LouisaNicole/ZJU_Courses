#include<stdio.h>
// #define max 1000
int main(){
    int M, N, K, cnt=0, i, j;
    int max, min;
    scanf("%d%d%d",&M,&N,&K);
    int stack_in[K][N];
    int flag[K];
    for(i=0; i<K; i++){
        for(j=0; j<N; j++){
            scanf("%d",&stack_in[i][j]);
        }
    }
    for(i=0; i<K; i++){
        if(stack_in[i][0]>M) {
            flag[i]=0;
            continue;
        }
        cnt=stack_in[i][0];
        max=min=cnt;
        for(j=1; j<N; j++){
            if(stack_in[i][j]<stack_in[i][j-1]) {
                cnt--;
                min=cnt;      //pop的最小的值
            }
            else{
                cnt=stack_in[i][j]-(max-min)-1;
                max=stack_in[i][j];      //现在栈内存在的个数
            }
            if(cnt>M){
                flag[i]=0;
                break;
            }
        }
        if(cnt<=0|cnt>M) {
            flag[i]=0;
        }
        else flag[i]=1;
        cnt=0;
    }
    for(i=0; i<K; i++){
        if(flag[i]==1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
