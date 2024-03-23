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

/*更好的方法不用指针

#include <stdio.h>
int main()
{
    int i = 0, j;
    static char str[1001];
    while ((str[i++] = getchar()) != '\n');//读入直至换行
    i = 0;
    j = 0;
    while (str[i + 1] != '\0') {//当为结束符时停止
        if (str[i] == '6')//当为6时计算有多少个6，注意，输入是字符‘6’不是数字6
            for (j = i; str[j] == '6'; j++);
        if (j - i > 3 && j - i <= 9) {//判断6数，记得清零j
            printf("9");
            i = j;//当符合条件替换，则输出位应跳过这些用过的6位
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
