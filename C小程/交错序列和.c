#include<stdio.h>
int main(void){
	int i,n,digital,letter,other;
	char ch;
	printf("Enter n:");
	scanf("%d",&n);
	digital=letter=other=0;
	getchar();/*�������з�*/ 
	printf("Enter %d characters:",n);
	
    for(i=1;i<=n;i++){
		ch=getchar();      /*��������ַ�*/
		if(ch>='1'&&ch<='9'){         /*�����˵����ţ�*/
			digital++;
		}
		else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
			letter++;
		}
		else{
			other++;
		}
	}
	printf("digital=%d,letter=%d,other=%d",digital,letter,other);
	return 0;
}

