
ENTRY(Reset_Handler)

_estack = ORIGIN(ram) + LENGTH(ram);

_Min_Heap_Size = 0x200;	/* required amount of heap  */
_Min_Stack_Size = 0x400;	/* required amount of stack */

/* Memory definition */
MEMORY
{
  ram (xrw)     : ORIGIN = 0x20000000, LENGTH = 128K
  flash (xr)    : ORIGIN = 0x08000000, LENGTH = 512K
}


/* Output Sections */
SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > flash

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    . = ALIGN(4);
    _etext = .;
  } > flash

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > flash

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > ram AT > flash

  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    *(.bss)
    *(.bss*)

    . = ALIGN(4);
    _ebss = .;
    _end = .;
  } > ram


  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM
}
