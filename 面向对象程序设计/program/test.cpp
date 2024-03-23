#include<iostream>
// #include<stdlib>
class A {
    int i;
public:
    virtual void set(int ii) { i = ii;}
    virtual int get() { return i; }
};

class B : public A {
    int i;
public:
    virtual void set(int ii) { i = ii;}
    virtual int get() { return i; }
};

int main()
{
    B a;
    B b;
    a.set(10);
    b.set(20);
    A& p = a;
    p.set(30);
    p = b;
    p.set(40);
    std::cout << a.get();
    return 0;
}
