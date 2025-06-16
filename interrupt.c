#include "utils.h"
#include "timer.h"


void enable_interrupts(void) {
    __asm__ volatile("msr daifclr, #0b1111" : : : "memory");
}


void resetHandler(){

//__asm__ volatile("mov sp, %0" : : "r"(0x1000000));

	__klog("reset handler!\r\n");
	enable_interrupts();
	initTimer(); 	
		
__delay:
	//goto __delay;
	return;

}	


void undefinedHandler(){
	__klog("undefined handler!\r\n");
}	
  
void svcHandler(){
	__klog("svc handler!\r\n");
}	
 

void prefAbortHandler(){

	__klog("pref abort handler!\r\n");
}	


void dataAbortHandler(){
	__klog("data abort handler!\r\n");
}	

void notUsedHandler(){
	__klog("not used handler!\r\n");

}	
void irqHandler(){
	__klog("irq handler!\r\n");

}	
void fiqHandler(){
	__klog("fiq handler!\r\n");
}	
