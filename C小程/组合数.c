#include<stdio.h>
double fact(int t);
int main(void)
{
	int m,n;
	double a,b,c,result;
	printf("Enter m & n:");
	scanf("%d%d",&m,&n);
	if(m<=n){
		a=fact(n);
	    b=fact(m);
	    c=fact(n-m);
	    result=a/(b*c);
	    printf("×éºÏÊýC%d%d=%.0f",m,n,result); 
	}
	else{
		printf("´íÎó"); 
	}
	return 0;
 } 

double fact(int n)
{
	int i;
	double product;
	product = 1;
	for(i=1;i<=n;i++){
		product=product*i;
	}
	return product;
}
