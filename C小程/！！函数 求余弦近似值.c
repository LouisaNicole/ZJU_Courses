#include <stdio.h>
#include <math.h>

double funcos( double e, double x );

int main()
{    
    double e, x;

    scanf("%lf %lf", &e, &x);
    printf("cos(%.2f) = %.6f\n", x, funcos(e, x));
    
    return 0;
}

/* 你的代码将被嵌在这里 */
double funcos( double e, double x )
{
	double result=1,sum=0,dec=1;
	int i=1,flag=-1;
	do{
		sum+=result;
        dec=(i*2-1)*(2*i)*dec;
        result=flag*pow(x,2*i)/dec;
        i++;flag=-flag;
	}while(fabs(result)>=e);
    sum+=result;
	return sum;
}
