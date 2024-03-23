#include<stdio.h>
int main(){
    char ch;
    do{
        ch=getchar();
        if(ch>='a'&&ch<='z'){
            ch=(ch+1-'a')%26+'A';
        }
        else if(ch>='A'&&ch<='Z'){
            ch=(ch+1-'A')%26+'a';
        }
        putchar(ch);
    }while(ch!='\n');
}
