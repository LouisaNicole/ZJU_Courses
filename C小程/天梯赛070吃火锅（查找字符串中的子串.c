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
