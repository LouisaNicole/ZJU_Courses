/*#include<stdio.h>
int main(void){
	int i1,i2,j1,j2,k1,k2,n;
	
	scanf("%d",&n);
	for(i1=0;i1<(n+1)/2;i1++){
		for(j1=1;j1<=(n-1)/2-i1;j1++){
			printf("  ");
		}
		for(k1=1;k1<=2*i1+1;k1++){
			printf("* ");
		}
		printf("\n");
	}
	for(i2=1;i2<=(n-1)/2;i2++)
	{
		for(j2=1;j2<=i2;j2++)
		{
			printf("  ");
		}
		for(k2=1;k2<=n-2*i2;k2++){
			printf("* ");
		}
		printf("\n");
	}
	return 0;
} */
#include<stdio.h>
int main()
{
    int n,i,j,k,a=2;
    scanf("%d",&n);
    k=n-1;
    for(i=1;i<=n;i++){
     
        for(j=1;j<=k;j++){
           printf(" ");
        }
  //���������ӡ�Ǻ� ��ʼΪ1   n-k����1  ÿ��k��2       �൱��n-k�Ӷ�
        for(j=1;j<=n-k;j++){
            printf("* ");
        }
         
  //��ӡ�°������
        if(k==0){
            a=-a;
        }
  //a=-2
        k-=a;
        printf("\n");
    }
}
