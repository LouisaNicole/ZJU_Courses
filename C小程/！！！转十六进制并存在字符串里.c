#include <stdio.h>
#define MAXN 10

void f( long int x, char *p );

int main()
{
    long int x;
    char s[MAXN] = "";
    
    scanf("%ld", &x);
    f(x, s);
    printf("%s\n", s);
    
    return 0;
}

void f( long int x, char *p ){
	int k[10],i=0;
    int flag=1;
    if(x<0){
        flag=-1;x=-x;
    }
	do{
		k[i++]=x%16;
		x/=16;
	}while(x!=0);
	for(i--;i>=0;i--){
        if(flag==-1&&*p=='\0'){
            *p++='-';//�жϸ�������һ���ַ��ĳɸ��� 
            flag=1;
        }
		*p++=k[i]<10?k[i]+'0':k[i]-10+'A';//��������ַ� 
	}
}


/*
#include <stdio.h>
#define MAXN 10

void f( long int x, char *p );

int main()
{
    long int x;
    char s[MAXN] = "";
    
    scanf("%ld", &x);
    f(x, s);
    printf("%s\n", s);
    
    return 0;
}


//����x�Ǵ�ת����ʮ���Ƴ�������
//pָ��ĳ���ַ��������Ԫ�ء�
//����f�Ĺ����ǰ�ת�����õ�16�����ַ���д��p��ָ������顣
//16���Ƶ�A~FΪ��д��ĸ�� 

void f( long int x, char *p )
{
  int i;
  int n;  //��¼xԭֵ
  int m;
  n = x;
  if (x<0)
  {
     x = -x;
     *p = '-';
     p ++;
  }
  if (x==0)
     *p = '0';
  for (i=0; i<MAXN; i++)
  {
     m = x % 16;
     x = x / 16;
     if (m<MAXN)
        *(p + MAXN - 1 -i) = m + '0';
     else
        *(p + MAXN - 1 -i) = m + 'A' - 10;
     if (x==0)
     {
        m = MAXN - 1 -i;
        break;
     }
  }
  for (i=0; i<MAXN-m; i++)
  {
     *(p + i) = *(p + m + i);
     *(p + m + i) = 0;
  }
}*/
