#include <dlfcn.h>
#include <ffi.h>
#include <stdio.h>
#include <stdlib.h>

/*
https://www.jianshu.com/p/92d4c06223e7
gcc -o fficall2 fficall2.c -ldl -lffi
拷贝成功
TODO:
实现doMath的函数回调，
    思路： 这里实现一个乘法函数，直接增加一个函数参数？可行么
    dart/java怎么办？
 */
int main(int argc, char const* argv[]) {
    void* libhandle = dlopen("./func_pointer1.so", RTLD_LAZY);

    void* func_ptr = dlsym(libhandle, "add");
    int args_count = 2;
    
    //参数类型数组
    ffi_type **ffi_arg_types = alloca(sizeof(ffi_type *) * args_count); //alloca栈上分配，不用销毁
    ffi_arg_types[0] = &ffi_type_sint;
    ffi_arg_types[1] = &ffi_type_sint;
    
    //参数数据数组
    void **ffig_arg_values = alloca(sizeof(void *) * args_count);

    //参数赋值, NOTE:这里第二指针是否多余?
    void *ffi_arg1_ptr = alloca(ffi_arg_types[0]->size);
    int *arg1_ptr = ffi_arg1_ptr;
    *arg1_ptr = 5;
    ffig_arg_values[0] = ffi_arg1_ptr;
    
    void *ffi_arg2_ptr = alloca(ffi_arg_types[1]->size);
    int *arg2_ptr = ffi_arg2_ptr;
    *arg2_ptr = 3;
    ffig_arg_values[1] = ffi_arg2_ptr;
    
    //生成函数原型 ffi_cfi 对象
    ffi_cif cif;
    ffi_type *ffi_return_type = &ffi_type_sint;
    ffi_status ffiPrepStatus = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, (unsigned int)args_count, ffi_return_type, ffi_arg_types);
    
    if (ffiPrepStatus == FFI_OK) {
        //生成用于保存返回值的内存
        void *returnPtr = NULL;
        if (ffi_return_type->size) {
            returnPtr = alloca(ffi_return_type->size);
        }
        //根据cif函数原型，函数指针，返回值内存指针，函数参数数据调用这个函数
        ffi_call(&cif, func_ptr, returnPtr, ffig_arg_values); //NOTE: 这里的func_ptr并没有使用FFI_FN宏包装
        
        //拿到返回值
        int returnValue = *(int *)returnPtr;
        printf("ret: %d \n", returnValue);
    }
    return 0;
}
