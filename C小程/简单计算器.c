#include<stdio.h>
int main(){
    int a,b,sum,flag;flag=1;
    char ch;
    scanf("%d%c",&a,&ch);sum=a;
    while(ch!='='){
        switch(ch){
            case '+':scanf("%d",&b);sum=sum+b;break;
            case '-':scanf("%d",&b);sum=sum-b;break;
            case '*':scanf("%d",&b);sum=sum*b;break;
            case '/':scanf("%d",&b);
                if(b==0){flag=0;}
                else sum=sum/b;break;
            default:flag=0;break;}
        ch=getchar();
    }
    if(flag==1){
    	printf("%d",sum);
	}else{
		printf("ERROR");
	}
}
