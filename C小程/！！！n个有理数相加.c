#include<stdio.h>
int gcd(long long int m,long long int n); /*���Լ��*/ 
int lcm(long long int m,long long int n); /*��С������*/ 
int main(){
    long long int a1,b1,a2,b2,c1,c2,d,e;
    int i=1,k;
    scanf("%d",&k);
	scanf("%lld/%lld",&a1,&b1);
	long long int t=gcd(a1,b1);
	if(t!=0){
		a1/=t;b1/=t;/*Լ�ֵ�һ����*/ 
	}
	while(i<k){
		scanf("%lld/%lld",&a2,&b2);
		c2=lcm(b1,b2);/*����������������*/ 
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
    if(m==0) return n;/*������Ϊ��ʱ�����Լ��Ϊ��ĸ��ֵ*/ 
}
int lcm(long long int m,long long int n){
    return m/gcd(m,n)*n;
}
/*������N�����ֵĺ�.��Щ������������������/��ĸ����ʽ�����ģ�������ĺ�Ҳ����������������ʽ��
�����һ�и���һ��������N����100�������һ�а���ʽa1/b1 a2/b2 ...����N����������
��Ŀ��֤���з��Ӻͷ�ĸ���ڳ����ͷ�Χ�ڡ����⣬�����ķ���һ�������ڷ���ǰ�档
����������ֺ͵������ʽ ���� �������д����������/��������
���з�������д�ɷ���/��ĸ��Ҫ�����С�ڷ�ĸ��������û�й����ӡ�����������������Ϊ0����ֻ����������֡�*/
