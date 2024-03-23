#include<stdio.h>
int m(int a,int b);
int main(void){
	int i,n,min,a,b;
	scanf("%d",&n);
	scanf("%d",&a);
    for(i=1;i<=n-1;i++){
	    scanf("%d",&b);
        min=m(a,b);
	    a=min;
	    }
	printf("min = %d",a);
} 
int m(int a,int b){
	int min;
	if(a<b) min=a;
	else min=b;
	return min;
}
