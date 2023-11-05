#include <stdio.h>
#include <string.h>
#include <math.h>
#include "./system.h"
#include "../f1c100s/arm926/inc/arm32.h"
#include "../f1c100s/drivers/inc/f1c100s_de.h"
#include "../f1c100s/drivers/inc/f1c100s_timer.h"
#include "../f1c100s/drivers/inc/f1c100s_intc.h"
#include "../f1c100s/drivers/inc/f1c100s_gpio.h"
#include "../f1c100s/drivers/inc/f1c100s_pwm.h"
#include "../FreeRTOS/include/FreeRTOS.h"
#include "../FreeRTOS/include/task.h"

static void Task1(void* pvParameters) {
    (void)pvParameters;
    while (1) {
        printf("FreeRTOS Task1 Task\n\r");
        vTaskDelay(1000);
    }
}

static void MainTask(void* pvParameters) {
    (void)pvParameters;
    while (1) {
        printf("FreeRTOS Main Task\n\r");
        vTaskDelay(1000);
    }
}

int main(void) {
    system_init();            // Initialize clocks, mmu, cache, uart, ...
    arm32_interrupt_enable(); // Enable interrupts

    // 创建任务
    xTaskCreate(MainTask, "MainTask", 1024, NULL, 3, NULL);
    xTaskCreate(Task1, "Task1", 1024, NULL, 3, NULL);
    // 启动任务
    vTaskStartScheduler();
    while (1) { }
    return 0;
}

