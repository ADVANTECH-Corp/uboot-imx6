	.arch armv8-a
	.file	"asm-offsets.c"
// GNU C11 (GCC) version 7.3.0 (aarch64-poky-linux)
//	compiled by GNU C version 7.3.0, GMP version 6.1.2, MPFR version 3.1.5, MPC version 1.0.3, isl version none
// GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
// options passed:  -nostdinc -I include -I ./arch/arm/include -I .
// -isysroot /home/poky/2.4/sysroots/aarch64-poky-linux -D __KERNEL__
// -D __UBOOT__ -D __ARM__ -D __LINUX_ARM_ARCH__=8 -D DO_DEPS_ONLY
// -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
// -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
// -isystem /home/poky/2.4/sysroots/x86_64-pokysdk-linux/usr/lib/aarch64-poky-linux/gcc/aarch64-poky-linux/7.3.0/include
// -include ./include/linux/kconfig.h -MD arch/arm/lib/.asm-offsets.s.d
// arch/arm/lib/asm-offsets.c -mstrict-align -march=armv8-a
// -mgeneral-regs-only -mlittle-endian -mabi=lp64
// -auxbase-strip arch/arm/lib/asm-offsets.s -g -Os -Wall
// -Wstrict-prototypes -Wno-format-security -Wno-format-nonliteral
// -Werror=date-time -fno-builtin -ffreestanding -fno-stack-protector
// -fno-delete-null-pointer-checks -fstack-usage -fno-pic
// -ffunction-sections -fdata-sections -ffixed-r9 -fno-common -ffixed-x18
// -fverbose-asm
// options enabled:  -faggressive-loop-optimizations -falign-functions
// -falign-jumps -falign-labels -falign-loops -fauto-inc-dec
// -fbranch-count-reg -fcaller-saves -fchkp-check-incomplete-type
// -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
// -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
// -fchkp-use-static-bounds -fchkp-use-static-const-bounds
// -fchkp-use-wrappers -fcode-hoisting -fcombine-stack-adjustments
// -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
// -fdata-sections -fdefer-pop -fdevirtualize -fdevirtualize-speculatively
// -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
// -fexpensive-optimizations -fforward-propagate -ffp-int-builtin-inexact
// -ffunction-cse -ffunction-sections -fgcse -fgcse-lm -fgnu-runtime
// -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
// -fif-conversion -fif-conversion2 -findirect-inlining -finline
// -finline-atomics -finline-functions -finline-functions-called-once
// -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-icf
// -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
// -fipa-ra -fipa-reference -fipa-sra -fipa-vrp -fira-hoist-pressure
// -fira-share-save-slots -fira-share-spill-slots
// -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
// -fleading-underscore -flifetime-dse -flra-remat -flto-odr-type-merging
// -fmath-errno -fmerge-constants -fmerge-debug-strings
// -fmove-loop-invariants -fomit-frame-pointer -foptimize-sibling-calls
// -fpartial-inlining -fpeephole -fpeephole2 -fplt -fprefetch-loop-arrays
// -free -freg-struct-return -freorder-blocks -freorder-functions
// -frerun-cse-after-loop -fsched-critical-path-heuristic
// -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
// -fsched-last-insn-heuristic -fsched-pressure -fsched-rank-heuristic
// -fsched-spec -fsched-spec-insn-heuristic -fsched-stalled-insns-dep
// -fschedule-fusion -fschedule-insns2 -fsection-anchors
// -fsemantic-interposition -fshow-column -fshrink-wrap
// -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
// -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstdarg-opt
// -fstore-merging -fstrict-aliasing -fstrict-overflow
// -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
// -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
// -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
// -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
// -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
// -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
// -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
// -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
// -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
// -funit-at-a-time -fvar-tracking -fvar-tracking-assignments -fverbose-asm
// -fzero-initialized-in-bss -mfix-cortex-a53-835769
// -mfix-cortex-a53-843419 -mgeneral-regs-only -mglibc -mlittle-endian
// -momit-leaf-frame-pointer -mpc-relative-literal-loads -mstrict-align

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup.main,"ax",@progbits
	.align	2
	.global	main
	.type	main, %function
main:
.LFB198:
	.file 1 "arch/arm/lib/asm-offsets.c"
	.loc 1 24 0
	.cfi_startproc
// arch/arm/lib/asm-offsets.c:202: }
	.loc 1 202 0
	mov	w0, 0	//,
	ret
	.cfi_endproc
