#include <iostream>
#include <string>
using namespace std;


int z;
int& add(int x,int y);

int main()
{   
    int a=add(5,7);
    cout<<a<<endl;
    add(4,9)++;
    cout<<z<<endl;
    add(2,8)=8;
    cout<<z<<endl;
    return 0;
}
int& add(int x,int y)
{
    return z=x+y;
}
       

// int main()
// {
//     //字符串操作
//     int age,num;
//     cin >> age >> num;
//     // Display Welcome to C++ to the console
//     cout << "Hello World! I am " << age << " " << num << " today" << endl;
//     string str1 = "foo";
//     string str2 = "bar";
//     string str3 = str1 + str2;
//     cout << "str3 = " << str3 << endl;

//     string str4("hello,china");
//     string str5(str3);
//     string str6(str4, 6, 5);  //从第7个开始找5个字符
//     cout << "str4 = " << str4 << endl;
//     cout << "str5 = " << str5 << endl;
//     cout << "str6 = " << str6 << endl;

//     string  str7;
//     str7.assign(10,'a');
//     cout << "str7 = " << str7 << endl;
//     string str8 = "hello,hangzhou!";
//     string str_find = "hangzhou";
//     cout << str8.find(str_find) << endl;   // 查找
//     cout << str8.replace(str8.find(str_find),str_find.length(),"beijing");  //替换

//     string str[] = {"zxw","qwe"};
//     cout << str[0] << " " << str[1] << endl;

//     int m;
//     int &n = m;      //变量n为m的引用别名
//     m = 30;
//     cout << "m=" << m << " "<< "n=" << n << "\n";
//     n = 80;
//     cout << "m=" << m << " "<< "n=" << n << "\n";
//     cout << "m地址是:" << &m << endl;
//     cout << "n地址是:" << &n << endl;
    
//     return 0;
// }