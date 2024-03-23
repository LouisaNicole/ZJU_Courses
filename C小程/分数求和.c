#include<stdio.h>
int main(void)
{
	int i,flag,n,item;
	double sum;
	flag=1;
	sum=0;
	printf("Enter n=");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		item=2*i-1;
		sum=sum+flag*1.0/item;
		flag=-1*flag;
	 } 
	printf("sum=%f",sum);
	return 0;
 } 
