#include <ffi.h>
#include <stdio.h>

/* GCC: gcc -g -o ffi_closure1 ffi_closure1.c -ldl -lffi */

/*
来源:
https://gist.github.com/TooTallNate/1575877
参考：
https://www.jianshu.com/p/92d4c06223e7
https://www.jianshu.com/p/936da8e0cd0d
*/

/* Acts like puts with the file given at time of enclosure. */
// 函数实体
void puts_binding(ffi_cif *cif, unsigned int *ret, void* args[],FILE *stream){
    // *ret = fputs(*(char **)args[0], stream);
    *ret = printf("我是那个要被动态调用的函数: %s\n",*(char **)args[0]);
}

int main(){
    ffi_cif cif;
    ffi_type *args[1];
    ffi_closure *closure;
    
    int (*bound_puts)(char *);  //声明一个函数指针
    int rc;
    
    /* Allocate closure and bound_puts */  //创建closure
    closure = ffi_closure_alloc(sizeof(ffi_closure), &bound_puts);
    
    if (closure){
        /* Initialize the argument info vectors */
        args[0] = &ffi_type_pointer;
        
        /* Initialize the cif */  //生成函数原型
        if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1,&ffi_type_uint, args) == FFI_OK){
            /* Initialize the closure, setting stream to stdout */
            // 通过 ffi_closure 把 函数原型_cifPtr / 函数实体JPBlockInterpreter / 上下文对象self / 函数指针blockImp 关联起来
            if (ffi_prep_closure_loc(closure,  //闭包
                                        &cif,  //函数原型
                                        puts_binding, //外层函数实体?
                                        stdout,     //userdata,函数上下文，函数实体实参(外层函数参数？)
                                        bound_puts //函数指针，指向函数实体
                                        ) == FFI_OK){
                rc = bound_puts("Hello World!"); //内层参数，closure参数？
                /* rc now holds the result of the call to fputs */
            }
        }
    }
    /* Deallocate both closure, and bound_puts */
    ffi_closure_free(closure);   //释放闭包
    
    return 0;
}