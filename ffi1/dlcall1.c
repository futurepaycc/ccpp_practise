#include <dlfcn.h>
#include <stdio.h>


/* GCC: gcc -g -o dlcall1 dlcall1.c -ldl */

//https://eli.thegreenplace.net/2013/03/04/flexible-runtime-interface-to-shared-libraries-with-libffi
int main(int argc, char const *argv[]) {
    void* libhandle = dlopen("./func_pointer1.so", RTLD_LAZY);

    int (*add_func_ptr)(int,int) = dlsym(libhandle, "add");
    int result = add_func_ptr(3,5);
    printf("add result = %d\n",result);
    /* code */
    return 0;
}
