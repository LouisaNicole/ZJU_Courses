
#include<stdio.h>
int main(){
    int num=0,count=0;char ch;/*count用于排除全零情况*/ 
    do{
        ch=getchar();
        while(ch==' '){ch=getchar();}/*开头是空格*/ 
        while(ch!=' '&&ch!='\n'){
            num++,count++;ch=getchar();
        }
        if(num!=0) printf("%d ",num);
        num=0;
    }while(ch!='\n');
    if(count==0) printf("0 ");
}
