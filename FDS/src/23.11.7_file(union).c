#include<stdio.h>

void input(int S[], int c1, int c2);
void check(int S[], int c1, int c2, int flag[]);
int find(int S[],int x);

int main(){
    int N, i, c1, c2;
    char format;
    scanf("%d", &N);
    int S[N], flag[10001]={0};
    for(i=0; i<N; i++){
        S[i] = -1;          //初始化都是根节点
        // flag[i] = -1;
    }
    getchar();          //回收回车符
    while((format=getchar())!='S'){
        if(format=='I') {
            scanf("%d%d", &c1, &c2); 
            input(S, c1, c2);
        }
        else if(format=='C') {
            scanf("%d%d", &c1, &c2); 
            check(S, c1, c2, flag);
        }
    }
    if(format=='S'){
        i = 0;
        while(flag[i] != 0){
            if(flag[i] == 1){
                printf("yes\n");
            }
            else if(flag[i] == -1){
                printf("no\n");
            }
            i++;
        }

        i = 0;
        int connection = 0;
        for(i=0; i<N; i++){
            if(S[i] < 0) connection++;
        }
        if(connection == 1) printf("The network is connected.");
        else printf("There are %d components.",connection);
    }
}

void input(int S[], int c1, int c2){
    int root1 = find(S, c1-1);
	int root2 = find(S, c2-1);
    if(root1 != root2){
        if(S[root1] == S[root2]){
            S[root1] += S[root2];
            S[root2] = root1;
        }
        else if(S[root1] < S[root2]){
            S[root1] += S[root2];
            S[root2] = root1;
        }
        else{
            S[root2] += S[root1];
            S[root1] = root2;
        }
    }

}

void check(int S[], int c1, int c2, int flag[]){
    static int cnt = 0;
    int root1 = find(S, c1-1);
	int root2 = find(S, c2-1);
    if(root1 == root2){
		flag[cnt++] = 1;
        // printf("yes\n");
	}
    else{
        flag[cnt++] = -1;
        // printf("no\n");
    }
}

int find(int S[], int x)
{
	if(S[x] < 0) return x;
	else return S[x] = find(S, S[x]); 
}