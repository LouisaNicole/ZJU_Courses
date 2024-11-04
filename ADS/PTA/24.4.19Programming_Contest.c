#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

/* Your function will be put here */
#include<string.h>
int need_time(const int time[], const int score[], int happy_score, int n){
    int total_score = 0, total_time = 0, i, j;
    for (i = 0; i < n; i++) {                // n 是物品数
        total_time += time[i];
        total_score += score[i];
    }
    int weight = total_score - happy_score;  // 背包重量就是最多可以失去的分数
    if (weight < 0) return -1;
    else {
        int value[weight+1];             // 背包价值就是找最多的time
        memset(value, 0, sizeof(int)*(weight+1));
        for (i = n - 1; i >= 0; i--) { 			 
            for (j = weight; j >= 0; j--) {
                if (j >= score[i] && (value[j-score[i]] + time[i]) >= value[j]) {
                    // 背包还有重量可称并且该物品要放入
                    value[j] = value[j-score[i]] + time[i];
                    // printf("%d ", more_time[j]);
                }
            }
        }
        return (total_time - value[weight]);
    }
}