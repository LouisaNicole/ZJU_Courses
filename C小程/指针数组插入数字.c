//���ַ��� str ���ҳ������ַ������ڸ��ַ�ǰ�������ַ�����˳���ƶ�һλ���ٰ�����ַ������ַ����ĵ�һ��λ���ϡ���"knowledge"���"wknoledge"��

#include <stdio.h>
int main()
{
    char max, str[80], *p, *q;  
    p = str; //ȡ�׵�ַ 
    gets(p); 
    max = *p;
    p++;
    while ( *p != '\0' )
	{
        if ( max < *p ){ 
            max = *p; 
            q=p; //ȡ���ֵ�ĵ�ַ 
        }
        p++;
    }
    p = q;
    while (p!=str)  {
        *p = *(p-1); //�����λ 
        *p--; 
    }
    *p = max;
    puts(p);
    
    return 0;
}
