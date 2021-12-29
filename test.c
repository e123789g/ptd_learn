#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "test.h"


struct timeval start;
struct timeval end;

#define NOT_COMPLETED 0 
#define COMPLETED     1

volatile int flag = NOT_COMPLETED;

// float time_diff(struct timeval *start, struct timeval *end)
// {
//     return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
// }
// 子執行緒函數
void* child(void* data) 
{
    char *str = (char*) data; // 取得輸入資料
    for(int i = 0;i < 3;++i) 
    {
        printf("%s\n", str); // 每秒輸出文字
        sleep(3);
    }
    pthread_cancel(timer);
    printf("callback finish\n");
    pthread_exit(NULL); // 離開子執行緒
}

void* timer_f(void* data) 
{
    // gettimeofday(&start, NULL);
    // gettimeofday(&end, NULL);
    
    // printf("start: %d\n", start.tv_sec);
    // printf("end: %d\n", end.tv_sec);
    // while (time_diff(&start, &end) < 10)
    // {
    //     gettimeofday(&end, NULL);
    // }
    // printf("end: %d\n", end.tv_sec);
    sleep(5);
    pthread_cancel(callback);
    printf("timer finish\n");
    pthread_exit(NULL); // 離開子執行緒
}

// 主程式
int main() 
{
    int ret = -1;
    
    pthread_create(&callback, NULL, child, "Child"); // 建立子執行緒
    pthread_create(&timer, NULL, timer_f, "Child"); // 建立子執行緒
    // 主執行緒工作
    for(int i = 0;i < 3;++i) 
    {
        printf("Master\n"); // 每秒輸出文字
        sleep(1);
    }

    ret = pthread_join(timer, NULL); // 等待子執行緒執行完成
    
    ret = pthread_join(callback, NULL); // 等待子執行緒執行完成
    
    return 0;
}