.LFE198:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "include/common.h"
	.file 3 "./arch/arm/include/asm/types.h"
	.file 4 "include/linux/types.h"
	.file 5 "include/errno.h"
	.file 6 "include/linux/string.h"
	.file 7 "include/ide.h"
	.file 8 "include/part.h"
	.file 9 "include/flash.h"
	.file 10 "include/lmb.h"
	.file 11 "include/asm-generic/u-boot.h"
	.file 12 "include/fdt.h"
	.file 13 "include/libfdt_env.h"
	.file 14 "include/image.h"
	.file 15 "./arch/arm/include/asm/setup.h"
	.file 16 "./arch/arm/include/asm/u-boot-arm.h"
	.file 17 "include/net.h"
	.file 18 "include/environment.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xb5e
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0xc
	.4byte	.LASF180
	.4byte	.LASF181
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF8
	.byte	0x2
	.byte	0xd
	.4byte	0x34
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x4
	.4byte	0x34
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x6
	.byte	0x8
	.4byte	0x62
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x4
	.4byte	0x62
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF7
	.uleb128 0x2
	.4byte	.LASF9
	.byte	0x3
	.byte	0xc
	.4byte	0x34
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2
	.4byte	.LASF11
	.byte	0x3
	.byte	0x12
	.4byte	0x6e
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x7
	.string	"u8"
	.byte	0x3
	.byte	0x1f
	.4byte	0x34
	.uleb128 0x4
	.4byte	0xa7
	.uleb128 0x7
	.string	"u32"
	.byte	0x3
	.byte	0x25
	.4byte	0x6e
	.uleb128 0x2
	.4byte	.LASF13
	.byte	0x3
	.byte	0x31
	.4byte	0xa0
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x3
	.byte	0x32
	.4byte	0xa0
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x4
	.byte	0x57
	.4byte	0x47
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x4
	.byte	0x59
	.4byte	0x40
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x4
	.byte	0x67
	.4byte	0x83
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x4
	.byte	0x69
	.4byte	0x95
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x4
	.byte	0x95
	.4byte	0x95
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x5
	.byte	0xc
	.4byte	0x4e
	.uleb128 0x6
	.byte	0x8
	.4byte	0x69
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x6
	.byte	0xb
	.4byte	0x5c
	.uleb128 0x9
	.byte	0x8
	.uleb128 0xa
	.4byte	0xe2
	.4byte	0x137
	.uleb128 0xb
	.byte	0
	.uleb128 0x8
	.4byte	.LASF22
	.byte	0x7
	.byte	0x10
	.4byte	0x12c
	.uleb128 0xc
	.4byte	.LASF25
	.byte	0x10
	.byte	0x8
	.byte	0xd
	.4byte	0x167
	.uleb128 0xd
	.4byte	.LASF23
	.byte	0x8
	.byte	0xe
	.4byte	0x5c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF24
	.byte	0x8
	.byte	0xf
	.4byte	0x180
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	0x142
	.uleb128 0xe
	.4byte	0x4e
	.4byte	0x180
	.uleb128 0xf
	.4byte	0x4e
	.uleb128 0xf
	.4byte	0x4e
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x16c
	.uleb128 0xa
	.4byte	0x167
	.4byte	0x191
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0x186
	.uleb128 0x8
	.4byte	.LASF25
	.byte	0x8
	.byte	0xba
	.4byte	0x191
	.uleb128 0x10
	.2byte	0x1218
	.byte	0x9
	.byte	0x13
	.4byte	0x1e8
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0x9
	.byte	0x14
	.4byte	0xe2
	.byte	0
	.uleb128 0xd
	.4byte	.LASF27
	.byte	0x9
	.byte	0x15
	.4byte	0xd7
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x9
	.byte	0x16
	.4byte	0xe2
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x9
	.byte	0x17
	.4byte	0x1e8
	.byte	0x18
	.uleb128 0x11
	.4byte	.LASF30
	.byte	0x9
	.byte	0x18
	.4byte	0x1f9
	.2byte	0x1018
	.byte	0
	.uleb128 0xa
	.4byte	0xe2
	.4byte	0x1f9
	.uleb128 0x12
	.4byte	0x40
	.2byte	0x1ff
	.byte	0
	.uleb128 0xa
	.4byte	0x29
	.4byte	0x20a
	.uleb128 0x12
	.4byte	0x40
	.2byte	0x1ff
	.byte	0
	.uleb128 0x2
	.4byte	.LASF31
	.byte	0x9
	.byte	0x32
	.4byte	0x1a1
	.uleb128 0xa
	.4byte	0x20a
	.4byte	0x220
	.uleb128 0xb
	.byte	0
	.uleb128 0x8
	.4byte	.LASF32
	.byte	0x9
	.byte	0x34
	.4byte	0x215
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF33
	.uleb128 0xc
	.4byte	.LASF34
	.byte	0x10
	.byte	0xa
	.byte	0x10
	.4byte	0x257
	.uleb128 0xd
	.4byte	.LASF35
	.byte	0xa
	.byte	0x11
	.4byte	0xc1
	.byte	0
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0xa
	.byte	0x12
	.4byte	0xcc
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.4byte	.LASF36
	.byte	0xa0
	.byte	0xa
	.byte	0x15
	.4byte	0x288
	.uleb128 0x13
	.string	"cnt"
	.byte	0xa
	.byte	0x16
	.4byte	0x40
	.byte	0
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0xa
	.byte	0x17
	.4byte	0xcc
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF37
	.byte	0xa
	.byte	0x18
	.4byte	0x288
	.byte	0x10
	.byte	0
	.uleb128 0xa
	.4byte	0x232
	.4byte	0x298
	.uleb128 0x14
	.4byte	0x40
	.byte	0x8
	.byte	0
	.uleb128 0x15
	.string	"lmb"
	.2byte	0x140
	.byte	0xa
	.byte	0x1b
	.4byte	0x2be
	.uleb128 0xd
	.4byte	.LASF38
	.byte	0xa
	.byte	0x1c
	.4byte	0x257
	.byte	0
	.uleb128 0xd
	.4byte	.LASF39
	.byte	0xa
	.byte	0x1d
	.4byte	0x257
	.byte	0xa0
	.byte	0
	.uleb128 0x16
	.string	"lmb"
	.byte	0xa
	.byte	0x20
	.4byte	0x298
	.uleb128 0x17
	.byte	0x10
	.byte	0xb
	.byte	0x84
	.4byte	0x2ea
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0xb
	.byte	0x85
	.4byte	0xc1
	.byte	0
	.uleb128 0xd
	.4byte	.LASF26
	.byte	0xb
	.byte	0x86
	.4byte	0xcc
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.4byte	.LASF40
	.byte	0x98
	.byte	0xb
	.byte	0x1b
	.4byte	0x3db
	.uleb128 0xd
	.4byte	.LASF41
	.byte	0xb
	.byte	0x1c
	.4byte	0x40
	.byte	0
	.uleb128 0xd
	.4byte	.LASF42
	.byte	0xb
	.byte	0x1d
	.4byte	0xcc
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF43
	.byte	0xb
	.byte	0x1e
	.4byte	0x40
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0xb
	.byte	0x1f
	.4byte	0x40
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF45
	.byte	0xb
	.byte	0x20
	.4byte	0x40
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0xb
	.byte	0x21
	.4byte	0x40
	.byte	0x28
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0xb
	.byte	0x22
	.4byte	0x40
	.byte	0x30
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0xb
	.byte	0x28
	.4byte	0x40
	.byte	0x38
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0xb
	.byte	0x29
	.4byte	0x40
	.byte	0x40
	.uleb128 0xd
	.4byte	.LASF50
	.byte	0xb
	.byte	0x2a
	.4byte	0x40
	.byte	0x48
	.uleb128 0xd
	.4byte	.LASF51
	.byte	0xb
	.byte	0x36
	.4byte	0x40
	.byte	0x50
	.uleb128 0xd
	.4byte	.LASF52
	.byte	0xb
	.byte	0x37
	.4byte	0x40
	.byte	0x58
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0xb
	.byte	0x38
	.4byte	0x3db
	.byte	0x60
	.uleb128 0xd
	.4byte	.LASF54
	.byte	0xb
	.byte	0x39
	.4byte	0x47
	.byte	0x66
	.uleb128 0xd
	.4byte	.LASF55
	.byte	0xb
	.byte	0x3a
	.4byte	0x40
	.byte	0x68
	.uleb128 0xd
	.4byte	.LASF56
	.byte	0xb
	.byte	0x3b
	.4byte	0x40
	.byte	0x70
	.uleb128 0xd
	.4byte	.LASF57
	.byte	0xb
	.byte	0x81
	.4byte	0xe2
	.byte	0x78
	.uleb128 0xd
	.4byte	.LASF58
	.byte	0xb
	.byte	0x82
	.4byte	0xe2
	.byte	0x80
	.uleb128 0xd
	.4byte	.LASF59
	.byte	0xb
	.byte	0x87
	.4byte	0x3eb
	.byte	0x88
	.byte	0
	.uleb128 0xa
	.4byte	0x34
	.4byte	0x3eb
	.uleb128 0x14
	.4byte	0x40
	.byte	0x5
	.byte	0
	.uleb128 0xa
	.4byte	0x2c9
	.4byte	0x3fb
	.uleb128 0x14
	.4byte	0x40
	.byte	0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF60
	.byte	0xb
	.byte	0x89
	.4byte	0x2ea
	.uleb128 0xc
	.4byte	.LASF61
	.byte	0x28
	.byte	0xc
	.byte	0x39
	.4byte	0x48b
	.uleb128 0xd
	.4byte	.LASF62
	.byte	0xc
	.byte	0x3a
	.4byte	0x49c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF63
	.byte	0xc
	.byte	0x3b
	.4byte	0x49c
	.byte	0x4
	.uleb128 0xd
	.4byte	.LASF64
	.byte	0xc
	.byte	0x3c
	.4byte	0x49c
	.byte	0x8
	.uleb128 0xd
	.4byte	.LASF65
	.byte	0xc
	.byte	0x3d
	.4byte	0x49c
	.byte	0xc
	.uleb128 0xd
	.4byte	.LASF66
	.byte	0xc
	.byte	0x3e
	.4byte	0x49c
	.byte	0x10
	.uleb128 0xd
	.4byte	.LASF67
	.byte	0xc
	.byte	0x3f
	.4byte	0x49c
	.byte	0x14
	.uleb128 0xd
	.4byte	.LASF68
	.byte	0xc
	.byte	0x40
	.4byte	0x49c
	.byte	0x18
	.uleb128 0xd
	.4byte	.LASF69
	.byte	0xc
	.byte	0x43
	.4byte	0x49c
	.byte	0x1c
	.uleb128 0xd
	.4byte	.LASF70
	.byte	0xc
	.byte	0x46
	.4byte	0x49c
	.byte	0x20
	.uleb128 0xd
	.4byte	.LASF71
	.byte	0xc
	.byte	0x49
	.4byte	0x49c
	.byte	0x24
	.byte	0
	.uleb128 0x8
	.4byte	.LASF72
	.byte	0xd
	.byte	0xf
	.4byte	0x496
	.uleb128 0x6
	.byte	0x8
	.4byte	0x406
	.uleb128 0x2
	.4byte	.LASF73
	.byte	0xd
	.byte	0x12
	.4byte	0x103
	.uleb128 0x18
	.4byte	.LASF74
	.byte	0x40
	.byte	0xe
	.2byte	0x137
	.4byte	0x551
	.uleb128 0x19
	.4byte	.LASF75
	.byte	0xe
	.2byte	0x138
	.4byte	0x103
	.byte	0
	.uleb128 0x19
	.4byte	.LASF76
	.byte	0xe
	.2byte	0x139
	.4byte	0x103
	.byte	0x4
	.uleb128 0x19
	.4byte	.LASF77
	.byte	0xe
	.2byte	0x13a
	.4byte	0x103
	.byte	0x8
	.uleb128 0x19
	.4byte	.LASF78
	.byte	0xe
	.2byte	0x13b
	.4byte	0x103
	.byte	0xc
	.uleb128 0x19
	.4byte	.LASF79
	.byte	0xe
	.2byte	0x13c
	.4byte	0x103
	.byte	0x10
	.uleb128 0x19
	.4byte	.LASF80
	.byte	0xe
	.2byte	0x13d
	.4byte	0x103
	.byte	0x14
	.uleb128 0x19
	.4byte	.LASF81
	.byte	0xe
	.2byte	0x13e
	.4byte	0x103
	.byte	0x18
	.uleb128 0x19
	.4byte	.LASF82
	.byte	0xe
	.2byte	0x13f
	.4byte	0xed
	.byte	0x1c
	.uleb128 0x19
	.4byte	.LASF83
	.byte	0xe
	.2byte	0x140
	.4byte	0xed
	.byte	0x1d
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0xe
	.2byte	0x141
	.4byte	0xed
	.byte	0x1e
	.uleb128 0x19
	.4byte	.LASF85
	.byte	0xe
	.2byte	0x142
	.4byte	0xed
	.byte	0x1f
	.uleb128 0x19
	.4byte	.LASF86
	.byte	0xe
	.2byte	0x143
	.4byte	0x551
	.byte	0x20
	.byte	0
	.uleb128 0xa
	.4byte	0xed
	.4byte	0x561
	.uleb128 0x14
	.4byte	0x40
	.byte	0x1f
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF87
	.byte	0xe
	.2byte	0x144
	.4byte	0x4a7
	.uleb128 0x18
	.4byte	.LASF88
	.byte	0x30
	.byte	0xe
	.2byte	0x146
	.4byte	0x5ef
	.uleb128 0x19
	.4byte	.LASF29
	.byte	0xe
	.2byte	0x147
	.4byte	0xe2
	.byte	0
	.uleb128 0x1b
	.string	"end"
	.byte	0xe
	.2byte	0x147
	.4byte	0xe2
	.byte	0x8
	.uleb128 0x19
	.4byte	.LASF89
	.byte	0xe
	.2byte	0x148
	.4byte	0xe2
	.byte	0x10
	.uleb128 0x19
	.4byte	.LASF90
	.byte	0xe
	.2byte	0x148
	.4byte	0xe2
	.byte	0x18
	.uleb128 0x19
	.4byte	.LASF91
	.byte	0xe
	.2byte	0x149
	.4byte	0xe2
	.byte	0x20
	.uleb128 0x19
	.4byte	.LASF92
	.byte	0xe
	.2byte	0x14a
	.4byte	0xed
	.byte	0x28
	.uleb128 0x19
	.4byte	.LASF93
	.byte	0xe
	.2byte	0x14a
	.4byte	0xed
	.byte	0x29
	.uleb128 0x1b
	.string	"os"
	.byte	0xe
	.2byte	0x14a
	.4byte	0xed
	.byte	0x2a
	.uleb128 0x19
	.4byte	.LASF94
	.byte	0xe
	.2byte	0x14b
	.4byte	0xed
	.byte	0x2b
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF95
	.byte	0xe
	.2byte	0x14c
	.4byte	0x56d
	.uleb128 0x1c
	.4byte	.LASF96
	.2byte	0x280
	.byte	0xe
	.2byte	0x152
	.4byte	0x798
	.uleb128 0x19
	.4byte	.LASF97
	.byte	0xe
	.2byte	0x158
	.4byte	0x798
	.byte	0
	.uleb128 0x19
	.4byte	.LASF98
	.byte	0xe
	.2byte	0x159
	.4byte	0x561
	.byte	0x8
	.uleb128 0x19
	.4byte	.LASF99
	.byte	0xe
	.2byte	0x15a
	.4byte	0xe2
	.byte	0x48
	.uleb128 0x19
	.4byte	.LASF100
	.byte	0xe
	.2byte	0x15d
	.4byte	0x119
	.byte	0x50
	.uleb128 0x19
	.4byte	.LASF101
	.byte	0xe
	.2byte	0x15f
	.4byte	0x12a
	.byte	0x58
	.uleb128 0x19
	.4byte	.LASF102
	.byte	0xe
	.2byte	0x160
	.4byte	0x119
	.byte	0x60
	.uleb128 0x19
	.4byte	.LASF103
	.byte	0xe
	.2byte	0x161
	.4byte	0x4e
	.byte	0x68
	.uleb128 0x19
	.4byte	.LASF104
	.byte	0xe
	.2byte	0x163
	.4byte	0x12a
	.byte	0x70
	.uleb128 0x19
	.4byte	.LASF105
	.byte	0xe
	.2byte	0x164
	.4byte	0x119
	.byte	0x78
	.uleb128 0x19
	.4byte	.LASF106
	.byte	0xe
	.2byte	0x165
	.4byte	0x4e
	.byte	0x80
	.uleb128 0x19
	.4byte	.LASF107
	.byte	0xe
	.2byte	0x167
	.4byte	0x12a
	.byte	0x88
	.uleb128 0x19
	.4byte	.LASF108
	.byte	0xe
	.2byte	0x168
	.4byte	0x119
	.byte	0x90
	.uleb128 0x19
	.4byte	.LASF109
	.byte	0xe
	.2byte	0x169
	.4byte	0x4e
	.byte	0x98
	.uleb128 0x19
	.4byte	.LASF110
	.byte	0xe
	.2byte	0x16b
	.4byte	0x12a
	.byte	0xa0
	.uleb128 0x19
	.4byte	.LASF111
	.byte	0xe
	.2byte	0x16c
	.4byte	0x119
	.byte	0xa8
	.uleb128 0x19
	.4byte	.LASF112
	.byte	0xe
	.2byte	0x16d
	.4byte	0x4e
	.byte	0xb0
	.uleb128 0x1b
	.string	"os"
	.byte	0xe
	.2byte	0x171
	.4byte	0x5ef
	.byte	0xb8
	.uleb128 0x1b
	.string	"ep"
	.byte	0xe
	.2byte	0x172
	.4byte	0xe2
	.byte	0xe8
	.uleb128 0x19
	.4byte	.LASF113
	.byte	0xe
	.2byte	0x174
	.4byte	0xe2
	.byte	0xf0
	.uleb128 0x19
	.4byte	.LASF114
	.byte	0xe
	.2byte	0x174
	.4byte	0xe2
	.byte	0xf8
	.uleb128 0x1d
	.4byte	.LASF115
	.byte	0xe
	.2byte	0x176
	.4byte	0x5c
	.2byte	0x100
	.uleb128 0x1d
	.4byte	.LASF116
	.byte	0xe
	.2byte	0x177
	.4byte	0xe2
	.2byte	0x108
	.uleb128 0x1d
	.4byte	.LASF117
	.byte	0xe
	.2byte	0x179
	.4byte	0xe2
	.2byte	0x110
	.uleb128 0x1d
	.4byte	.LASF118
	.byte	0xe
	.2byte	0x17a
	.4byte	0xe2
	.2byte	0x118
	.uleb128 0x1d
	.4byte	.LASF119
	.byte	0xe
	.2byte	0x17b
	.4byte	0xe2
	.2byte	0x120
	.uleb128 0x1d
	.4byte	.LASF120
	.byte	0xe
	.2byte	0x17c
	.4byte	0xe2
	.2byte	0x128
	.uleb128 0x1e
	.string	"kbd"
	.byte	0xe
	.2byte	0x17d
	.4byte	0x79e
	.2byte	0x130
	.uleb128 0x1d
	.4byte	.LASF121
	.byte	0xe
	.2byte	0x180
	.4byte	0x4e
	.2byte	0x138
	.uleb128 0x1d
	.4byte	.LASF122
	.byte	0xe
	.2byte	0x18d
	.4byte	0x4e
	.2byte	0x13c
	.uleb128 0x1e
	.string	"lmb"
	.byte	0xe
	.2byte	0x190
	.4byte	0x298
	.2byte	0x140
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x561
	.uleb128 0x6
	.byte	0x8
	.4byte	0x3fb
	.uleb128 0x1a
	.4byte	.LASF123
	.byte	0xe
	.2byte	0x192
	.4byte	0x5fb
	.uleb128 0x1f
	.4byte	.LASF124
	.byte	0xe
	.2byte	0x194
	.4byte	0x7a4
	.uleb128 0xa
	.4byte	0x62
	.4byte	0x7cc
	.uleb128 0x14
	.4byte	0x40
	.byte	0x1f
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF125
	.byte	0x2
	.2byte	0x11a
	.4byte	0xe2
	.uleb128 0xa
	.4byte	0xa7
	.4byte	0x7e3
	.uleb128 0xb
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF126
	.byte	0x2
	.2byte	0x11c
	.4byte	0x7d8
	.uleb128 0x1f
	.4byte	.LASF127
	.byte	0x2
	.2byte	0x159
	.4byte	0xe2
	.uleb128 0x1f
	.4byte	.LASF128
	.byte	0x2
	.2byte	0x15a
	.4byte	0xe2
	.uleb128 0x1f
	.4byte	.LASF129
	.byte	0x2
	.2byte	0x15b
	.4byte	0xe2
	.uleb128 0xa
	.4byte	0x62
	.4byte	0x824
	.uleb128 0x12
	.4byte	0x40
	.2byte	0x3ff
	.byte	0
	.uleb128 0x20
	.byte	0x18
	.byte	0xf
	.2byte	0x104
	.4byte	0x855
	.uleb128 0x19
	.4byte	.LASF29
	.byte	0xf
	.2byte	0x105
	.4byte	0x40
	.byte	0
	.uleb128 0x19
	.4byte	.LASF26
	.byte	0xf
	.2byte	0x106
	.4byte	0x40
	.byte	0x8
	.uleb128 0x19
	.4byte	.LASF130
	.byte	0xf
	.2byte	0x107
	.4byte	0x4e
	.byte	0x10
	.byte	0
	.uleb128 0x18
	.4byte	.LASF131
	.byte	0xd0
	.byte	0xf
	.2byte	0x101
	.4byte	0x88a
	.uleb128 0x19
	.4byte	.LASF132
	.byte	0xf
	.2byte	0x102
	.4byte	0x4e
	.byte	0
	.uleb128 0x1b
	.string	"end"
	.byte	0xf
	.2byte	0x103
	.4byte	0x40
	.byte	0x8
	.uleb128 0x19
	.4byte	.LASF133
	.byte	0xf
	.2byte	0x108
	.4byte	0x88a
	.byte	0x10
	.byte	0
	.uleb128 0xa
	.4byte	0x824
	.4byte	0x89a
	.uleb128 0x14
	.4byte	0x40
	.byte	0x7
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF131
	.byte	0xf
	.2byte	0x10b
	.4byte	0x855
	.uleb128 0x8
	.4byte	.LASF134
	.byte	0x10
	.byte	0x11
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF135
	.byte	0x10
	.byte	0x12
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF136
	.byte	0x10
	.byte	0x13
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF137
	.byte	0x10
	.byte	0x14
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF138
	.byte	0x10
	.byte	0x15
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF139
	.byte	0x10
	.byte	0x16
	.4byte	0xe2
	.uleb128 0x8
	.4byte	.LASF140
	.byte	0x10
	.byte	0x17
	.4byte	0xe2
	.uleb128 0xc
	.4byte	.LASF141
	.byte	0x4
	.byte	0x11
	.byte	0x32
	.4byte	0x90c
	.uleb128 0xd
	.4byte	.LASF142
	.byte	0x11
	.byte	0x33
	.4byte	0x103
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.4byte	0x29
	.uleb128 0x21
	.4byte	0x922
	.uleb128 0xf
	.4byte	0x12a
	.uleb128 0xf
	.4byte	0x4e
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF143
	.byte	0x11
	.2byte	0x122
	.4byte	0x92e
	.uleb128 0x6
	.byte	0x8
	.4byte	0x912
	.uleb128 0xa
	.4byte	0xa7
	.4byte	0x944
	.uleb128 0x14
	.4byte	0x40
	.byte	0x5
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF144
	.byte	0x11
	.2byte	0x201
	.4byte	0x8f3
	.uleb128 0x1f
	.4byte	.LASF145
	.byte	0x11
	.2byte	0x202
	.4byte	0x8f3
	.uleb128 0x1f
	.4byte	.LASF146
	.byte	0x11
	.2byte	0x204
	.4byte	0x8f3
	.uleb128 0x1f
	.4byte	.LASF147
	.byte	0x11
	.2byte	0x209
	.4byte	0x7bc
	.uleb128 0x1f
	.4byte	.LASF148
	.byte	0x11
	.2byte	0x20a
	.4byte	0x7bc
	.uleb128 0xa
	.4byte	0x62
	.4byte	0x990
	.uleb128 0x14
	.4byte	0x40
	.byte	0x3f
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF149
	.byte	0x11
	.2byte	0x20b
	.4byte	0x980
	.uleb128 0x1f
	.4byte	.LASF150
	.byte	0x11
	.2byte	0x20d
	.4byte	0x934
	.uleb128 0x1f
	.4byte	.LASF151
	.byte	0x11
	.2byte	0x20e
	.4byte	0x934
	.uleb128 0x1f
	.4byte	.LASF152
	.byte	0x11
	.2byte	0x20f
	.4byte	0x8f3
	.uleb128 0x1f
	.4byte	.LASF153
	.byte	0x11
	.2byte	0x210
	.4byte	0x8f3
	.uleb128 0x1f
	.4byte	.LASF154
	.byte	0x11
	.2byte	0x211
	.4byte	0x90c
	.uleb128 0xa
	.4byte	0x90c
	.4byte	0x9e8
	.uleb128 0x14
	.4byte	0x40
	.byte	0x3
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF155
	.byte	0x11
	.2byte	0x212
	.4byte	0x9d8
	.uleb128 0x1f
	.4byte	.LASF156
	.byte	0x11
	.2byte	0x213
	.4byte	0x90c
	.uleb128 0x1f
	.4byte	.LASF157
	.byte	0x11
	.2byte	0x214
	.4byte	0x4e
	.uleb128 0xa
	.4byte	0xb1
	.4byte	0xa1c
	.uleb128 0x14
	.4byte	0x40
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.4byte	0xa0c
	.uleb128 0x1f
	.4byte	.LASF158
	.byte	0x11
	.2byte	0x215
	.4byte	0xa1c
	.uleb128 0x1f
	.4byte	.LASF159
	.byte	0x11
	.2byte	0x216
	.4byte	0xa1c
	.uleb128 0x1f
	.4byte	.LASF160
	.byte	0x11
	.2byte	0x21a
	.4byte	0xd7
	.uleb128 0x1f
	.4byte	.LASF161
	.byte	0x11
	.2byte	0x21b
	.4byte	0xd7
	.uleb128 0x1f
	.4byte	.LASF162
	.byte	0x11
	.2byte	0x21d
	.4byte	0x4e
	.uleb128 0x1f
	.4byte	.LASF163
	.byte	0x11
	.2byte	0x224
	.4byte	0x813
	.uleb128 0x1f
	.4byte	.LASF164
	.byte	0x11
	.2byte	0x226
	.4byte	0xb6
	.uleb128 0x1f
	.4byte	.LASF165
	.byte	0x11
	.2byte	0x228
	.4byte	0xb6
	.uleb128 0x1f
	.4byte	.LASF166
	.byte	0x11
	.2byte	0x230
	.4byte	0x8f3
	.uleb128 0x22
	.4byte	.LASF182
	.byte	0x7
	.byte	0x4
	.4byte	0x6e
	.byte	0x11
	.2byte	0x286
	.4byte	0xab8
	.uleb128 0x23
	.4byte	.LASF167
	.byte	0
	.uleb128 0x23
	.4byte	.LASF168
	.byte	0x1
	.uleb128 0x23
	.4byte	.LASF169
	.byte	0x2
	.uleb128 0x23
	.4byte	.LASF170
	.byte	0x3
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF171
	.byte	0x11
	.2byte	0x28c
	.4byte	0xa8d
	.uleb128 0x8
	.4byte	.LASF172
	.byte	0x12
	.byte	0x91
	.4byte	0x5c
	.uleb128 0x24
	.4byte	.LASF173
	.2byte	0x1000
	.byte	0x12
	.byte	0x9b
	.4byte	0xaf5
	.uleb128 0x13
	.string	"crc"
	.byte	0x12
	.byte	0x9c
	.4byte	0xf8
	.byte	0
	.uleb128 0xd
	.4byte	.LASF174
	.byte	0x12
	.byte	0xa0
	.4byte	0xaf5
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.4byte	0x34
	.4byte	0xb06
	.uleb128 0x12
	.4byte	0x40
	.2byte	0xffb
	.byte	0
	.uleb128 0x2
	.4byte	.LASF175
	.byte	0x12
	.byte	0xa1
	.4byte	0xacf
	.uleb128 0xa
	.4byte	0x3b
	.4byte	0xb1c
	.uleb128 0xb
	.byte	0
	.uleb128 0x4
	.4byte	0xb11
	.uleb128 0x8
	.4byte	.LASF176
	.byte	0x12
	.byte	0xac
	.4byte	0xb1c
	.uleb128 0x8
	.4byte	.LASF177
	.byte	0x12
	.byte	0xad
	.4byte	0xb37
	.uleb128 0x6
	.byte	0x8
	.4byte	0xb06
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF178
	.uleb128 0x25
	.4byte	.LASF183
	.byte	0x1
	.byte	0x17
	.4byte	0x4e
	.8byte	.LFB198
	.8byte	.LFE198-.LFB198
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
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
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
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
	.uleb128 0x4
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB198
	.8byte	.LFE198-.LFB198
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB198
	.8byte	.LFE198
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF100:
	.string	"fit_uname_cfg"
