#include <stdio.h>
#include <uv.h>

/* GCC: gcc -luv -o hello1 hello1.c */
static void onTimerTick(uv_timer_t *handle){
    printf("timer tick\n");
}

int main(int argc, char const *argv[])
{
    uv_loop_t *loop = uv_default_loop();
    uv_timer_t timerHandle;
    uv_timer_init(loop,&timerHandle);
    uv_timer_start(&timerHandle,onTimerTick,0,1000);
    uv_run(loop,UV_RUN_DEFAULT);
    return 0;
}
