#include<stdio.h>
#include<math.h>
int main(void){
	long n,i;
	double s=0,y,h;
	scanf("%lf%ld",&h,&n);
	if(n==1){
		s=h;y=h/2.0;
	}
    else if(n==0) {s=0;y=0;}
	else if(n>1)
	{
		for(i=1;i<=n-1;i++){
			s=s+h*(pow(0.5,i-1));
		}
        y=h*(pow(0.5,n));
        s=s+h;
	}
	printf("%.1f %.1f",s,y);
}
