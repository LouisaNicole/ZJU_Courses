#include<stdio.h>
#include<string.h>
int main(){
    char s[5][80],min[80]; //用二维数组 
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
//输入为由空格分隔的5个非空字符串，
//每个字符串不包括空格、制表符、换行符等空白字符，长度小于80。
