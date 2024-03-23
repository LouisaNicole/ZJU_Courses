#include<stdio.h>
int find(int a[],int b[],int n);//或者int *a也可以 
int main(){
	int a[5]={1,2,3,4,5},b[5]={6,7,8,9,10};
	int result;
	result=find(a,b,5);
    printf("%d",result);
}
int find(int a[],int b[],int n){
	if(n==1) return a[0];
	int mid=n/2;
	if(a[mid]==b[mid]) return a[mid];
	if(a[mid]<b[mid]) return find(a+mid,b,n-mid);
	else return find(a,b+mid,n-mid);
}
