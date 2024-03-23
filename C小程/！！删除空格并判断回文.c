#include <stdio.h>
#include <string.h>

int main(void)
{
    char ch, s[80], *p, *q;
    int i, j, n;
    
    gets(s);
    p =s;
    while ( *p == ' '){
        p++;
    }
    n = strlen(s);
    q = s+n-1;
    while ( *q == ' '){
        q--;
    }
    while ( p<q && *p ==*q){
        p++;
        q--;
    }
    if ( p<q ){
        printf("NO\n");
    }else{
        printf("YES\n");
    }
    
        return 0;
}
