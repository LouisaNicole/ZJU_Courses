#include<stdio.h>
int main(void)
{
	int odd,even,i,n,number;
	printf("Enter n = ");
	scanf("%d",&n);
	odd=0;
	even=0;
	printf("Respectively enter %d numbers: ",n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&number);
		if(number%2==0){
			odd++;
		}
		else{
			even++;
		}
	}
	printf("odd:%d\neven:%d",odd,even);
	return 0;
}
