#include<stdio.h>
#include<string.h>
int main(){
    char a[81],*p;
    int i=0,j=0,start=-1,count=0,num=0;
    gets(a);
    while(strcmp(a,".")!=0){ //记得要用strcpm 
        num++;p=a;
	//查找字符串中的子串用strstr，返回字符串第一次出现子串的地址，找不到返回NULL 
	//若p="wo chi1 huo3 guo1 hao ma" 下面代码返回的是"chi1 huo3 guo1 hao ma"
        if(strstr(p,"chi1 huo3 guo1")!=NULL){ 
            count++;
            if(start<0) start=num;
        }
        gets(a);
    }
    printf("%d\n",num);
    if(start>0) printf("%d %d",start,count);
    else printf("-_-#");
}
