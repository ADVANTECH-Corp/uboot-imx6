MEMORY { .sram : ORIGIN = 0x7E1000,
  LENGTH = (124 * 1024) }
MEMORY { .sdram : ORIGIN = 0x00180000,
  LENGTH = 0x2000 }
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
 .text : {
  . = ALIGN(8);
  *(.__image_copy_start)
  arch/arm/cpu/armv8/start.o (.text*)
  *(.text*)
 } >.sram
 .rodata : {
  . = ALIGN(8);
  *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
 } >.sram
 .data : {
  . = ALIGN(8);
  *(.data*)
 } >.sram
 .u_boot_list : {
  . = ALIGN(8);
  KEEP(*(SORT(.u_boot_list*)));
 } >.sram
 .image_copy_end : {
  . = ALIGN(8);
  *(.__image_copy_end)
 } >.sram
 .end : {
  . = ALIGN(8);
  *(.__end)
 } >.sram
 _image_binary_end = .;
 .bss_start : {
  . = ALIGN(8);
  KEEP(*(.__bss_start));
 } >.sdram
 .bss : {
  *(.bss*)
   . = ALIGN(8);
 } >.sdram
 .bss_end : {
  KEEP(*(.__bss_end));
 } >.sdram
 /DISCARD/ : { *(.dynsym) }
 /DISCARD/ : { *(.dynstr*) }
 /DISCARD/ : { *(.dynamic*) }
 /DISCARD/ : { *(.plt*) }
 /DISCARD/ : { *(.interp*) }
 /DISCARD/ : { *(.gnu*) }
}
