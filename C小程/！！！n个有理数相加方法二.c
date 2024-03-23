#include<stdio.h>
#include<math.h>
long long int zhanzhuan(long long int m,long long int n);

int main(){
	int n,i,flag=1;
    long long int x1,x2,y1,y2,d,sum1,sum2;
    scanf("%d",&n);
    scanf("%lld/%lld",&x1,&y1);
    
    for(i=1;i<n;i++){
        scanf("%lld/%lld",&x2,&y2);
        d=zhanzhuan(y1,y2);
        sum2=y1/d*y2;
        sum1=y2/d*x1+y1/d*x2;
        if(sum1<0) {flag=-1;sum1=-sum1;}
        d=zhanzhuan(sum1,sum2);
        x1=flag*sum1/d;
        y1=sum2/d;
    }
    if(x1%y1==0) printf("%lld",x1/y1);
    else if(fabs(x1)<y1) printf("%lld/%lld",x1,y1);
    else printf("%lld %lld/%lld",x1/y1,x1-x1/y1*y1,y1);
}

long long int zhanzhuan(long long int m,long long int n){
    while(m!=n){
        if(m==0||n==0) return 1;
        if(m>n) m=m-n;
        else n=n-m;
    }
    return m;
}
