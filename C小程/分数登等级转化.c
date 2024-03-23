#include<stdio.h>
int main(void){
	double score;
	printf("Enter score:");
	scanf("%lf",&score);
	if(score>=90){
	    printf("A");
	}
	else if(score>=80){
		printf("B");
	}
	else if(score>=70){
		printf("C");
	}
	else if(score>=60){
		printf("D");
	}
	else{
		printf("E");
	}
	return 0 ;
}
