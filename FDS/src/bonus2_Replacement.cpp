#include <iostream>
#include <set>
#include <vector>
#define MAX_ELEMENTS 100001
using namespace std;

typedef multiset<int> runs;  //升序存储元素，包括重复的元素

void insert(runs& run, int element) {
    run.insert(element);
}

void erase(runs& run, int element) {
    run.erase(run.find(element));
}

int main() {
    int n, m, index = 0, cnt = 0, i;
    int num[MAX_ELEMENTS];
    cin >> n >> m;
    runs m1, m2;
    vector<runs> result(MAX_ELEMENTS/2);
    for(i=0; i<n; i++) {
        cin >> num[i];
        if(i < m) {
            insert(m1, num[i]);
            insert(result[0], num[i]);
        }
    }
    for(i=m; i<n; i++) {
        if(num[i] > *m1.begin()) {      //m1.begin()返回m1中最小元素的指针
            insert(result[index], num[i]);
            erase(m1, *m1.begin());
            insert(m1, num[i]);
        } 
        else {                          //小于就放在第二轮
            insert(m2, num[i]);
            erase(m1, *m1.begin());
            insert(result[index + 1], num[i]);
        }
        if(m1.empty()) {
            index++;
            int k;
            for(k=0; k<m; k++) {
                m1.insert(*m2.begin());
                m2.erase(m2.begin());
            }
        }
    }
    while(!result[cnt].empty()) cnt++;
    for(i=0; i<cnt; i++) {
        int flag = 0;
        for(auto it = result[i].begin(); it != result[i].end(); it++) {
            int element = *it;
            if(flag != 0) cout << " ";
            cout << element;
            flag = 1;
        }
        cout << "\n";
    }
    return 0;
}