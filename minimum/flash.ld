
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
    *(.text)
    *(.text*)
    _etext = .;
  } > flash

  .rodata :
  {
    *(.rodata)
    *(.rodata*)
  } > flash

  _sidata = LOADADDR(.data);

  .data :
  {
    _sdata = .;
    *(.data)
    *(.data*)
    _edata = .;
  } > ram AT > flash

  .bss :
  {
    _sbss = .;
    *(.bss)
    *(.bss*)

    . = ALIGN(4);
    _ebss = .;
  } > ram


}
