#include<stdio.h>
int main(){
    int count=0,i;
    char s[1001],*p=s;
    gets(s);
    while(*p!='\0'){
        while(*p=='6'){
            if(*(p-1)!='6') count=1;
            else if(*(p-1)=='6') count++;
            p++;
        }
        if(count>3&&count<=9){
            *(p-count)='9';
            for(i=count-1;i>0;i--){
                *(p-i)='#';
            }
            p--;
            count=0;
        }
        else if(count>9){
            *(p-count)='2';*(p-count+1)='7';
            for(i=count-2;i>0;i--){
                *(p-i)='#';
            }
            p--;
            count=0;
        }
        p++;
    }
    p=s;
    while(*p!='\0'){
        if(*p!='#') printf("%c",*p);
        p++;
    }
}

/*���õķ�������ָ��

#include <stdio.h>
int main()
{
    int i = 0, j;
    static char str[1001];
    while ((str[i++] = getchar()) != '\n');//����ֱ������
    i = 0;
    j = 0;
    while (str[i + 1] != '\0') {//��Ϊ������ʱֹͣ
        if (str[i] == '6')//��Ϊ6ʱ�����ж��ٸ�6��ע�⣬�������ַ���6����������6
            for (j = i; str[j] == '6'; j++);
        if (j - i > 3 && j - i <= 9) {//�ж�6�����ǵ�����j
            printf("9");
            i = j;//�����������滻�������λӦ������Щ�ù���6λ
            j = 0;
        }
        else if (j - i > 9) {
            printf("27");
            i = j;
            j = 0;
        }
        else j = 0;
        putchar(str[i++]);
    }
    return 0;
}*/ 
