#include <iostream>
#include <set>
#include <vector>
#define MAX_ELEMENTS 100001
using namespace std;
int main() {
    int n, m, index = 0, cnt = 0, i;
    int num[MAX_ELEMENTS];
    cin >> n >> m;
    multiset<int> m1, m2;   //升序存储元素，包括重复的元素
    vector<multiset<int>> result(MAX_ELEMENTS/2);
    for(i=0; i<n; i++) {
        cin >> num[i];
        if(i < m) {
            m1.insert(num[i]);
            result[0].insert(num[i]);
        }
    }
    for(i=m; i<n; i++) {
        if(num[i] > *m1.begin()) {      //m1.begin()返回m1中最小元素的指针
            result[index].insert(num[i]);
            m1.erase(m1.find(*m1.begin()));
            m1.insert(num[i]);
        } 
        else {                          //小于就放在第二轮
            result[index + 1].insert(num[i]);
            m1.erase(m1.find(*m1.begin()));
            m2.insert(num[i]);
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
            if(flag) cout << " ";
            cout << element;
            flag = 1;
        }
        cout << "\n";
    }
    return 0;
}