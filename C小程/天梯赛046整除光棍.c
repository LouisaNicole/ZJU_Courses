#include<stdio.h>
int main(){
    int x,n=1,number=1;
    scanf("%d",&x);
    while(number<x){
        number=number*10+1;
        n++;
    }
    while(1){
        printf("%d",number/x);
        if(number%x==0) break;
        else{
            number%=x;
            number=number*10+1;
            n++;
        }
    }
    printf(" %d",n);
}
