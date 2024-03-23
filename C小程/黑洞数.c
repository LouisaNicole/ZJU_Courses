#include<stdio.h>
int main(void){
    int a,b,c,number,temp,count;count=0;
    scanf("%d",&number);
    do{
        a=number/100;b=number/10%10;c=number%100%10;
        if(a<b){temp=a;a=b;b=temp;}
        if(a<c){temp=a;a=c;c=temp;}
        if(b<c){temp=b;b=c;c=temp;}
        number=100*a+10*b+c-100*c-10*b-a;
        count++;
        printf("%d: %d - %d = %d\n",count,100*a+10*b+c,100*c+10*b+a,number);
    }while(number!=495);
}/*黑洞数也称为陷阱数，又称“Kaprekar问题”，是一类具有奇特转换特性的数。

任何一个各位数字不全相同的三位数，经有限次“重排求差”操作，总会得到495。最后所得的495即为三位黑洞数。所谓“重排求差”操作即组成该数的数字重排后的最大数减去重排后的最小数。（6174为四位黑洞数。）

例如，对三位数207：

第1次重排求差得：720 - 27 ＝ 693；
第2次重排求差得：963 - 369 ＝ 594；
第3次重排求差得：954 - 459 ＝ 495；
以后会停留在495这一黑洞数。如果三位数的3个数字全相同，一次转换后即为0。

任意输入一个三位数，编程给出重排求差的过程。*/
