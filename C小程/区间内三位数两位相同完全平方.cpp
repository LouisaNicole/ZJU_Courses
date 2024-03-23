#include <stdio.h>
#include <math.h>
int search( int n );
int main()
{
    int number;
    scanf("%d",&number);
    printf("count=%d\n",search(number)); 
    return 0;
}

//本题要求实现一个函数，
//统计给定区间内的三位数中有两位数字相同的完全平方数的个数 
/* 你其中传入的参数int n是一个三位数的正整数（最高位数字非0）
函数search返回[101, n]区间内所有满足条件的数的个数 */

int search( int n ){
    int i,a,b,c,num=0;;
    double m;
    for(i=101;i<n;i++){
    	m=sqrt(i);
        a=i/100;b=i/10%10;c=i%10;
    	if((m==(int)m)&&(a==b||a==c||b==c)) num++;
	}
    return num;
}
/*方法二
int search( int n ){
    int a[10]={0},i,j,flag=0,num=0;
    if(n<121) return num;
    else{
        for(i=11;i<32;i++,num++){
            if(n<i*i) break;
            a[i*i/100]++;a[i*i/10/10]++;a[i*i%100%10]++;
            for(j=0;j<10;j++){
                if(a[j]==2) flag=1;
            }
            if(flag==1) num--;
            flag=0;
        }
    }
    return num;
}*/ 
