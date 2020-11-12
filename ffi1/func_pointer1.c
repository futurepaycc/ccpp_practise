#include <stdio.h>

/* 
来源: 
https://blog.csdn.net/liushuiwen101423/article/details/39547813
*/

void hello() { printf("hello world\n"); }

int add(int a,int b){return a + b;}

int subtract(int a,int b){return a - b;}

/* NOTE: 这个可以看做一个基本的回调原型，函数体内加一些处理就是是了 */
int doMath(int a,int b,int (*func_ptr)(int,int)){
    //
    return func_ptr(a,b);
}

int main(int argc, char const *argv[]) {
    //1. 无参无返回
    void (*hello_func_ptr)() = hello;
    hello_func_ptr();
    //2. 有参有返回
    int (*add_func_ptr)(int,int) = add;
    int result = add_func_ptr(3,5);
    printf("add result = %d\n",result);
    //3.根据静态函数名调用
    result = doMath(10,5,subtract);
    printf("subtract result = %d\n",result);

    return 0;
}
