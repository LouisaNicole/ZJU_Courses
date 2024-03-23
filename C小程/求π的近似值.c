#include<stdio.h>
int main(){
    double eps,PI=0,item=1.0;int i=1;
    scanf("%le", &eps);
    while(item>=eps)
    {
        PI+=item;
        item=item*i/(2*i+1);
        i++; 
    }
    PI+=item;
    PI*=2;
    printf("PI = %.5f",PI);
    return 0;
}
