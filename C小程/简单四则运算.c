#include<stdio.h>
int main(void)
{
	double a,b;
	char op;
	printf("type in a expression:");
	scanf("%lf%c%lf",&a,&op,&b);
	if(op=='+'){
		printf("=%f",a+b);
	}
	else if(op=='-'){
		printf("=%f",a-b);
	}
	else if(op=='*'){
		printf("=%f",a*b); 
	}
	else if(op=='/'){
		printf("=%f",a/b);
	}
	return 0;
}
