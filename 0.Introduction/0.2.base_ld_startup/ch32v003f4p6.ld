ENTRY(_start)  

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 16K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 2K
}

SECTIONS
{
    .text : {
        *(.text*)
        *(.text.*)
        . = ALIGN(4);
    } > FLASH

    .rodata : {
        *(.rodata*)
        *(.rodata.*)
        . = ALIGN(4);
    } > FLASH

    .data : {
        _data_start = .;
        *(.data*)
        *(.data.*)
        *(.sdata*)
        . = ALIGN(4);
        _data_end = .;
    } > RAM AT > FLASH

    PROVIDE(__global_pointer$ = _data_start + 0x800);

    .bss : {
        _bss_start = .;
        *(.bss*)
        *(.bss.*)
        *(.sbss*)
        . = ALIGN(4);
        _bss_end = .;
    } > RAM
}

PROVIDE(_stack_end = ORIGIN(RAM) + LENGTH(RAM));
PROVIDE(_data_load = LOADADDR(.data));