#include<stdio.h>
#include<string.h>
int main(){
	int i,count=0,day,sum=0;
    struct book{
    	int a,hh,mm,t;
    	char b;
        int flag;
	}c[1001]; 
	scanf("%d",&day);
	while(day--){
		count=sum=0;
		while(1){
			scanf("%d",&i);
			getchar();//���ջس� 
			scanf("%c %d:%d",&c[i].b,&c[i].hh,&c[i].mm);//������%c��%d��ո� 
			if(i==0){
				if(count==0) printf("0 0\n");
				else printf("%d %d\n",count,(int)(1.0*sum/count+0.5));//����!!!
				break;
			} 
			if(c[i].b=='S'){
				c[i].flag=1;
				c[i].t=-(c[i].hh*60+c[i].mm);//���ţ��� 
			} 
			if(c[i].b=='E'&&c[i].flag==1){
				count++;
				c[i].t+=c[i].hh*60+c[i].mm;
				sum+=c[i].t;
				c[i].t=c[i].flag=0;
			} 	
		}
	}
    return 0;
}

