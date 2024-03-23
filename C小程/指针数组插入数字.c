//在字符串 str 中找出最大的字符，将在该字符前的所有字符往后顺序移动一位，再把最大字符放在字符串的第一个位置上。如"knowledge"变成"wknoledge"。

#include <stdio.h>
int main()
{
    char max, str[80], *p, *q;  
    p = str; //取首地址 
    gets(p); 
    max = *p;
    p++;
    while ( *p != '\0' )
	{
        if ( max < *p ){ 
            max = *p; 
            q=p; //取最大值的地址 
        }
        p++;
    }
    p = q;
    while (p!=str)  {
        *p = *(p-1); //向后移位 
        *p--; 
    }
    *p = max;
    puts(p);
    
    return 0;
}
