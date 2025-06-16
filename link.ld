
ENTRY(_start)
SECTIONS
{
        . = 0x40000000;
        .startup . : {start.o(.text)}
        .text :{*(.text)}
        .data : {*(.data)}
        .bss : {*(.bss COMMON)}
        . = ALIGN(16);
        . = .+0x100000;
        RESET_HANDLER_STACK_TOP = .;
}


