//#include <stdint.h>
//#include <stdio.h>

#include "utils.h"
#include "config.h"


#define GICD_BASE  0x08000000
#define GICC_BASE  0x08010000


void enable_interrupt() {
    __asm__ volatile("msr daifclr, #2");  // 清除 DAIF 的 I 位（启用 IRQ）
}


// 定时器中断处理函数
void timer_irq_handler() {
    __printf("Timer interrupt!\n");
    __asm__ volatile("msr cntp_ctl_el0, %0" :: "r"(1));  // 重新启用定时器
}

// 初始化 GIC
void init_gic() {
    volatile uint32_t *gicd_isenabler = (uint32_t *)(GICD_BASE + 0x100);
    gicd_isenabler[0] |= (1 << 30);  // 使能 PPI 30

    volatile uint32_t *gicc_pmr = (uint32_t *)(GICC_BASE + 0x04);
    *gicc_pmr = 0xFF;
}

// 初始化 ARM 定时器
void init_arm_timer(uint64_t interval_ns) {
    uint64_t freq;
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(freq));

    uint64_t ticks = (freq * interval_ns) / 1000000000;
    __asm__ volatile("msr cntp_cval_el0, %0" :: "r"(ticks));
    __asm__ volatile("msr cntp_ctl_el0, %0" :: "r"(1));
}

int initTimer() {
    init_gic();
    init_arm_timer(1000000000);  // 1 秒间隔
    enable_interrupt();

    //while (1) {}  // 主循环等待中断
    return 0;
}
