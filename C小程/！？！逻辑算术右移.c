#include<stdio.h>
unsigned srl(unsigned x,int k);
unsigned sra(int x,int k);
int main(){
	int x,k,p,q; 
	scanf("%u%d",&x,&k);
	p=srl(x,k);
	q=sra(x,k);
    printf("%d\n",p);
    printf("%d\n",q);
}

unsigned srl(unsigned x,int k)
{
	unsigned xsra=(int)x>>k;
    int w = 8*sizeof(int);
	unsigned sign = x >> (w-1);
	xsra = xsra & (-1 >> k);
	return sign << (w-1) | xsra;

}
unsigned sra(int x,int k)
{
	unsigned xsrl=(unsigned)x>>k;
    int w2 = 8*sizeof(int);
    unsigned sign2 = x >> (w2-1);
	xsrl = xsrl | (-sign2 << (w2-k));
	return xsrl;
	

}

