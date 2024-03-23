#include <stdio.h>
#define MAXN 20

void CountOff( int n, int m, int out[] );

int main()
{
    int out[MAXN], n, m;
    int i;
    
    scanf("%d %d", &n, &m);
    CountOff( n, m, out );   
    for ( i = 0; i < n; i++ )
        printf("%d ", out[i]);
    printf("\n");
     
    return 0;
}

/* 你的代码将被嵌在这里 */

void CountOff( int n, int m, int out[] ){
    int count=1,i,j;
    for(i=0;i<n;i++){
        out[i]=0;
    }
    i=j=0;
    while(count<=n){
        if(out[i%n]==0){j++;}//报数j 
        if(j==m){out[i%n]=count;count++;j=0;}//重置j并且记录 
        i++;
    }
}
