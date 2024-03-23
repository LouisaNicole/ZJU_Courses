#include<stdio.h>
int main(void){
	int time1,time2;
	int m1,m2,h1,h2,m3,h3;
	
	scanf("%d%d",&time1,&time2);
	h1=time1/100;h2=time2/100;
	m1=time1%100;m2=time2%100;
	if(m2>=m1){
		m3=m2-m1;
		h3=h2-h1;
	}
	else{
	    m3=m2+60-m1;
		h3=h2-h1-1;
	}
	if(h3<10) printf("0");	
	printf("%d:",h3);
	if(m3<10) printf("0");
	printf("%d",m3);
	return 0;
} 
