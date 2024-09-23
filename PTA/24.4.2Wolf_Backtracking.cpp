#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int N, M, L; // N是总玩家，M是狼，L是撒谎人数
int flag = 0; // 标志位是否找到一种解法
int inputs[103], wolfs[103] = {0}; // inputs是玩家说的话，wolfs是狼的下标(0表示不是浪,1表示是狼)
vector<int> result;

void Wolf(int N, int M, int L);
void DFS(int idx, int M, int L);

int main(){
    scanf("%d %d %d", &N, &M, &L);
    for(int i = 1; i <= N; i++){
        scanf("%d", &inputs[i]);
    }
    for(int i = N; i >= M; i--){
        DFS(i, M, L);
        if(flag) break;
    }
    if(!flag) printf("No Solution");
}

void Wolf(int N, int M, int L){
    int total_lie = 0, wolf_lie = 0;
    for(int i = 1; i <= N; i++){
        if((inputs[i]>0 && wolfs[abs(inputs[i])]==1) || (inputs[i]<0 && wolfs[abs(inputs[i])]==0)){
            // 说是狼但事实是人 或者 说是人但事实是狼，即记录谎话数量
            total_lie++;
            if(wolfs[i]==1){ // 狼说的谎话数量增加
                wolf_lie++;
            }
        }
        if(total_lie > L) return; // 谎话数量超了但是不满足其他约束，剪枝回溯
    }
    if((total_lie==L) && (wolf_lie>0) && (wolf_lie<M)){ // 找到了一种结果
        flag = 1;   
        printf("%d", result[0]);
        for(int i = 1; i < M; i++){
            printf(" %d", result[i]);
        }
    }
    return;
}

void DFS(int idx, int M, int L){
    if(result.size() == M){ // 已经找到足够数量的狼，剪枝
        Wolf(N, M, L);
        return;
    }
    if(idx == 0){ // 已经遍历完所有玩家
        return;
    }
    // 选当前玩家作为狼
    result.push_back(idx);
    wolfs[idx] = 1;
    // 不选当前玩家作为狼
    DFS(idx-1, M, L);
    if(!flag){
        wolfs[idx] = 0;
        result.pop_back(); 
        if(result.size() == 0) return;
        DFS(idx-1, M, L); // 继续尝试下一个玩家
    }
    return;
}
