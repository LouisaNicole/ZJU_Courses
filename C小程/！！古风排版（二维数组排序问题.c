#include<stdio.h>
int main(){
    int n,i=0,j,count=0,num=0;
    char s[5000];
    scanf("%d",&n);
    getchar();
    while((s[i]=getchar())!='\n'){
        i++;count++;
    }
    s[i]='\0';
    if(count%n==0) count--;
    char a[101][1001];
    for(i=count/n;i>=0;i--){
        for(j=0;j<n;j++){
            if(s[num]!='\0') a[j][i]=s[num];//µ¹ÐòÊä³ö
            else a[j][i]=' ';
            num++;
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<count/n+1;j++){
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
}
/*¹Å·çÅÅ°æ
4
This is a test case

asa T
st ih
e tsi
 ce s
*/ 
 