.LASF102:
	.string	"fit_uname_os"
.LASF16:
	.string	"ulong"
.LASF58:
	.string	"bi_boot_params"
.LASF144:
	.string	"net_gateway"
.LASF170:
	.string	"NETLOOP_FAIL"
.LASF42:
	.string	"bi_memsize"
.LASF103:
	.string	"fit_noffset_os"
.LASF79:
	.string	"ih_load"
.LASF168:
	.string	"NETLOOP_RESTART"
.LASF93:
	.string	"type"
.LASF92:
	.string	"comp"
.LASF24:
	.string	"select_hwpart"
.LASF135:
	.string	"FIQ_STACK_START"
.LASF63:
	.string	"totalsize"
.LASF159:
	.string	"net_null_ethaddr"
.LASF12:
	.string	"long long unsigned int"
.LASF68:
	.string	"last_comp_version"
.LASF34:
	.string	"lmb_property"
.LASF148:
	.string	"net_hostname"
.LASF6:
	.string	"long long int"
.LASF7:
	.string	"signed char"
.LASF75:
	.string	"ih_magic"
.LASF57:
	.string	"bi_arch_number"
.LASF97:
	.string	"legacy_hdr_os"
.LASF118:
	.string	"initrd_end"
.LASF96:
	.string	"bootm_headers"
