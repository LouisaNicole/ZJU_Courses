#include<stdio.h>
#include<math.h>
int main(void)
{
	int day;
	double factor,initial,result;
	/*printf("Enter day:");
	scanf("%d",&day);
	printf("Enter factor:");
	scanf("%lf",&factor);
	printf("Enter initial:");
	scanf("%lf",&initial);*/
	printf("Enter day factor initial:");
	scanf("%d%lf%lf",&day,&factor,&initial);
	result = initial*pow(1+factor,day);
	printf("result=%.2f\n",result);
	return 0;
 } 
 
 
