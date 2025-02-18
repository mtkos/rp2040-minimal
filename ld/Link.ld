MEMORY{
        BOOT2      : ORIGIN = 0x10000000, LENGTH = 0x100 
        FLASH (rx) : ORIGIN = 0x10000100, LENGTH = 2048K  - 0x100
        RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 264K
}

_flash_base = ORIGIN(FLASH);
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {

    .boot2 :{
      *(.boot2*);
    } >BOOT2

    .init :{ 
      . = ALIGN(4);
      *(.init)
      . = ALIGN(4);
    } >FLASH

    .text :{
      . = ALIGN(4);
      *(.text .text*)
      *(.rodata .rodata*)
      *(.srodata .srodata*)
      . = ALIGN(4);
    } >FLASH

    .sdata :{
      . = ALIGN(4);
      _sdata = .;
    } >RAM

    .sidata :{
      . = ALIGN(4); 
      _sidata = .;
    } >FLASH

    .data :{
      . = ALIGN(4);
      *(.data .data.*)
      *(.sdata .sdata.*)
      . = ALIGN(4);
      _edata = .;
    } >RAM AT>FLASH

    .bss :{
      . = ALIGN(4);
      _sbss = .;
      *(.sbss*)
      *(.bss*)
      . = ALIGN(4);
      _ebss = .;
    } >RAM

}
