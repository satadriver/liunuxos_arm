
#pragma once

#include <stdint.h>

// GICv2 寄存器基地址（QEMU virt 平台）
#define GICD_BASE  ((volatile uint32_t *)0x08000000)
#define GICC_BASE  ((volatile uint32_t *)0x08010000)

// ARM 定时器寄存器
#define CNTP_CTL_EL0   "S3_1_C14_C2_1"  // 定时器控制寄存器
#define CNTP_CVAL_EL0  "S3_3_C14_C2_2"  // 定时器比较值
#define CNTFRQ_EL0     "S3_3_C14_C0_0"  // 定时器频率

// DAIF 中断屏蔽位
#define DAIF_IRQ_BIT   (1 << 1)

// 内联汇编辅助宏
#define READ_REG(reg) ({ uint64_t val; asm volatile("mrs %0, " reg : "=r"(val)); val; })
#define WRITE_REG(reg, val) asm volatile("msr " reg ", %0" : : "r"(val))
#define ENABLE_IRQ() asm volatile("msr daifclr, %0" : : "i"(DAIF_IRQ_BIT))


int initTimer() ;
