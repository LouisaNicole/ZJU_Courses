#include<stdio.h>
int main(void){
	int i,n,digital,letter,other;
	char ch;
	printf("Enter n:");
	scanf("%d",&n);
	digital=letter=other=0;
	getchar();/*舍弃换行符*/ 
	printf("Enter %d characters:",n);
	
    for(i=1;i<=n;i++){
		ch=getchar();      /*逐个输入字符*/
		if(ch>='1'&&ch<='9'){         /*别忘了单引号！*/
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

