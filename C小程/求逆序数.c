#include <stdio.h>

int reverse( int number );
    
int main()
{
    int n;

    scanf("%d", &n);
    printf("%d\n", reverse(n));

    return 0;
}

/* 你的代码将被嵌在这里 */

int reverse( int number ){
    int flag=1,s=0;
    if(number<0){flag=-1;number=-number;}
    else{
        int n=number,power=1;
        while(n!=0){
            s=s*10+n%10;
            power*=10;
            n/=10;
        }
    }
    s=s*flag;
    return s;
}
