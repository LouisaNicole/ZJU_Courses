#include <stdio.h>
#include <math.h>
int search( int n );
int main()
{
    int number;
    scanf("%d",&number);
    printf("count=%d\n",search(number)); 
    return 0;
}

//����Ҫ��ʵ��һ��������
//ͳ�Ƹ��������ڵ���λ��������λ������ͬ����ȫƽ�����ĸ��� 
/* �����д���Ĳ���int n��һ����λ���������������λ���ַ�0��
����search����[101, n]�����������������������ĸ��� */

int search( int n ){
    int i,a,b,c,num=0;;
    double m;
    for(i=101;i<n;i++){
    	m=sqrt(i);
        a=i/100;b=i/10%10;c=i%10;
    	if((m==(int)m)&&(a==b||a==c||b==c)) num++;
	}
    return num;
}
/*������
int search( int n ){
    int a[10]={0},i,j,flag=0,num=0;
    if(n<121) return num;
    else{
        for(i=11;i<32;i++,num++){
            if(n<i*i) break;
            a[i*i/100]++;a[i*i/10/10]++;a[i*i%100%10]++;
            for(j=0;j<10;j++){
                if(a[j]==2) flag=1;
            }
            if(flag==1) num--;
            flag=0;
        }
    }
    return num;
}*/ 
