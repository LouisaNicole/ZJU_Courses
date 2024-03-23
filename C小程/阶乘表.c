#include<stdio.h>
double fact(int n); /*自定义函数的声明 */ 
int main(void)
{
	int n,i;
	double f;
	printf("Enter n:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		f = fact(i);
		printf("%d!%5.0f\n",i,f);
	}
	return 0;
 } 
 
double fact(int n)/*自定义函数首部*/ 
{
	int i;
	double result;
	result=1;
	for(i=1;i<=n;i++)
	{
		result=result*i;
	}
	return result;/*将结果回送主函数*/ 
}
