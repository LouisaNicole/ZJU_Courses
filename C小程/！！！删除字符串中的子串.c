#include<stdio.h>
#include<string.h>
int main(){
    char a[81],*p;
    int i=0,j=0,start=-1,count=0,num=0;
    gets(a);
    while(strcmp(a,".")!=0){ //�ǵ�Ҫ��strcpm 
        num++;p=a;
	//�����ַ����е��Ӵ���strstr�������ַ�����һ�γ����Ӵ��ĵ�ַ���Ҳ�������NULL 
	//��p="wo chi1 huo3 guo1 hao ma" ������뷵�ص���"chi1 huo3 guo1 hao ma"
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
    while(count!=0){ //�ظ�ѭ����û��ָ���ַ� 
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
    		if(*(t+i)!=*(s+i)) break;//����һ����ͬ�ַ��ĳ��� 
		}
		if(i<lent){ //���������ȫ��ͬ�������������� 
			s++;
			continue;
		}
		lenp=strlen(s);
		count=1;
		for(i=0;i<lenp-lent;i++){
			*(s+i)=*(s+lent+i); //ɾ����ͬ�ַ� 
		}
		*(s+i)='\0';
	}
}*/


 
