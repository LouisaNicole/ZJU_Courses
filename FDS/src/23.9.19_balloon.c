#include<stdio.h>
int main(){
    int n,h,i,j,count,index,pop,start;
    int max=1;
    scanf("%d%d",&n,&h);
    int ball[n];
    for(i=0;i<n;i++){
        scanf("%d",&ball[i]);
    }
    for(i=n-1;i>=0;i--){  //���һ����һ���������е����򣬵������ʱ�����
        pop=ball[i]-h;  //�������ʼλ��
        if(pop<=ball[0]) {  
            count=i+1;
            if(count>=max) {max=count;start=pop;}  //�ӵ�һ����߿�ʼ���
            //ע�������ʼ����pop������ball[0]
            continue;
        }  
        count=0;
        for(j=i;j>=0;j--){ 
            if(pop<=ball[j]) {count++;}  //�ҵ�start position
            else break;
        }
        if(count>=max) {max=count;start=pop;}
    }
    printf("%d %d",start,max);
    return 0;
}
