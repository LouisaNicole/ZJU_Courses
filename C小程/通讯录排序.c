#include<stdio.h>
struct book {
    char name[11];
    int birth;
    char dial[18];
};
int main(){
    int i,n,j;
    scanf("%d",&n);
    struct book a[n],temp;
    for(i=0;i<n;i++){
        getchar();
        scanf("%s%d%s",a[i].name,&a[i].birth,a[i].dial);
    }
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(a[j].birth>a[j+1].birth){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%s %d %s\n",a[i].name,a[i].birth,a[i].dial);
    }
}
//按照年龄从大到小的顺序依次输出通讯录 
