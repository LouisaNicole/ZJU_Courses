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
//     //�ַ�������
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
//     string str6(str4, 6, 5);  //�ӵ�7����ʼ��5���ַ�
//     cout << "str4 = " << str4 << endl;
//     cout << "str5 = " << str5 << endl;
//     cout << "str6 = " << str6 << endl;

//     string  str7;
//     str7.assign(10,'a');
//     cout << "str7 = " << str7 << endl;
//     string str8 = "hello,hangzhou!";
//     string str_find = "hangzhou";
//     cout << str8.find(str_find) << endl;   // ����
//     cout << str8.replace(str8.find(str_find),str_find.length(),"beijing");  //�滻

//     string str[] = {"zxw","qwe"};
//     cout << str[0] << " " << str[1] << endl;

//     int m;
//     int &n = m;      //����nΪm�����ñ���
//     m = 30;
//     cout << "m=" << m << " "<< "n=" << n << "\n";
//     n = 80;
//     cout << "m=" << m << " "<< "n=" << n << "\n";
//     cout << "m��ַ��:" << &m << endl;
//     cout << "n��ַ��:" << &n << endl;
    
//     return 0;
// }