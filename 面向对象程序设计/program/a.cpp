#include <iostream>
using namespace std;

enum ERROR{UnderFlow,OverFlow};
template<typename T>
class StackTemplate {
    enum { ssize = 100 };
    T stack[ssize];
    int top;
public:
    StackTemplate() : top(0) {}
    void push(const T& i) {
        if (top >= ssize) throw OverFlow;
        stack[top++] = i;
    }
    T pop() {
        if (top <= 0) throw UnderFlow;
        return stack[--top];
    }
    int size() const
    { return top; }
};
int fibonacci(int n);
int main() {
    try {
        StackTemplate<int> is;
        for(int i = 0; i < 20; i++)
            is.push(fibonacci(i));
        for(int k = 0; k < 20; k++)
            cout << is.pop() << "  ";
    }
    catch( ERROR e ) {
        switch(e){
            case OverFlow:
                exit;
            case UnderFlow:
                exit;
        }
    }
    catch(...){   
        exit;
    }
    return 0;
}

int fibonacci(int n) {
    const int sz = 100;
    int i;
    static int f[sz]; 
    if (n >= sz) return fibonacci(sz-1);
    f[0] = f[1] = 1;
    for(i = 0; i < sz; i++) if(f[i] == 0) break;
    while(i <= n) {
        f[i] = f[i-1] + f[i-2];
        i++;
    }
    return f[n];
}