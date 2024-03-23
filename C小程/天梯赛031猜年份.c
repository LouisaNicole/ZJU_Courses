#include<stdio.h>
int main(){
    int a[10]={0},x,n=0,i=0,count=0,num=0;
    char y[5];
    scanf("%s",y);
    while(y[n]) n++;
    if(n<4){
    	for(i=3;i>=4-n;i--) y[i]=y[i-4+n];
    	for(i=0;i<4-n;i++) y[i]='0';
	}
    scanf("%d",&n);
    for(i=0;i<4;i++){
        a[y[i]-'0']++;
    }
    for(i=0;i<10;i++){
        if(a[i]>0) count++;
    }
    while(count!=n){
        count=0;y[3]++;
        if(y[3]>'9'){
            y[3]='0';y[2]++;
            if(y[2]>'9'){
                y[2]='0';y[1]++;
                if(y[1]>'9'){
                    y[1]='0';y[0]++;
                }
            }
        }
        for(i=0;i<4;i++){
            a[y[i]-'0']++;
        }
        for(i=0;i<10;i++){
            if(a[i]>0) count++;
        }
        num++;
        for(i=0;i<10;i++){
            a[i]=0;
        }
    }
    printf("%d %s",num,y);
}

/*fangfa2
#include<stdio.h>
int main()
{
    int y, n, count = 0, cnt = 0;
    scanf("%d %d", &y, &n);
    while (1)
    {
        int flag[10] = { 0 };
        cnt = 0;
        int t = y;
        if (t < 1000)确保前面的0 也算在不同的数字 
        {
            flag[0] = 1;
            cnt++;
        }
        while (t)
        {
            int a = t % 10;
            if (flag[a] == 0)确保前面的0不重复计算 
            {
                flag[a] = 1;
                cnt++;
            }
            t /= 10;
        }
        if (cnt == n)
            break;
        y++;
        count++;
    }
    printf("%d %04d\n", count, y);
    return 0;
}*/
