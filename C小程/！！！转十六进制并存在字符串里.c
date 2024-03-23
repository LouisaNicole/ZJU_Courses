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
            *p++='-';//判断负数降低一个字符改成负号 
            flag=1;
        }
		*p++=k[i]<10?k[i]+'0':k[i]-10+'A';//逐个输入字符 
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


//其中x是待转化的十进制长整数，
//p指向某个字符数组的首元素。
//函数f的功能是把转换所得的16进制字符串写入p所指向的数组。
//16进制的A~F为大写字母。 

void f( long int x, char *p )
{
  int i;
  int n;  //记录x原值
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
