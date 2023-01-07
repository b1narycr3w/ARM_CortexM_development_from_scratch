
ENTRY(Reset_Handler)

_estack = ORIGIN(ram) + LENGTH(ram);

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
    *(.isr_vector)
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

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
    _ebss = .;
    _end = .;
  } > ram

}
