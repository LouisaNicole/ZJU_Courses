#include<stdio.h>
int main(){
    char ch;int c=0;
    do{
        c=0;
        do{
            ch=getchar();
            if(ch>='a'&&ch<='z'&&c==0){
                ch=ch+'A'-'a';
            }
			c++;
			putchar(ch);
        }while(ch!=' '&&ch!='\n');
    }while(ch!='\n');
    
}