.LASF124:
	.string	"images"
.LASF122:
	.string	"state"
.LASF3:
	.string	"long int"
.LASF132:
	.string	"nr_banks"
.LASF19:
	.string	"__be32"
.LASF175:
	.string	"env_t"
.LASF108:
	.string	"fit_uname_fdt"
.LASF139:
	.string	"_datarelro_start_ofs"
.LASF22:
	.string	"ide_bus_offset"
.LASF95:
	.string	"image_info_t"
.LASF146:
	.string	"net_dns_server"
.LASF160:
	.string	"net_our_vlan"
.LASF27:
	.string	"sector_count"
.LASF169:
	.string	"NETLOOP_SUCCESS"
.LASF157:
	.string	"net_rx_packet_len"
.LASF121:
	.string	"verify"
.LASF101:
	.string	"fit_hdr_os"
.LASF165:
	.string	"net_boot_file_expected_size_in_blocks"
.LASF145:
	.string	"net_netmask"
.LASF180:
	.string	"arch/arm/lib/asm-offsets.c"
.LASF127:
	.string	"load_addr"
.LASF38:
	.string	"memory"
.LASF161:
	.string	"net_native_vlan"
.LASF140:
	.string	"IRQ_STACK_START_IN"
.LASF5:
	.string	"unsigned int"
