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

/* ��Ĵ��뽫��Ƕ������ */

void CountOff( int n, int m, int out[] ){
    int count=1,i,j;
    for(i=0;i<n;i++){
        out[i]=0;
    }
    i=j=0;
    while(count<=n){
        if(out[i%n]==0){j++;}//����j 
        if(j==m){out[i%n]=count;count++;j=0;}//����j���Ҽ�¼ 
        i++;
    }
}
