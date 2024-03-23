#include<stdio.h>
int main(){
    int m,n,max;
    scanf("%d%d",&m,&n);
    int a=m,b=n;
    while(a!=b){
        while(a>b){a=a-b;}
        while(a<b){b=b-a;}
    }
    max=a;
    a=m/max;b=n/max;
    printf("%d %d",max,max*a*b);
}
