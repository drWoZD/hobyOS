ENTRY (loader)
LMA = 0x00100000;
SECTIONS
{
    . = LMA;
    .multiboot ALIGN (0x400) :   {  boot.o( .text ) }
    .text      ALIGN (0x400) :   {  *(.text)          }
    .rodata    ALIGN (0x400) :   {  *(.rodata*)       }
    .data      ALIGN (0x400) :   {  *(.data)          }
    .bss :                       {  *(COMMON) *(.bss) }
    /DISCARD/ :                  {  *(.comment) }
} 
