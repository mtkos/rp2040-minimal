MEMORY{
        FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 2048K
        RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 264K
}

_flash_base = ORIGIN(FLASH);
_estack = ORIGIN(RAM) + LENGTH(RAM);
_estack1 = ORIGIN(RAM) + LENGTH(RAM) - 0x1000;

SECTIONS {

    .boot2 :{
      *(.boot2*);
    } >FLASH

    .init :{ 
      . = ALIGN(256);
      _vtable = .;
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
