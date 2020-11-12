#include <dlfcn.h>
#include <ffi.h>
#include <stdio.h>
#include <stdlib.h>

/*
https://eli.thegreenplace.net/2013/03/04/flexible-runtime-interface-to-shared-libraries-with-libffi
gcc -o fficall1 fficall1.c -ldl -lffi
ERROR:
自已写的失败
 */
int main(int argc, char const* argv[]) {
    void* libhandle = dlopen("./func_pointer1.so", RTLD_LAZY);

    // int (*add_func_ptr)(int,int) = dlsym(libhandle, "add");
    // int result = add_func_ptr(3,5);
    // printf("add result = %d\n",result);

    void* add_func = dlsym(libhandle, "add");
    char* err = dlerror();
    if (err) {
        fprintf(stderr, "dlsym failed: %s\n", err);
        exit(1);
    }

    ffi_type* args_types[] = {&ffi_type_pointer, &ffi_type_pointer};
    ffi_cif cif;
    ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, (unsigned int)2, &ffi_type_sint, args_types);

    if (status != FFI_OK) {
        fprintf(stderr, "ffi_prep_cif failed: %d\n", status);
        exit(1);
    }


    int result=0;
    int arg1 = 3;
    int arg2 = 7;
    int arg_values[2] = {arg1,arg2};
    void *arg_pointers = arg_values;
    // void* arg_values = {&arg1, &arg2};
    // ffi_call(&cif, FFI_FN(add_func), &result, arg_values);
    ffi_call(&cif, FFI_FN(add_func), &result, arg_pointers);

    printf("add result = %d\n", result);

    /* code */
    return 0;
}
