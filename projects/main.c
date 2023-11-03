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

void delay(uint32_t t);
void timer_init(void);
void timer_irq_handler(void);

volatile uint8_t tick_flag = 0;

int main(void) {
    system_init();            // Initialize clocks, mmu, cache, uart, ...
    arm32_interrupt_enable(); // Enable interrupts

    timer_init();

    while (1) {
        printf("Hello World!\n\r");
        delay(1000);
    }
    return 0;
}

void timer_init(void) {
    // Configure timer to generate update event every 1ms
    tim_init(TIM0, TIM_MODE_CONT, TIM_SRC_HOSC, TIM_PSC_1);
    tim_set_period(TIM0, 24000000UL / 1000UL);
    tim_int_enable(TIM0);
    // IRQ configuration
    intc_set_irq_handler(IRQ_TIMER0, timer_irq_handler);
    intc_enable_irq(IRQ_TIMER0);

    tim_start(TIM0);
}

void timer_irq_handler(void) {
    tick_flag = 1;
    tim_clear_irq(TIM0);
}

void delay(uint32_t t) {
    while (1) {
        if (t == 0) return;
        if (tick_flag == 1) {
            tick_flag = 0;
            t--;
        }
    }
}
