#include<stdio.h>
int main(){
    int i=0,j,k=0,m=0,flag=0;
    char a[80],b[80],c[80];
    while((a[i]=getchar())!='\n'){
        i++;
    }
    a[i]='\0';
    for(j=0;j<i;j++){
        if(a[j]>='A'&&a[j]<='Z'){
            b[k]=a[j];
            k++;
        }
    }
    b[k]='\0';
    for(j=0;j<i;j++){
        for(k=0;k<j;k++){
            if(b[j]==b[k]){
                flag=1;break;
            }
        }
        if(flag==0){
            c[m]=b[j];m++;
        }
        flag=0; 
    }
    c[m]='\0';
    for(j=0;j<m;j++){
        printf("%c",c[j]);
    }
}
/*·½·¨¶þ
int main()
{
    char sz[80];
    int i=0,a=0;
    int sl[26]={0};
    while((sz[i]=getchar())!='\n')
    {
        if(sz[i]>='A'&&sz[i]<='Z')
        {
            if(sl[sz[i]-65]==0)
            {
                printf("%c",sz[i]);
                sl[sz[i]-65]=1;
                a++;
            }
        }
        i++;
    }
    if(a==0)
    {
        printf("Not Found");
    }
}*/
