#include<stdio.h>
int main(void)
{
	printf("****\n***\n**\n*\n");
/*输出倒三角*/ 

	int celsius,fahr;
	fahr = 100;
	celsius = 5 * (fahr - 32) / 9;
	printf("fahr=%d,celsius=%d\n",fahr,celsius);
/*华氏度转换摄氏度*/ 

	int height = 100;
	int t = 3;
	int h;
	h = height -10*t*t/2;
	printf("h=%d",h);
	return 0;
/*计算自由落体*/ 
}
 



