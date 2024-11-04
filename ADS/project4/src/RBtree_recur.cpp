#include <iostream>
#include <cmath>
#include <cstring>
#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX_N 502
using namespace std;
long long black_red[MAX_N][MAX_N][2];

long long recur(int n, int h, int b_r) {
    if (black_red[n][h][b_r] != -1) {
        return black_red[n][h][b_r];
    }
    black_red[n][h][b_r] = 0;
    if (h == 0) {
        return black_red[n][h][b_r];
    }
    if (b_r == 0) {  // 黑根
        for (int i = 0; i < n; i++) {
            black_red[n][h][b_r] = (black_red[n][h][b_r] + ((recur(i, h - 1, 0) + recur(i, h, 1)) % MOD) * ((recur(n - i - 1, h - 1, 0) + recur(n - i - 1, h, 1)) % MOD) % MOD) % MOD;
        }
    } 
    else {  // 红根
        for (int i = 0; i < n; i++) {
            black_red[n][h][b_r] = (black_red[n][h][b_r] + recur(i, h - 1, 0) * recur(n - i - 1, h - 1, 0) % MOD) % MOD;
        }
    }
    return black_red[n][h][b_r];
}

int main() {
    ios::sync_with_stdio(false);
    ofstream file;
    file.open("../black_red_recursion.txt");
    for(int in = 1; in <= 500; in++) {
        double time = 0;
        int N = in;
        int i, BH;
        // BH 是后面根据输入的 N 计算的实际黑高最大值
        long long trees=0;
        for (int loop = 0; loop < 10; loop++) {
            clock_t start=clock();
            trees = 0;
            memset(black_red,-1, sizeof(black_red));
            black_red[0][0][0] = 1;
            black_red[1][1][0] = 1;
            black_red[1][1][1] = 1;
            BH = (int)(log2(N + 1));
            for (i = 1; i <= BH; ++i) {
                trees = (trees + recur(N, i, 0)) % MOD;
            }
            time += clock() - start;
        } 
        file << N << " nodes: "<< trees << " trees with time of " << 1.0*time/10 <<endl;
    }
    file.close();
    return 0;
}