#include<stdio.h>
#include<math.h>
int main(){
    int n,i,j,qidian,count=0,num=0,sum;
    
    scanf("%d",&n);
    for(i=2;i<=sqrt(n);i++){
    	sum=n;
        for(j=i;sum%j==0&&sum!=0;j++){
            sum/=j; num++;
        }
        if(num>count) {
        	qidian=i;count=num;
		} 
        num=0;
    }
    if(count==0) printf("1\n%d",n);
    else{
        printf("%d\n",count);
        for(i=qidian;i<qidian+count;i++){
            if(i==qidian) printf("%d",qidian);
            else printf("*%d",i);
        }
    }
}

/*
一个正整数 N 的因子中可能存在若干连续的数字。
例如 630 可以分解为 3×5×6×7，
其中 5、6、7 就是 3 个连续的数字。
给定任一正整数 N，要求编写程序求出最长连续因子的个数，
并输出最小的连续因子序列。

输入格式：
输入在一行中给出一个正整数 N（1<N<2^31）。
输出格式：
首先在第 1 行输出最长连续因子的个数；
然后在第 2 行中按 因子1*因子2*……*因子k 的格式输出最小的连续因子序列，
其中因子按递增顺序输出，1 不算在内。 
*/
