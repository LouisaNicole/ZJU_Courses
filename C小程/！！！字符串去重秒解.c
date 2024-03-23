#include<stdio.h>
int main(){
    int i,d[257]={0};
    char s[80],*p;
    gets(s);p=s;
    while((*p)!='\0'){
        d[*p]++;
        p++;
    }
    for(i=0;i<80;i++){
        if(d[s[i]]>0){
        	printf("%c",s[i]);
        	d[s[i]]=0;
		}
    }
}
