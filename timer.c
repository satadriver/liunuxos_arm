#include "timer.h"

// 中断处理函数指针
typedef void (*irq_handler_t)(void);
static irq_handler_t irq_handler = 0;

// 注册中断处理函数
void register_irq_handler(irq_handler_t handler) {
    irq_handler = handler;
}

// 初始化 GICv2
void gic_init() {
    // 1. 启用 GIC Distributor
    GICD_BASE[0] = 1;  // GICD_CTLR

    // 2. 启用 PPI 30（ARM 定时器中断）
    GICD_BASE[0x100 / 4] = 1 << 30;  // GICD_ISENABLERn

    // 3. 启用 CPU Interface
    GICC_BASE[0] = 1;  // GICC_CTLR

    // 4. 设置优先级掩码（允许所有中断）
    GICC_BASE[4 / 4] = 0xFF;  // GICC_PMR
}

// 初始化定时器（interval_ns 为中断间隔纳秒）
void timer_init(uint64_t interval_ns) {
    // 1. 获取定时器频率（Hz）
    uint64_t freq = READ_REG(CNTFRQ_EL0);

    // 2. 计算比较值（ticks = freq * interval_ns / 1e9）
    uint64_t ticks = (freq * interval_ns) / 1000000000;
    WRITE_REG(CNTP_CVAL_EL0, ticks);

    // 3. 启用定时器并允许中断
    WRITE_REG(CNTP_CTL_EL0, 1);  // ENABLE=1, IMASK=0
}

// 默认中断处理函数
void default_irq_handler() {
    uint32_t irq_num = GICC_BASE[0x0C / 4] & 0x3FF;  // GICC_IAR

    if (irq_num == 30) {  // 定时器中断
        // 重新设置定时器比较值（周期性触发）
        uint64_t freq = READ_REG(CNTFRQ_EL0);
        WRITE_REG(CNTP_CVAL_EL0, READ_REG(CNTP_CVAL_EL0) + freq);

        // 处理中断（例如打印信息）
        asm volatile("mov x0, #'T'; svc #0");  // 示例：通过 SVC 打印字符
    }

    // 通知 GIC 中断处理完成
    GICC_BASE[0x10 / 4] = irq_num;  // GICC_EOIR
}

// 主函数
int initTimer() {
    // 1. 注册中断处理函数
    register_irq_handler(default_irq_handler);

    // 2. 初始化 GIC 和定时器（1秒间隔）
    gic_init();
    timer_init(1000000000);

    // 3. 启用 CPU 中断响应
    ENABLE_IRQ();

    // 4. 主循环（等待中断）
    while (1) {
        asm volatile("wfi");  // 等待中断
    	break;
    }
    return 0;
}
