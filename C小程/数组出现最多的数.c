#include<stdio.h>
int main(){
    int i,n,m=0,number,item;
    scanf("%d",&n);
    static int a[10];
    for(i=1;i<=n;i++){
        scanf("%d",&number);
        if(number==0) a[0]++; 
        while(number>0){
        	item=number%10;
            a[item]++;
            number/=10;
        }
    }
    for(i=0;i<10;i++){
        if(a[i]>m){
            m=a[i];
        }
    }
    printf("%d:",m);
    for(i=0;i<10;i++){
        if(a[i]==m) printf(" %d",i);
    }
}
