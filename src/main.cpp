#include "application.h"
#include <stdio.h>

extern "C" {
int main(void) {
    Application::GetInstance().Start();
}

/**
 * @brief FreeRTOS栈溢出钩子函数
 * @param xTask 发生栈溢出的任务句柄
 * @param pcTaskName 发生栈溢出的任务名称
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    /* 栈溢出处理 - 可以在这里添加调试信息或错误处理 */
    printf("栈溢出错误: 任务 %s 发生栈溢出\r\n", pcTaskName);

    /* 进入无限循环，防止系统继续运行 */
    for (;;) {
        /* 可以在这里添加LED闪烁等指示 */
    }
}
}