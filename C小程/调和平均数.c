#include<stdio.h>
int main(void){
	int i,n;
	double sum=0;
	double f,number;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
    	scanf("%lf",&number);
    	sum=sum+1.0/number;
	}
    f=1.0/(sum/n);
    printf("%.2f",f);
    return 0;
}
