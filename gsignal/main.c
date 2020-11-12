#include "my-file.h"

/* GCC: gcc -g `pkg-config --cflags --libs glib-2.0 gobject-2.0` main.c my-file.c -o main */

/* 
来源：
https://blog.csdn.net/knowledgebao/article/details/82491581
http://garfileo.is-programmer.com/2011/3/21/gobject-signal.25477.html

ref:
https://github.com/gobject-app/GObject-demo (也有一些信号相关的练习)

TODO:
增加参数测试
*/

static void file_print(gpointer gobject, gpointer user_data) { 
    int *value = user_data;
    // g_printf("invoking file_print!\n"); 
    printf("....file_print, arg=%d \n",*value);
}
static void file_print_xml(gpointer gobject, gpointer user_data) { g_printf("invoking file_print_xml!\n"); }
static void file_print_tex(gpointer gobject, gpointer user_data) { g_printf("invoking file_print_tex!\n"); }

int main(void) {
    g_type_init();

    int arg0 = 100;
    MyFile *file = g_object_new(MY_TYPE_FILE, "name", "test.txt", NULL);

    // g_signal_connect(file, "file_changed", G_CALLBACK(file_print), NULL);
    g_signal_connect(file, "file_changed", G_CALLBACK(file_print), &arg0);
    g_signal_connect(file, "file_changed", G_CALLBACK(file_print_xml), NULL);
    g_signal_connect(file, "file_changed", G_CALLBACK(file_print_tex), NULL);

    my_file_write(file, "hello world!\n");

    g_object_unref(file);

    return 0;
}