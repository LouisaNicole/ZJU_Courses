/*����Ҫ��ʵ��һ���������Ը�����һ���ַ����������ַ�����ӡ�������ַ�����
�����һ���ַ�ƥ���λ�ÿ�ʼ����ڶ����ַ�ƥ���λ��֮��������ַ���*/
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

/* ��Ĵ��뽫��Ƕ������ */

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
