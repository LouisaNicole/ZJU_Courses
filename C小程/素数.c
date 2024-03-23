#include<stdio.h>
int main(void){
	int m,n,i,j,sum,count;
	sum=count=0;
	scanf("%d%d",&m,&n);
	for(i=m;i<=n;i++){
		j=2;
		while(i%j!=0&&j<=i/2){
			j++;
		}
		if(j==i/2+1){
			count++;
			sum=sum+i;
		}
	}
	printf("%d %d",count,sum);
	return 0;
} 
