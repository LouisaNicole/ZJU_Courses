#include <iostream>
#include <cmath>
#include <cstring>
#include <bits/stdc++.h>
#define MAX_N 502
#define MAX_BH 9
#define MOD 1000000007
using namespace std;
// n 最大 500，取 log 是 9，MAX_BH 定义为最大的黑高
int main(){
    ios::sync_with_stdio(false);
    ofstream file;
    file.open("../black_red.txt");
    for(int in = 1; in <= 500; in++) {
        double time = 0;
        int N = in;
        int i, j, k, BH;
        // BH 是后面根据输入的 N 计算的实际黑高最大值
        long long trees=0;
        // 这里是个坑，一开始写的是 int 类型死活过不了，long long 八的字节可以覆盖到 1000000007
        long long black[MAX_N][MAX_BH], red[MAX_N][MAX_BH];    // 非空节点为n，高度为h的黑根(红根)红黑树的个数
        for (int loop = 0; loop < 10; loop++) {
            clock_t start=clock();
            trees = 0;
            memset(black, 0, sizeof(black));  // 初始化为0
            memset(red, 0, sizeof(red));    // 初始化为0
            black[1][1] = 1;                                       // 黑(父)——null+null
            black[2][1] = 2;                                       // 黑(父)——红+null 或者 黑(父)——null+红
            black[3][1] = 1;                                       // 黑(父)——红+红
            // cin >> N;
            BH = (int)(log2(N + 1));
            for (i = 1; i <= N; i++) {
                for (j = 1; j <= BH; j++) {
                    for (k = 1; k < i - 1; k++) {
                        black[i][j] = (black[i][j] + ((black[k][j-1] + red[k][j-1]) * (black[i-1-k][j-1] + red[i-1-k][j-1]) % MOD)) % MOD;
                        // 一个黑根红黑树的左右子树为 黑高是父亲节点黑高-1 的两个黑根红黑树、两个红根红黑树或者一红一黑
                        // 其中一棵子树节点数k，可能是黑根或者红根，但是黑高比父节点少一所以是j-1
                        // 另一棵子树节点数i-1-k，可能是黑根或者红根，但是黑高比父节点少一所以是j-1
                        red[i][j] = (red[i][j] + (black[k][j] * black[i-1-k][j]) % MOD) % MOD;
                        // 一个红根红黑树的 左右子树为 黑高与父亲节点黑高相同 的两个黑根红黑树，一棵节点数k，另一棵节点数i-k-1，黑高都和父节点一样是j
                    }
                }
            }
            for (i = 1; i <= BH; i++) {
                trees = (trees + black[N][i]) % MOD;
                // 将所有可能黑高的N节点树加起来
            }   
            time += clock() - start;
        }
        // cout << trees << "\n";
        // cout << clock()-start << endl;
        file << N << " nodes: "<< trees << " trees with time of " << 1.0*time/10 <<endl;
    }
    file.close();
    return 0;
}