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
        *(.data*)
        *(.data.*)
        *(.sdata*)
        . = ALIGN(4);
    } > RAM AT > FLASH

    .bss : {
        *(.bss*)
        *(.bss.*)
        *(.sbss*)
        . = ALIGN(4);
    } > RAM
}