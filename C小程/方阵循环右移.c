#include<stdio.h>
int main(){
    int m,n,i,j,temp;
    scanf("%d%d",&m,&n);
    int a[n][n],b[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    m=m%n;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(j<m){
                b[i][j]=a[i][j+n-m];
            }
            else{b[i][j]=a[i][j-m];}
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ",b[i][j]);
        }printf("\n");
    }
}
