源文件是main.cpp mian.h、input.cpp、output.cpp和四个pdxxx.cpp程序。
你可以选择在终端输入g++ main.cpp pdadd.cpp input.cpp output.cpp -o add来生成add.exe文件，同理生成其他三个。
也可以选择解压exe文件夹得到四个exe文件
另外程序的运行不能直接通过点击exe文件，而需要打开后缀名为bat的文件，根据上面的提示语，输入pdadd/pdlist/pdremove/pdshow/exit五种操作名称之一，改变的结果体现在Diary.txt文件中，里面也有一些原本的测试样例可供使用。