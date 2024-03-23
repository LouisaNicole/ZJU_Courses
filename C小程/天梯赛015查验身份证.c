#include<stdio.h>
int main(){
    int n,i,j,k,sum=0,flag=1;
    scanf("%d",&n);
    int count=n;
    int z[100]={0};
	char a[n][18];
    int b[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char m[11]={'1','0','X','9','8','7','6','5','4','3','2'}; 
    
    for(i=0;i<n;i++){
        scanf("%s",&a[i]);
    }
    for(i=0;i<n;i++){
        for(j=0;j<17;j++){
            if(a[i][j]>='0'&&a[i][j]<='9') sum+=b[j]*(a[i][j]-'0');
            else {
            	flag=0;break;
			}
        }
        sum=sum%11;
        if(m[sum]!=a[i][17]||!flag){
            count--;z[i]=1;
        }
        sum=0;
        flag=1;
        
    }
    
    if(count==n) printf("All passed");
    else{
    	for(i=0;i<n;i++){
    		if(z[i]==1) {
    			for(k=0;k<18;k++){
    				printf("%c",a[i][k]);
				}printf("\n");
			}
		}
	}
}
