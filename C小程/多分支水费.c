#include<stdio.h>
int main (void)
{
	double x,y;
	printf("Enter x=");
	scanf("%lf",&x);
	if(x<=15)
	{
		if(x<0) y=0;
		else y=4*x/3.0; 
	}
	else{
		y=2.5*x-10.5;
	}
	printf("ˮ��Ϊ%.2fԪ",y);
	return 0;
}
