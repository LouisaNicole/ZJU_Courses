#include<stdio.h>
int main(void){
	int n,a,b,c,f;
	scanf("%d",&n);
	a=n/100;
	b=n/10%10;
	c=n%10;
	f=100*c+10*b+a;
	printf("%d",f);
	return 0;
}
