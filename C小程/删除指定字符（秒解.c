#include <stdio.h>
#define MAXN 20

void delchar( char *str, char c );
void ReadString( char s[] ); /* �ɲ���ʵ�֣���ȥ���� */

int main()
{
    char str[MAXN], c;

    scanf("%c\n", &c);
    ReadString(str);
    delchar(str, c);
    printf("%s\n", str);
    
    return 0;
}

/* ��Ĵ��뽫��Ƕ������ */

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

