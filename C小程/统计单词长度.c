
#include<stdio.h>
int main(){
    int num=0,count=0;char ch;/*count�����ų�ȫ�����*/ 
    do{
        ch=getchar();
        while(ch==' '){ch=getchar();}/*��ͷ�ǿո�*/ 
        while(ch!=' '&&ch!='\n'){
            num++,count++;ch=getchar();
        }
        if(num!=0) printf("%d ",num);
        num=0;
    }while(ch!='\n');
    if(count==0) printf("0 ");
}
