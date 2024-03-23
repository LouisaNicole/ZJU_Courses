#include<stdio.h>
int main(void){
    int right,guess,n,i,flag;flag=0;
    scanf("%d%d",&right,&n);
    for(i=1;i<=n;i++){
        scanf("%d",&guess);
        if(guess<0){break;}
        else if(guess>=0){
            if(guess<right){printf("Too small\n");}
            else if(guess>right){printf("Too big\n");}
            else if(guess==right){
                if(i==1){printf("Bingo!");flag=1;break;}
                else if(i>1&&i<=3){printf("Lucky You!\n");flag=1;break;}
                else if(i>3){printf("Good Guess!\n");flag=1;break;}
            }
        }
    }
    if(flag==0){printf("Game Over");}
    return 0;
}
