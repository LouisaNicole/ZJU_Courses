#include<stdio.h>
#include<string.h>
int main()
{
    int len,i,j,k=0;
    char s[22][15],t[15]={'0'};
    while(1){
        scanf("%s",s[k]);
        if(s[k][0]=='#'){
            break;
        }
        k++;
    }
    s[k][0]='\0';
    for(i=0;i<k;i++)
        for(j=0;j<k-i;j++){
            if(strlen(s[j])>strlen(s[j+1]))
                {
                    strcpy(t,s[j]);
                    strcpy(s[j],s[j+1]);
                    strcpy(s[j+1],t);
                }
        }
    for(i=1;i<=k;i++)
    {
        printf("%s ",s[i]);
    }
    return 0;
}
