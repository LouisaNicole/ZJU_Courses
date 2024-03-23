#include<stdio.h>
#include<math.h>
int choice(char a[],int n);
int main(){
    int i,n,m;
    scanf("%d%d",&n,&m);
    char a[n];int b[m];
    getchar();
    for(i=0;i<m;i++){
        gets(a);
        b[i]=choice(a,n);
    }
    for(i=0;i<m;i++){
        printf("%d\n",b[i]);
    }
}
int choice(char *p,int n){
    int left=1,right=pow(2,n),mid,i=0;
    for(i=0;i<n;i++){
        mid=(left+right)/2;
        if(*(p+i)=='y'){
            right=mid;
        }
        else if(*(p+i)=='n'){
            left=mid+1;
        }
    }
    return left;
}

