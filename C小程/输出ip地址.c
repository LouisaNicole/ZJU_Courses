#include<stdio.h>
#include<string.h>
int main(){
    char a[32];
    int i,j,sum=0;
    gets(a);
    for(i=0;i<32;i++){
    	sum=sum*2+(a[i]-'0');
	}
    if((i+1)%8==0){
        if(i+1==8){
            printf("%d",sum);
        }
        else {
            printf(".%d",sum);
        }
    }
    
}
