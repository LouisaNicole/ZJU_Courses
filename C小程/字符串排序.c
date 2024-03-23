#include<stdio.h>
#include<string.h>
int main(){
    char s[5][80],min[80];
    int i,j;
    for(i=0;i<5;i++){
        scanf("%s",&s[i]);
    }
    for(i=1;i<5;i++){
        for(j=0;j<5-i;j++){
            if(strcmp(s[j],s[j+1])>0){
                strcpy(min,s[j]);
                strcpy(s[j],s[j+1]);
                strcpy(s[j+1],min);
            }
        }
    }
    printf("After sorted:\n");
    for(i=0;i<5;i++){
        printf("%s\n",s[i]);
    }
    return 0;
}
