#include<stdio.h>
int main(){
	int n,i,j,num=1,shu=1;
	scanf("%d",&n);
	int a[n][n];
	for(i=n-1;i>0;i-=2){
		for(j=num-1;j<n-num;j++){
			a[num-1][j]=shu++;
		}
		for(j=num-1;j<n-num;j++){
			a[j][n-num]=shu++;
		}
		for(j=n-num;j>=num;j--){
			a[n-num][j]=shu++;
		}
		for(j=n-num;j>=num;j--){
			a[j][num-1]=shu++;
		}
		num++;
	}
	if(n%2==1) a[n/2][n/2]=shu;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%3d",a[i][j]);
		}
		printf("\n");
	}
}
