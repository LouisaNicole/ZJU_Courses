#include<stdio.h>
int main(){
    int i=0,n;
    char a[1000][11];
    while(++i){
        scanf("%s",a[i]);
        if(strcmp(a[i],".")==0) break;//这步一定要用strcmp比较字符串！！ 
    }
    if(i>14) printf("%s and %s are inviting you to dinner...",a[2],a[14]);
    else if(i>2) printf("%s is the only one for you...",a[2]);
    else printf("Momo... No one is for you ...");
}