.LASF84:
	.string	"ih_type"
.LASF80:
	.string	"ih_ep"
.LASF60:
	.string	"bd_t"
.LASF147:
	.string	"net_nis_domain"
.LASF115:
	.string	"ft_addr"
.LASF9:
	.string	"__u8"
.LASF1:
	.string	"long unsigned int"
.LASF11:
	.string	"__u32"
.LASF65:
	.string	"off_dt_strings"
.LASF56:
	.string	"bi_busfreq"
.LASF105:
	.string	"fit_uname_rd"
.LASF23:
	.string	"name"
.LASF81:
	.string	"ih_dcrc"
.LASF174:
	.string	"data"
.LASF51:
	.string	"bi_bootflags"
.LASF26:
	.string	"size"
.LASF2:
	.string	"short unsigned int"
.LASF106:
	.string	"fit_noffset_rd"
.LASF142:
	.string	"s_addr"
.LASF117:
	.string	"initrd_start"
.LASF94:
	.string	"arch"
.LASF131:
	.string	"meminfo"
.LASF98:
	.string	"legacy_hdr_os_copy"
.LASF32:
	.string	"flash_info"
.LASF52:
	.string	"bi_ip_addr"
.LASF88:
	.string	"image_info"
.LASF53:
	.string	"bi_enetaddr"
