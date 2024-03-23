#include<stdio.h>
#include<math.h>
int main(void) 
{
	double x,y;
	printf("Enter x£º");
	scanf("%lf",&x);
	if (x<0)
	{
		y=pow(x+1,2)+2.0*x+1.0/x;
	}
	else
	{
		y=sqrt(x); 
	}
	printf("y=%.2f",y);
	return 0;
}
