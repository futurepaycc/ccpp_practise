#include <crack.h>
#include <stdio.h>

/*GCC: gcc -lcrack -o hello1 hello1.c*/
/* 
操作：
sudo create-cracklib-dict /usr/share/dict/*
生成词典目录:
/usr/share/cracklib
*/
int main(int argc, char const *argv[])
{
    char * passwd = "hello";
    char * result = FascistCheck(passwd,"/usr/share/cracklib/pw_dict");
    printf("result = %s\n",result);
    return 0;
}
