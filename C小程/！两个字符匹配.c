/*本题要求实现一个函数，对给定的一个字符串和两个字符，打印出给定字符串中
从与第一个字符匹配的位置开始到与第二个字符匹配的位置之间的所有字符。*/
#include <stdio.h>

#define MAXS 10

char *match( char *s, char ch1, char ch2 );

int main()
{
    char str[MAXS], ch_start, ch_end, *p;
    
    scanf("%s\n", str);
    scanf("%c %c", &ch_start, &ch_end);
    p = match(str, ch_start, ch_end);
    printf("%s\n", p);

    return 0;
}

/* 你的代码将被嵌在这里 */

char *match( char *s, char ch1, char ch2 ){
    int i=0;
    int *p;
    while(*s!=ch1&&*s!='\0')
    {
        s++;
    }
    if(*s!='\0') {
        p=s;
        while(1){
            if(*s=='\0') break;
            printf("%c",*s);
            if(*s==ch2){
                break;
            }
            s++;
        }
         printf("\n");
         return p;
    }
    else return "\n";
} 