.LASF182:
	.string	"net_loop_state"
.LASF20:
	.string	"errno"
.LASF91:
	.string	"load"
.LASF35:
	.string	"base"
.LASF71:
	.string	"size_dt_struct"
.LASF67:
	.string	"version"
.LASF158:
	.string	"net_bcast_ethaddr"
.LASF110:
	.string	"fit_hdr_setup"
.LASF111:
	.string	"fit_uname_setup"
.LASF129:
	.string	"save_size"
.LASF149:
	.string	"net_root_path"
.LASF82:
	.string	"ih_os"
.LASF128:
	.string	"save_addr"
.LASF48:
	.string	"bi_arm_freq"
.LASF64:
	.string	"off_dt_struct"
.LASF173:
	.string	"environment_s"
.LASF40:
	.string	"bd_info"
.LASF15:
	.string	"ushort"
.LASF177:
	.string	"env_ptr"
.LASF87:
	.string	"image_header_t"
.LASF123:
	.string	"bootm_headers_t"
.LASF39:
	.string	"reserved"
.LASF8:
	.string	"uchar"
.LASF70:
	.string	"size_dt_strings"
.LASF107:
	.string	"fit_hdr_fdt"
.LASF21:
	.string	"___strtok"
.LASF43:
	.string	"bi_flashstart"
