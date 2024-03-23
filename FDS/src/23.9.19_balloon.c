#include<stdio.h>
int main(){
    int n,h,i,j,count,index,pop,start;
    int max=1;
    scanf("%d%d",&n,&h);
    int ball[n];
    for(i=0;i<n;i++){
        scanf("%d",&ball[i]);
    }
    for(i=n-1;i>=0;i--){  //最后一个数一定是数组中的气球，倒着算的时间更少
        pop=ball[i]-h;  //允许的起始位置
        if(pop<=ball[0]) {  
            count=i+1;
            if(count>=max) {max=count;start=pop;}  //从第一个左边开始最多
            //注意这个起始点是pop而不是ball[0]
            continue;
        }  
        count=0;
        for(j=i;j>=0;j--){ 
            if(pop<=ball[j]) {count++;}  //找到start position
            else break;
        }
        if(count>=max) {max=count;start=pop;}
    }
    printf("%d %d",start,max);
    return 0;
}
