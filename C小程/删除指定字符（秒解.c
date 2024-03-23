#include <stdio.h>
#define MAXN 20

void delchar( char *str, char c );
void ReadString( char s[] ); /* 由裁判实现，略去不表 */

int main()
{
    char str[MAXN], c;

    scanf("%c\n", &c);
    ReadString(str);
    delchar(str, c);
    printf("%s\n", str);
    
    return 0;
}

/* 你的代码将被嵌在这里 */

void delchar( char *str, char c ){
    int new=0;
    int i;
    for(i=0;*(str+i)!='\0';i++);
    for(int j=0;j<=i;j++){
        if(*(str+j)!=c){
            *(str+new)=*(str+j);
            new++;
        }   
    }
}

