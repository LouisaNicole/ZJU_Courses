#include<stdio.h>
#include<math.h>
int main(){
    int n,i,j,qidian,count=0,num=0,sum;
    
    scanf("%d",&n);
    for(i=2;i<=sqrt(n);i++){
    	sum=n;
        for(j=i;sum%j==0&&sum!=0;j++){
            sum/=j; num++;
        }
        if(num>count) {
        	qidian=i;count=num;
		} 
        num=0;
    }
    if(count==0) printf("1\n%d",n);
    else{
        printf("%d\n",count);
        for(i=qidian;i<qidian+count;i++){
            if(i==qidian) printf("%d",qidian);
            else printf("*%d",i);
        }
    }
}

/*
һ�������� N �������п��ܴ����������������֡�
���� 630 ���Էֽ�Ϊ 3��5��6��7��
���� 5��6��7 ���� 3 �����������֡�
������һ������ N��Ҫ���д���������������ӵĸ�����
�������С�������������С�

�����ʽ��
������һ���и���һ�������� N��1<N<2^31����
�����ʽ��
�����ڵ� 1 �������������ӵĸ�����
Ȼ���ڵ� 2 ���а� ����1*����2*����*����k �ĸ�ʽ�����С�������������У�
�������Ӱ�����˳�������1 �������ڡ� 
*/
