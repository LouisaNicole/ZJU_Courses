#include<stdio.h>
#include<math.h>
int main(void)
{
	int n,i;
	double m;
	printf("Enter n:");
	scanf("%d",&n);
	for(i=0;i<=n;i++)
	{
		m=pow(2,i);
		printf(" 2^%d%5.0f\n",i,m);
	}
	return 0;
 } 
