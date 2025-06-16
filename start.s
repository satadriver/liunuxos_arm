
.global _start

_start:

.align 7
b  __resetInit

.align 7
bl  undefinedHandler      

.align 7
bl  svcHandler             

.align 7
bl prefAbortHandler     

.align 7
bl dataAbortHandler        

.align 7
bl notUsedHandler        

.align 7
bl irqHandler            

.align 7
bl fiqHandler          





.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler


.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler


.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler
.align 7
bl fiqHandler

__resetInit:
ldr x0,=RESET_HANDLER_STACK_TOP
mov sp,x0
bl resetHandler
b .
