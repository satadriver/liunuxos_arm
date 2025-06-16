

#include "config.h"

void __klog(char * str){

        int * base = (int*)UART_BASE_ADDRESS;
        while(*str){
                *base = (int)*str;
        	str++;
        }
}


