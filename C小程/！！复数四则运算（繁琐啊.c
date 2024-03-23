#include<stdio.h>
#include<math.h>
 
void Print(double a1,double b1,double a2,double b2,char c,double x,double y)
{
    if (b1 >= 0 && b2 >= 0)         	  //对复数符号的处理
		printf("(%.1lf+%.1lfi) %c (%.1lf+%.1lfi) = ", a1, b1,c, a2, b2);
	else if (b1 > 0 && b2 < 0)
		printf("(%.1lf+%.1lfi) %c (%.1lf%.1lfi) = ", a1, b1,c, a2, b2);
	else if (b1 < 0 && b2 > 0)
		printf("(%.1lf%.1lfi) %c (%.1lf+%.1lfi) = ", a1, b1,c, a2, b2);
	else if (b1 < 0 && b2 < 0)
		printf("(%.1lf%.1lfi) %c (%.1lf%.1lfi) = ", a1, b1,c, a2, b2);
 
	if (fabs(x) < 0.05) {
		if (fabs(y) < 0.05)        
            printf("0.0\n");
		else printf("%.1lfi\n", y);
	}
	else if (fabs(y) < 0.05)
        printf("%.1lf\n", x);
	else {	                            
		if (y > 0) printf("%.1lf+%.1lfi\n", x, y);
		else printf("%.1lf%.1lfi\n", x, y);
    }
}
 
//加
void add(double a1,double b1,double a2,double b2)
{
    double x,y;
    x = a1 + a2;
    y = b1 + b2;
    Print(a1,b1,a2,b2,'+',x,y);
}
//减
void sub(double a1,double b1,double a2,double b2)
{
    double x,y;
    x = a1 - a2;
	y = b1 - b2;
	Print(a1,b1,a2,b2,'-',x,y);
}
 
//乘
void mul(double a1,double b1,double a2,double b2)
{
    double x,y;
    x = a1*a2 - b1*b2;
	y = a1*b2 + a2*b1;
	Print(a1,b1,a2,b2,'*',x,y);
}
 
//除
void div(double a1,double b1,double a2,double b2)
{
    double x,y;
    x = (a1*a2 + b1*b2)/(a2*a2+b2*b2);
	y = (-a1*b2 + a2*b1)/(a2*a2+b2*b2);     
	Print(a1,b1,a2,b2,'/',x,y);
}
 
int main()
{
    double a,b,c,d;
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
    add(a,b,c,d);
    sub(a,b,c,d);
    mul(a,b,c,d);
    div(a,b,c,d);
    return 0;
}