.LASF164:
	.string	"net_boot_file_size"
.LASF89:
	.string	"image_start"
.LASF36:
	.string	"lmb_region"
.LASF171:
	.string	"net_state"
.LASF85:
	.string	"ih_comp"
.LASF116:
	.string	"ft_len"
.LASF59:
	.string	"bi_dram"
.LASF178:
	.string	"_Bool"
.LASF134:
	.string	"IRQ_STACK_START"
.LASF0:
	.string	"unsigned char"
.LASF78:
	.string	"ih_size"
.LASF153:
	.string	"net_server_ip"
.LASF113:
	.string	"rd_start"
.LASF130:
	.string	"node"
.LASF152:
	.string	"net_ip"
.LASF66:
	.string	"off_mem_rsvmap"
.LASF10:
	.string	"short int"
.LASF62:
	.string	"magic"
.LASF47:
	.string	"bi_sramsize"
.LASF114:
	.string	"rd_end"
.LASF99:
	.string	"legacy_hdr_valid"
.LASF112:
	.string	"fit_noffset_setup"
.LASF156:
	.string	"net_rx_packet"
.LASF126:
	.string	"__dtb_dt_begin"
.LASF49:
	.string	"bi_dsp_freq"
.LASF125:
	.string	"monitor_flash_len"
