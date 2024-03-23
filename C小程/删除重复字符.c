#include<stdio.h>
#define MAX 80
int main(){
    int i=0,j,k,m=0,flag=1;char temp;
    char str[MAX],a[MAX];
    while((str[i]=getchar())!='\n'){
        i++;
    }
    
    for(j=0;j<i;j++){
        for(k=0;k<j;k++){
            if(str[j]==str[k]){flag=0;break;}
        }
        if(flag==1){a[m]=str[j];m++;}
        flag=1;
    }
    a[m]='\0';
    for(i=0;i<m-1;i++){
        for(j=0;j<m-1-i;j++){
            if(a[j]>a[j+1]){temp=a[j];a[j]=a[j+1];a[j+1]=temp;}
        }
    }
    for(j=0;j<m;j++){
        printf("%c",a[j]);
    }
}
/*É¾³ýÖØ¸´×Ö·û±ù´ÓÐ¡µ½´óÅÅÐò*/ 
