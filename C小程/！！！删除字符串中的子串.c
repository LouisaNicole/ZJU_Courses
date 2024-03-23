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
/*

#include<stdio.h>
#include<string.h>
int count=0;
void xunhuan(char *s,char *t);
int main(){
    char s[81],t[81];
    gets(s); 
    gets(t);
    xunhuan(s,t);
    while(count!=0){ //重复循环到没有指定字符 
        count=0;
        xunhuan(s,t);
    }
    puts(s);
}

void xunhuan(char *s,char *t){
    int lenp,lent,i;
    
    lent=strlen(t);
    while(strlen(s)>=lent){
    	for(i=0;i<lent;i++){
    		if(*(t+i)!=*(s+i)) break;//到第一个相同字符的出现 
		}
		if(i<lent){ //如果不是完全相同则跳过后续步骤 
			s++;
			continue;
		}
		lenp=strlen(s);
		count=1;
		for(i=0;i<lenp-lent;i++){
			*(s+i)=*(s+lent+i); //删除相同字符 
		}
		*(s+i)='\0';
	}
}*/


 
