#include <ffi.h>
#include <stdio.h>

/*
来源:
https://gist.github.com/TooTallNate/1575877
参考：
https://github.com/libffi/libffi/blob/master/doc/libffi.texi
gcc -o ffi_closure2 ffi_closure2.c -ldl -lffi

理解:
外层是包装函数： puts_binding 形成一个bridge, 任何在if(ffi_prep_closure_loc)代码块中的
int (*bound_puts)(char *) 形式调用都会被传递进来

FILE *stream: 对应用外层函数，常见的是的env context
*args[]: 外层内层均可用

内层： 就是一块任意代码，可充当closure

理解难点：
1. 这个场景容易混淆(stdout,printf/puts太常用)
2. int (*bound_puts)(char *) 只是外层函数调用/拦载的类型，和futs没毛线关系, 内层是任意代码块

场景TODO:
1. 任意的加、减、乘、除算法int (mathFunc*)(int,int),通过dlopen动态调用(args[0]传方法名)
2. 尝试实现一个dart版本

 */

/* Acts like puts with the file given at time of enclosure. */
void puts_binding(ffi_cif *cif, unsigned int *ret, void *args[], FILE *stream) { 
    printf("....1. in puts_binding\n");
    *ret = fputs(*(char **)args[0], stream); 
}

int main() {
    ffi_cif cif;
    ffi_type *args[1];
    ffi_closure *closure;

    int (*bound_puts)(char *);
    int rc;

    /* Allocate closure and bound_puts */
    closure = ffi_closure_alloc(sizeof(ffi_closure), &bound_puts);

    if (closure) {
        /* Initialize the argument info vectors */
        args[0] = &ffi_type_pointer;

        /* Initialize the cif */
        if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_uint, args) == FFI_OK) {
            /* Initialize the closure, setting stream to stdout */
            if (ffi_prep_closure_loc(closure, &cif, puts_binding, stdout, bound_puts) == FFI_OK) {
                printf("Before bound_put()\n");
                rc = bound_puts("Hello World!");
                /* rc now holds the result of the call to fputs */
            }
        }
    }

    /* Deallocate both closure, and bound_puts */
    ffi_closure_free(closure);

    return 0;
}