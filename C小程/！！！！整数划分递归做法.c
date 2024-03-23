#include<stdio.h>
#include<string.h>
#define N 100

void f(int n,int a[],int k)
{           //用数组存储每种划分的数字组合
    int flag=0;
	if(n<=0)
    {
        for(int i=0;i<k-1;i++)  //k为当前位置
        {
            printf("%d+",a[i]);flag=1;
        }
        if(flag==1) printf("%d\n",a[k-1]);
        flag=0;
    }
    for(int i=n;i>0;i--)     
    {
        if(k>0&&a[k-1]<i)  //后面的数字不能大于前面数字
            continue;       //防止重复
        a[k]=i;
        f(n-i,a,k+1);
    }
}
int main()
{
    int n;
    int a[N];
    scanf("%d",&n);
    f(n,a,0);
    return 0;
}
