#include<stdio.h>
#include<math.h>
double prime(int n);
int main(){
    double n,i,k;
    scanf("%lf",&n);
    for(i=2;i<=n/2;i++){
        k=n-i;
		if(prime(i)==1&&prime(k)==1){
            printf("%.0f = %.0f + %.0f\n",n,i,k);
            break;	
    	}
	}	
}

double prime(int n){
	int i,result;
    for(i=2;i<=sqrt(n);i++){
        if(n%i==0){
            result=0;break;
        } result=1;
    }
    return result;
}

