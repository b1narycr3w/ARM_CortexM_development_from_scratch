	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"startup.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	1
	.global	Default_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	Default_Handler, %function
Default_Handler:
.LFB0:
	.file 1 "startup.c"
	.loc 1 14 1
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	add	r7, sp, #0
	.cfi_def_cfa_register 7
.L2:
	.loc 1 15 10 discriminator 1
	b	.L2
	.cfi_endproc
.LFE0:
	.size	Default_Handler, .-Default_Handler
	.align	1
	.global	Reset_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	Reset_Handler, %function
Reset_Handler:
.LFB1:
	.loc 1 19 1
	.cfi_startproc
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.loc 1 24 13
	ldr	r5, .L9
	.loc 1 25 13
	ldr	r4, .L9+4
	.loc 1 27 8
	b	.L4
.L5:
	.loc 1 29 13
	ldr	r3, [r5]
	.loc 1 29 11
	str	r3, [r4]
	.loc 1 30 5
	adds	r5, r5, #4
	.loc 1 31 5
	adds	r4, r4, #4
.L4:
	.loc 1 27 8
	ldr	r3, .L9+8
	cmp	r4, r3
	bcc	.L5
	.loc 1 34 8
	ldr	r4, .L9+12
	.loc 1 35 8
	b	.L6
.L7:
	.loc 1 37 11
	movs	r3, #0
	str	r3, [r4]
	.loc 1 38 5
	adds	r4, r4, #4
.L6:
	.loc 1 35 8
	ldr	r3, .L9+16
	cmp	r4, r3
	bcc	.L7
	.loc 1 41 3
	bl	main
.L8:
	.loc 1 43 8 discriminator 1
	b	.L8
.L10:
	.align	2
.L9:
	.word	_sidata
	.word	_sdata
	.word	_edata
	.word	_sbss
	.word	_ebss
	.cfi_endproc
.LFE1:
	.size	Reset_Handler, .-Reset_Handler
	.global	vector_table
	.section	.isr_vector,"aw"
	.align	2
	.type	vector_table, %object
	.size	vector_table, 392
vector_table:
	.word	_estack
	.word	Reset_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	Default_Handler
	.word	Default_Handler
	.word	0
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	Default_Handler
	.word	0
	.word	Default_Handler
	.word	Default_Handler
	.text
.Letext0:
	.file 2 "/home/javi/local/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/javi/local/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include/sys/_stdint.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x135
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0xc
	.4byte	.LASF21
	.4byte	.LASF22
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x54
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x48
	.uleb128 0x5
	.4byte	.LASF11
	.byte	0x1
	.byte	0x4
	.byte	0x11
	.4byte	0x77
	.uleb128 0x5
	.4byte	.LASF12
	.byte	0x1
	.byte	0x5
	.byte	0x11
	.4byte	0x77
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x1
	.byte	0x6
	.byte	0x11
	.4byte	0x77
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x1
	.byte	0x7
	.byte	0x11
	.4byte	0x77
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x1
	.byte	0x8
	.byte	0x11
	.4byte	0x77
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x1
	.byte	0x9
	.byte	0x11
	.4byte	0x77
	.uleb128 0x6
	.4byte	0x77
	.4byte	0xdb
	.uleb128 0x7
	.4byte	0x70
	.byte	0x61
	.byte	0
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x1
	.byte	0x2f
	.byte	0xa
	.4byte	0xcb
	.uleb128 0x5
	.byte	0x3
	.4byte	vector_table
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x1
	.byte	0x12
	.byte	0x1d
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x120
	.uleb128 0xa
	.4byte	.LASF18
	.byte	0x1
	.byte	0x18
	.byte	0xd
	.4byte	0x120
	.uleb128 0x1
	.byte	0x55
	.uleb128 0xa
	.4byte	.LASF19
	.byte	0x1
	.byte	0x19
	.byte	0xd
	.4byte	0x120
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x77
	.uleb128 0xc
	.4byte	.LASF24
	.byte	0x1
	.byte	0xd
	.byte	0x6
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF21:
	.ascii	"startup.c\000"
.LASF13:
	.ascii	"_sdata\000"
.LASF18:
	.ascii	"psrc\000"
.LASF15:
	.ascii	"_sbss\000"
.LASF16:
	.ascii	"_ebss\000"
.LASF23:
	.ascii	"Reset_Handler\000"
.LASF17:
	.ascii	"vector_table\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF14:
	.ascii	"_edata\000"
.LASF12:
	.ascii	"_sidata\000"
.LASF5:
	.ascii	"long unsigned int\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF22:
	.ascii	"/home/javi/MIS_CURSOS/CURSO_ENTORNO_DESARROLLO/stm3"
	.ascii	"2_embedded_ecosystem/minimum\000"
.LASF9:
	.ascii	"__uint32_t\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF6:
	.ascii	"long long int\000"
.LASF24:
	.ascii	"Default_Handler\000"
.LASF20:
	.ascii	"GNU C17 10.3.1 20210824 (release) -mcpu=cortex-m4 -"
	.ascii	"mthumb -mfloat-abi=soft -march=armv7e-m -g -O0\000"
.LASF2:
	.ascii	"short int\000"
.LASF11:
	.ascii	"_estack\000"
.LASF10:
	.ascii	"uint32_t\000"
.LASF4:
	.ascii	"long int\000"
.LASF0:
	.ascii	"signed char\000"
.LASF19:
	.ascii	"pdst\000"
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
