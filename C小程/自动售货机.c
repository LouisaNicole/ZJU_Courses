#include<stdio.h>
int main(void)
{
	int choice,i;
	double price;
	printf("[1]select crisps\n");
	printf("[2]select popcorn\n");
	printf("[3]select chocolate\n");
	printf("[4]select cola\n");
	printf("[0]exit\n");
	
	for(i=1;i<=5;i++){
		printf("Enter choice:");
		scanf("%d",&choice);
		if(choice==0)
			break;
		switch(choice){
			case 1: price = 3.0;break; /*case后面记得空格！*/ 
			case 2: price = 10.0;break;
			case 3: price = 15.0;break;
			case 4: price = 5.0;break;
			default : price = 0.0;break;
		}
		printf("price=%0.1f\n",price);
    }
	printf("Thanks\n");
	return 0;
} 
