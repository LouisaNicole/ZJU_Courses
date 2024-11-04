test.cpp函数是只有输入节点数，输出答案的源代码；
RBtree.cpp文件包含了N从1-500的全部测试样例，可以直接g++ RBtree.cpp -o编译，测试结果将输出到black_red.txt文件中；
RBtree_recur.cpp文件是递归版本的实现，同样包含了N从1-500的全部测试样例，测试结果将输出到black_red_recursion.txt文件中，但是由于函数的调用使得时间反而更长；
RBtree_mtt.cpp是利用傅里叶变换优化的