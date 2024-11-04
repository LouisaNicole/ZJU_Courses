#include <iostream>
#include <cstdio>
#include <algorithm>
#include<limits.h>
using namespace std;

int main() {
    int C, N, i, min_index;
    double D, D_avg, D_max;
    scanf("%d %lf %lf %d", &C, &D, &D_avg, &N);
    double Di[N], Di_copy[N], Pi[N], Pi_copy[N];
    D_max = C * D_avg;
    for (i = 0; i < N; i++) {
        scanf("%lf %lf", &Pi[i], &Di[i]);
        Di_copy[i] = Di[i];
        Pi_copy[i] = Pi[i];
    }
    for (i = 0; i < N; i++) {
        min_index = min_element(Di_copy, Di_copy + N) - Di_copy; // 找出最小距离的下标，用来将全部加油站按照相对位置升序排序
        Di[i] = Di_copy[min_index];
        Di_copy[min_index] = INT_MAX;
        Pi[i] = Pi_copy[min_index];
    }
    // for (i = 0; i < N; i++) {
    //     cout << Di[i] << " " << Pi[i] << endl;
    // }
    if (Di[0] != 0) cout << "The maximum travel distance = 0.00"; 
    else{
        double cost = 0, distance = 0, cap = 0;
        if(N == 1){
            if(D > D_max) printf("The maximum travel distance = %.2f", D_max); 
            else cout << Pi[0] * D; 
            return 0;
        }

        i = 1;
        while(i < N){
            if((Di[i] - Di[i-1]) > D_max){
                printf("The maximum travel distance = %.2f", Di[i-1] + D_max); 
                return 0;
            }
            else if((D - Di[N-1]) > D_max && i == N-1){ 
                printf("The maximum travel distance = %.2f", Di[N-1] + D_max); 
                return 0;
            }
            else{
                int cur = i, cur_index = i - 1;
                double min_unit = Pi[i-1];
                while((Di[cur] - Di[i-1]) <= D_max && cur < N){  // 找出所有可到达的加油站
                    if(Pi[cur] <= min_unit){  // 找到油价最低的加油站
                        min_unit = Pi[cur];
                        cur_index = cur;
                    }
                    cur++;
                }
                if(i - 1 == cur_index){  // 如果可达的加油站油价全部比当前加油站高，那么加满油并且去范围内的油价最低（相同油价则最远）的加油站。
                    cur = i, cur_index = cur;
                    min_unit = Pi[i];
                    while((Di[cur] - Di[i-1]) <= D_max){  // 找出所有可到达的加油站
                        if(Pi[cur] <= min_unit){  // 找到除了当前站的油价最低的加油站
                            min_unit = Pi[cur];
                            cur_index = cur;
                        }
                        cur++;
                    }
                    distance += Di[cur_index] - Di[i-1];
                    if ((D - Di[i-1]) <= D_max){
                        cost += Pi[i-1] * (D - Di[i-1]) / D_avg;  // 加到刚好能到终点
                    } 
                    else cost += Pi[i-1] * (C - cap);  // 不然加满
                    cap = C - (Di[cur_index] - Di[i-1]) / D_avg;  // 开到下一个最低的加油站后剩下的油量
                    i = cur_index + 1;
                    if(i == N){
                        if((D - Di[N-1]) <= D_max) cost += (D - Di[N-1]) * Pi[N-1] / D_avg;
                        else printf("The maximum travel distance = %.2f", Di[N-1] + D_max); 
                    }
                }
                else{  // 如果可达的加油站存在加油更便宜或相等的，那么加油至正好到达第一个这样的加油站
                    cur = i - 1;
                    while((Di[i] - Di[cur]) <= D_max){  // 找出所有可到达的加油站
                        if(Pi[i] <= Pi[cur]){
                            distance += Di[i] - Di[cur];
                            if(cap * D_avg < (Di[i] - Di[cur])){
                                cost += Pi[cur] * (Di[i] - Di[cur] - cap * D_avg) / D_avg;  // 还得再加油至正好到达
                            }
                            else{
                                cap -= (cap * D_avg - Di[i] - Di[cur]) / D_avg;  // 正好到达时还剩油
                            }
                            // cap = C - (Di[cur_index] - Di[i-1]) / D_avg;  // 开到下一个最低的加油站后剩下的油量
                            i++;
                            break;
                        }
                        i++;
                    }
                    if(i == N){
                        if((D - Di[N-1]) <= D_max) cost += (D - Di[N-1]) * Pi[N-1] / D_avg;
                        else printf("The maximum travel distance = %.2f", Di[N-1] + D_max); 
                    }
                }
            }
        }
        printf("%.2f", cost);
    }
    return 0;
}