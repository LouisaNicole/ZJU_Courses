#include <stdio.h>
int fun (int m);
int main (void)
{   
    int n;
    scanf ("%d", &n);
    while (n > 0) {
        if (fun(n)==1) {
            printf("yes\n");
        }else{
            printf("No\n");
        }
        scanf("%d", &n);
    }
    return 0;
}

int fun (int m)
{   
    int cur_digit, old_digit = 10; 
    while(m > 0){
        cur_digit = m % 10;
        if( cur_digit >= old_digit){
            return 0;
        }
        old_digit = cur_digit; m=m/10;
    }
    return 1;
 }/*判断每个数从高位到低位的各位数字是否按值从小到大排列*/
