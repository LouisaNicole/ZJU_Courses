#include<stdio.h>
struct book{
    char name[31];
    double price;
};

int main(){
    int n,i,min,max;
    scanf("%d",&n);
    struct book a[n];
    for(i=0;i<n;i++){
        getchar();//������һ����Ŀ�����ջس���ֹ�س��ַ������һ�������� 
        gets(a[i].name);
        scanf("%lf",&a[i].price);
    }
    min=max=0;
    for(i=0;i<n;i++){
        if(a[i].price>a[max].price) max=i;
        if(a[i].price<a[min].price) min=i;
    }
    printf("%.2f, %s\n",a[max].price,a[max].name);
    printf("%.2f, %s",a[min].price,a[min].name);
}
