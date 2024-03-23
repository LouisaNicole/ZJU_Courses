#include<stdio.h>
int main(void)
{
	int fahr,lower,upper;
	double celsius;
	printf("Enter lower upper£º"); 
	scanf("%d%d",&lower,&upper);
	if(lower<upper)
	{
		printf("fahr&celsius\n");
		for(fahr=lower;fahr<upper;fahr++)
		{
			celsius=5*(fahr-32)/9;
			printf("%4d%6.1f\n",fahr,celsius);
		}
	 } 
	else{
		printf("Error");
	}
	return 0;
 } 
