#include<stdio.h>
int gcd(long long int m,long long int n); /*最大公约数*/ 
int lcm(long long int m,long long int n); /*最小公倍数*/ 
int main(){
    long long int a1,b1,a2,b2,c1,c2,d,e;
    int i=1,k;
    scanf("%d",&k);
	scanf("%lld/%lld",&a1,&b1);
	long long int t=gcd(a1,b1);
	if(t!=0){
		a1/=t;b1/=t;/*约分第一个数*/ 
	}
	while(i<k){
		scanf("%lld/%lld",&a2,&b2);
		c2=lcm(b1,b2);/*这里计算两分数相加*/ 
        c1=c2/b1*a1+c2/b2*a2;
        long long int t=gcd(c1,c2);
        if(t!=0){
        	a1=c1/t;b1=c2/t;
		}
		i++;
	}
    d=a1/b1;e=a1%b1;
    if(e==0&&d!=0) printf("%d",d);
    if(d==0&&e!=0) printf("%d/%d",e,b1);
    if(e!=0&&d!=0) printf("%d %d/%d",d,e,b1);
    if(e==0&&d==0) printf("0");
}
int gcd(long long int m,long long int n){
	if(m<0) m=-m;
    if(m>0){
        while(m!=n){
            if(m>n) m-=n;
            if(m<n) n-=m;
        }return m;
    }
    if(m==0) return n;/*当分子为零时，最大公约数为分母的值*/ 
}
int lcm(long long int m,long long int n){
    return m/gcd(m,n)*n;
}
/*就是求N个数字的和.这些数字是以有理数分子/分母的形式给出的，你输出的和也必须是有理数的形式。
输入第一行给出一个正整数N（≤100）。随后一行按格式a1/b1 a2/b2 ...给出N个有理数。
题目保证所有分子和分母都在长整型范围内。另外，负数的符号一定出现在分子前面。
输出上述数字和的最简形式 —— 即将结果写成整数部分/分数部分
其中分数部分写成分子/分母，要求分子小于分母，且它们没有公因子。如果结果的整数部分为0，则只输出分数部分。*/
