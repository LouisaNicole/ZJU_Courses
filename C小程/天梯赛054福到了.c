#include<stdio.h>
int main(){
    int i,j,n,flag=0;
    char ch;
    scanf("%c %d",&ch,&n);
    getchar();
    int a[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i][j]=getchar();
            if(a[i][j]!=' ') a[i][j]=ch;
        }
        getchar();
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]!=a[n-i-1][n-j-1]){
            	flag=1;break;
			}
        }
    }
    if(flag==0) printf("bu yong dao le\n");
    for(i=n-1;i>=0;i--){
        for(j=n-1;j>=0;j--){
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
}
