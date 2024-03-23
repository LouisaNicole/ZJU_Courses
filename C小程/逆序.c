#include<stdio.h>
int main(void){
	int number;
	printf("Enter a number");
	scanf("%d",&number);
	while(number!=0){
		printf("%d",number%10);
		number=number/10;
	}
	/*do{
		printf("%d",number%10);
		number=number/10;
	}while(number!=0);*/
	
	return 0;
} 