.LASF151:
	.string	"net_server_ethaddr"
.LASF18:
	.string	"uint32_t"
.LASF137:
	.string	"_datarelrolocal_start_ofs"
.LASF136:
	.string	"_datarel_start_ofs"
.LASF33:
	.string	"long double"
.LASF4:
	.string	"char"
.LASF109:
	.string	"fit_noffset_fdt"
.LASF44:
	.string	"bi_flashsize"
.LASF74:
	.string	"image_header"
.LASF181:
	.string	"/home/tim/2.4/uboot-imx6"
.LASF176:
	.string	"default_environment"
.LASF13:
	.string	"phys_addr_t"
.LASF46:
	.string	"bi_sramstart"
.LASF90:
	.string	"image_len"
.LASF28:
	.string	"flash_id"
.LASF77:
	.string	"ih_time"
.LASF61:
	.string	"fdt_header"
.LASF150:
	.string	"net_ethaddr"
.LASF133:
	.string	"bank"
.LASF72:
	.string	"working_fdt"
.LASF54:
	.string	"bi_ethspeed"
.LASF25:
	.string	"block_drvr"
.LASF37:
	.string	"region"
.LASF162:
	.string	"net_restart_wrap"
.LASF167:
	.string	"NETLOOP_CONTINUE"
.LASF55:
	.string	"bi_intfreq"
.LASF120:
	.string	"cmdline_end"
.LASF14:
	.string	"phys_size_t"
.LASF31:
	.string	"flash_info_t"
.LASF163:
	.string	"net_boot_file_name"
.LASF76:
	.string	"ih_hcrc"
.LASF172:
	.string	"env_name_spec"
.LASF17:
	.string	"uint8_t"
.LASF104:
	.string	"fit_hdr_rd"
.LASF179:
	.ascii	"GNU C11 7.3.0 -m"
	.string	"strict-align -march=armv8-a -mgeneral-regs-only -mlittle-endian -mabi=lp64 -g -Os -fno-builtin -ffreestanding -fno-stack-protector -fno-delete-null-pointer-checks -fstack-usage -fno-pic -ffunction-sections -fdata-sections -ffixed-r9 -fno-common -ffixed-x18"
.LASF69:
	.string	"boot_cpuid_phys"
.LASF30:
	.string	"protect"
.LASF166:
	.string	"net_ping_ip"
.LASF155:
	.string	"net_rx_packets"
.LASF86:
	.string	"ih_name"
.LASF50:
	.string	"bi_ddr_freq"
.LASF41:
	.string	"bi_memstart"
.LASF29:
	.string	"start"
.LASF183:
	.string	"main"
.LASF73:
	.string	"fdt32_t"
.LASF83:
	.string	"ih_arch"
.LASF45:
	.string	"bi_flashoffset"
.LASF138:
	.string	"_datarellocal_start_ofs"
.LASF143:
	.string	"push_packet"
.LASF154:
	.string	"net_tx_packet"
.LASF119:
	.string	"cmdline_start"
.LASF141:
	.string	"in_addr"
	.ident	"GCC: (GNU) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
