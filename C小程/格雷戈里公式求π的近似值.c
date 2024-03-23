#include<stdio.h>
#include<math.h> 
int main(void){
	int i,flag,n;
	double eps,sum,item;
	printf("Enter your eps:");
	scanf("%lf",&eps);
	i=1;n=1;item=1;sum=0;flag=1;
	while(fabs(item)>=eps){
		sum=sum+item;
		i++;
		n=n+2;
		flag=-flag;
		item=flag*(1.0/n);
	}
	sum=sum+item;
	sum=sum*4;
	printf("¦Ð=%f",sum);
	return 0;
} 
