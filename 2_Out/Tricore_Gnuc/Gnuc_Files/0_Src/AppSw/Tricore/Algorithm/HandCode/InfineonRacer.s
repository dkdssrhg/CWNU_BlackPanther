	.file	"InfineonRacer.c"
.section .text,"ax",@progbits
.Ltext0:
.section .text.InfineonRacer_init,"ax",@progbits
	.align 1
	.global	InfineonRacer_init
	.type	InfineonRacer_init, @function
InfineonRacer_init:
.LFB713:
	.file 1 "0_Src/AppSw/Tricore/Algorithm/HandCode/InfineonRacer.c"
	.loc 1 49 0
	.loc 1 51 0
	movh	%d15, 16000
	movh.a	%a15, hi:IR_Motor
	.loc 1 50 0
	mov	%d4, 0
	call	IR_setMotor0En
.LVL0:
	.loc 1 51 0
	st.w	[%a15] lo:IR_Motor, %d15
	.loc 1 52 0
	mov	%d15, 0
	movh.a	%a15, hi:IR_Srv
	st.w	[%a15] lo:IR_Srv, %d15
	ret
.LFE713:
	.size	InfineonRacer_init, .-InfineonRacer_init
.section .text.InfineonRacer_detectLane,"ax",@progbits
	.align 1
	.global	InfineonRacer_detectLane
	.type	InfineonRacer_detectLane, @function
InfineonRacer_detectLane:
.LFB714:
	.loc 1 55 0
.LVL1:
	.loc 1 60 0
	movh.a	%a15, hi:index_left
	ld.w	%d15, [%a15] lo:index_left
	movh	%d2, 17022
	.loc 1 61 0
	movh.a	%a15, hi:index_right
	.loc 1 60 0
	sub.f	%d3, %d2, %d15
.LVL2:
	.loc 1 61 0
	ld.w	%d15, [%a15] lo:index_right
	sub.f	%d2, %d15, %d2
.LVL3:
	.loc 1 63 0
	sub.f	%d15, %d3, %d2
	movh	%d2, 16544
.LVL4:
	cmp.f	%d2, %d15, %d2
	jz.t	%d2, 2, .L3
	.loc 1 65 0
	movh	%d2, 48589
	addi	%d2, %d2, -13107
	movh.a	%a15, hi:IR_Srv
	st.w	[%a15] lo:IR_Srv, %d2
.L3:
	.loc 1 68 0
	movh	%d2, 49312
	cmp.f	%d2, %d15, %d2
	jz.t	%d2, 0, .L5
	.loc 1 70 0
	movh	%d2, 15821
	addi	%d2, %d2, -13107
	movh.a	%a15, hi:IR_Srv
	st.w	[%a15] lo:IR_Srv, %d2
.L5:
	.loc 1 73 0
	movh	%d2, 49312
	cmp.f	%d2, %d15, %d2
	jz.t	%d2, 2, .L2
	.loc 1 73 0 is_stmt 0 discriminator 1
	movh	%d2, 16544
	cmp.f	%d15, %d15, %d2
	jz.t	%d15, 0, .L2
	.loc 1 75 0 is_stmt 1
	mov	%d15, 0
	movh.a	%a15, hi:IR_Srv
	st.w	[%a15] lo:IR_Srv, %d15
.L2:
	ret
.LFE714:
	.size	InfineonRacer_detectLane, .-InfineonRacer_detectLane
.section .text.InfineonRacer_control,"ax",@progbits
	.align 1
	.global	InfineonRacer_control
	.type	InfineonRacer_control, @function
InfineonRacer_control:
.LFB715:
	.loc 1 79 0
	ret
.LFE715:
	.size	InfineonRacer_control, .-InfineonRacer_control
.section .text.FindIndex,"ax",@progbits
	.align 1
	.global	FindIndex
	.type	FindIndex, @function
FindIndex:
.LFB716:
	.loc 1 84 0
.LVL5:
	movh.a	%a2, hi:IR_LineScan
	.loc 1 84 0
	mov	%d7, 0
	.loc 1 91 0
	mov	%d2, 0
	.loc 1 98 0
	mov	%d15, 0
	.loc 1 85 0
	mov	%d3, 0
	lea	%a2, [%a2] lo:IR_LineScan
	.loc 1 100 0
	mov	%d5, 2000
	.loc 1 103 0
	movh	%d6, 16256
	lea	%a15, 63
.LVL6:
.L18:
	.loc 1 100 0
	addsc.a	%a3, %a2, %d15, 2
	ld.w	%d4, [%a3] 512
	jge.u	%d4, %d5, .L17
	.loc 1 102 0
	itof	%d4, %d15
	.loc 1 103 0
	add.f	%d2, %d2, %d6
.LVL7:
	.loc 1 102 0
	add.f	%d3, %d3, %d4
.LVL8:
	.loc 1 104 0
	add	%d7, 1
.L17:
	.loc 1 98 0 discriminator 2
	add	%d15, 1
.LVL9:
	loop	%a15, .L18
	.loc 1 107 0
	div.f	%d2, %d3, %d2
.LVL10:
	movh.a	%a15, hi:index_left
	movh.a	%a4, hi:pixel_count_cross
	st.w	[%a15] lo:index_left, %d2
.LVL11:
	st.w	[%a4] lo:pixel_count_cross, %d7
	.loc 1 92 0
	mov	%d2, 0
	.loc 1 111 0
	mov	%d15, 64
.LVL12:
	.loc 1 86 0
	mov	%d3, 0
.LVL13:
	.loc 1 113 0
	mov	%d5, 2000
	.loc 1 116 0
	movh	%d6, 16256
	lea	%a15, 63
.LVL14:
.L20:
	.loc 1 113 0
	addsc.a	%a3, %a2, %d15, 2
	ld.w	%d4, [%a3] 512
	jge.u	%d4, %d5, .L19
	.loc 1 115 0
	itof	%d4, %d15
	.loc 1 116 0
	add.f	%d2, %d2, %d6
.LVL15:
	.loc 1 115 0
	add.f	%d3, %d3, %d4
.LVL16:
	.loc 1 117 0
	add	%d7, 1
.L19:
	.loc 1 111 0 discriminator 2
	add	%d15, 1
.LVL17:
	loop	%a15, .L20
	.loc 1 120 0
	div.f	%d2, %d3, %d2
.LVL18:
	movh.a	%a15, hi:index_right
	st.w	[%a4] lo:pixel_count_cross, %d7
	st.w	[%a15] lo:index_right, %d2
.LVL19:
	ret
.LFE716:
	.size	FindIndex, .-FindIndex
.section .text.Find_Cross,"ax",@progbits
	.align 1
	.global	Find_Cross
	.type	Find_Cross, @function
Find_Cross:
.LFB717:
	.loc 1 125 0
	.loc 1 126 0
	movh.a	%a15, hi:pixel_count_cross
	ld.w	%d15, [%a15] lo:pixel_count_cross
	lt	%d15, %d15, 50
	jnz	%d15, .L23
	.loc 1 128 0
	movh.a	%a12, hi:status
	ld.bu	%d15, [%a12] lo:status
	jz	%d15, .L27
.L25:
	.loc 1 135 0
	jeq	%d15, 1, .L28
.L26:
	.loc 1 141 0
	mov	%d15, 0
	st.w	[%a15] lo:pixel_count_cross, %d15
.L23:
	ret
.L27:
	.loc 1 130 0
	mov	%d2, 1
	.loc 1 131 0
	mov	%d4, 1
	.loc 1 130 0
	st.b	[%a12] lo:status, %d2
	.loc 1 131 0
	call	IR_setBeeperOn
.LVL20:
	.loc 1 132 0
	movh.a	%a2, hi:status_count
	st.w	[%a2] lo:status_count, %d15
	ld.bu	%d15, [%a12] lo:status
	j	.L25
.L28:
	.loc 1 137 0
	mov	%d15, 0
	.loc 1 138 0
	mov	%d4, 0
	.loc 1 137 0
	st.b	[%a12] lo:status, %d15
	.loc 1 139 0
	mov	%d15, 0
	.loc 1 138 0
	call	IR_setBeeperOn
.LVL21:
	.loc 1 139 0
	movh.a	%a2, hi:status_count
	st.w	[%a2] lo:status_count, %d15
	j	.L26
.LFE717:
	.size	Find_Cross, .-Find_Cross
.section .text.Control_Velocity,"ax",@progbits
	.align 1
	.global	Control_Velocity
	.type	Control_Velocity, @function
Control_Velocity:
.LFB718:
	.loc 1 146 0
	.loc 1 147 0
	movh.a	%a15, hi:status
	ld.bu	%d15, [%a15] lo:status
	jnz	%d15, .L30
	.loc 1 149 0
	movh	%d15, 16000
	movh.a	%a15, hi:IR_Motor
	st.w	[%a15] lo:IR_Motor, %d15
	ret
.L30:
	.loc 1 152 0
	jne	%d15, 1, .L29
	.loc 1 154 0
	movh	%d15, 15898
	addi	%d15, %d15, -26214
	movh.a	%a15, hi:IR_Motor
	st.w	[%a15] lo:IR_Motor, %d15
.L29:
	ret
.LFE718:
	.size	Control_Velocity, .-Control_Velocity
	.global	pixel_count_cross
.section .bss.pixel_count_cross,"aw",@nobits
	.align 2
	.type	pixel_count_cross, @object
	.size	pixel_count_cross, 4
pixel_count_cross:
	.zero	4
	.global	index_right
.section .bss.index_right,"aw",@nobits
	.align 2
	.type	index_right, @object
	.size	index_right, 4
index_right:
	.zero	4
	.global	index_left
.section .bss.index_left,"aw",@nobits
	.align 2
	.type	index_left, @object
	.size	index_left, 4
index_left:
	.zero	4
	.global	status_count
.section .bss.status_count,"aw",@nobits
	.align 2
	.type	status_count, @object
	.size	status_count, 4
status_count:
	.zero	4
	.global	status
.section .bss.status,"aw",@nobits
	.type	status, @object
	.size	status, 1
status:
	.zero	1
	.global	IR_Ctrl
.section .data.IR_Ctrl,"aw",@progbits
	.align 2
	.type	IR_Ctrl, @object
	.size	IR_Ctrl, 12
IR_Ctrl:
	.word	64
	.word	64
	.byte	0
	.zero	3
.section .debug_frame,"",@progbits
.Lframe0:
	.uaword	.LECIE0-.LSCIE0
.LSCIE0:
	.uaword	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 1
	.uleb128 0x1b
	.byte	0xc
	.uleb128 0x1a
	.uleb128 0
	.align 2
.LECIE0:
.LSFDE0:
	.uaword	.LEFDE0-.LASFDE0
.LASFDE0:
	.uaword	.Lframe0
	.uaword	.LFB713
	.uaword	.LFE713-.LFB713
	.align 2
.LEFDE0:
.LSFDE2:
	.uaword	.LEFDE2-.LASFDE2
.LASFDE2:
	.uaword	.Lframe0
	.uaword	.LFB714
	.uaword	.LFE714-.LFB714
	.align 2
.LEFDE2:
.LSFDE4:
	.uaword	.LEFDE4-.LASFDE4
.LASFDE4:
	.uaword	.Lframe0
	.uaword	.LFB715
	.uaword	.LFE715-.LFB715
	.align 2
.LEFDE4:
.LSFDE6:
	.uaword	.LEFDE6-.LASFDE6
.LASFDE6:
	.uaword	.Lframe0
	.uaword	.LFB716
	.uaword	.LFE716-.LFB716
	.align 2
.LEFDE6:
.LSFDE8:
	.uaword	.LEFDE8-.LASFDE8
.LASFDE8:
	.uaword	.Lframe0
	.uaword	.LFB717
	.uaword	.LFE717-.LFB717
	.align 2
.LEFDE8:
.LSFDE10:
	.uaword	.LEFDE10-.LASFDE10
.LASFDE10:
	.uaword	.Lframe0
	.uaword	.LFB718
	.uaword	.LFE718-.LFB718
	.align 2
.LEFDE10:
.section .text,"ax",@progbits
.Letext0:
	.file 2 "0_Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Std/Platform_Types.h"
	.file 3 "0_Src/BaseSw/iLLD/TC23A/Tricore/Cpu/Std/Ifx_Types.h"
	.file 4 "0_Src/AppSw/Tricore/Algorithm/HandCode/InfineonRacer.h"
	.file 5 "0_Src/AppSw/Tricore/SnsAct/BasicLineScan.h"
	.file 6 "0_Src/AppSw/Tricore/SnsAct/BasicGtmTom.h"
	.file 7 "0_Src/BaseSw/iLLD/TC23A/Tricore/_Impl/IfxCpu_cfg.h"
	.file 8 "0_Src/BaseSw/Service/CpuGeneric/SysSe/Bsp/Assert.h"
	.file 9 "0_Src/AppSw/Tricore/SnsAct/BasicPort.h"
.section .debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x755
	.uahalf	0x3
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.string	"GNU C 4.9.4 build on 2017-01-30 -mlicense-dir=c:\\hightec\\toolchains\\tricore\\v4.9.1.0-infineon-1.1\\bin\\../lib/gcc/tricore/4.9.4/../../../../licenses -mtc161 -g -O2 -std=c99 -fno-common -fstrict-volatile-bitfields -ffunction-sections -fdata-sections"
	.byte	0x1
	.string	"0_Src/AppSw/Tricore/Algorithm/HandCode/InfineonRacer.c"
	.string	"C:\\\\Tools\\\\Workspaces\\\\CWNU_BlackPanther"
	.uaword	.Ldebug_ranges0+0
	.uaword	0
	.uaword	0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.string	"float"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.string	"long int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.string	"long unsigned int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.string	"signed char"
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.string	"unsigned char"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.string	"short int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.string	"short unsigned int"
	.uleb128 0x3
	.string	"sint32"
	.byte	0x2
	.byte	0x5c
	.uaword	0x17e
	.uleb128 0x3
	.string	"uint32"
	.byte	0x2
	.byte	0x5d
	.uaword	0x18a
	.uleb128 0x3
	.string	"float32"
	.byte	0x2
	.byte	0x5e
	.uaword	0x175
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.string	"double"
	.uleb128 0x3
	.string	"boolean"
	.byte	0x2
	.byte	0x68
	.uaword	0x1b5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.string	"long long int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.string	"long long unsigned int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.string	"char"
	.uleb128 0x4
	.byte	0x4
	.uaword	0x266
	.uleb128 0x5
	.uleb128 0x6
	.byte	0x8
	.byte	0x3
	.byte	0x77
	.uaword	0x28d
	.uleb128 0x7
	.string	"module"
	.byte	0x3
	.byte	0x79
	.uaword	0x260
	.byte	0
	.uleb128 0x7
	.string	"index"
	.byte	0x3
	.byte	0x7a
	.uaword	0x1e9
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.string	"IfxModule_IndexMap"
	.byte	0x3
	.byte	0x7b
	.uaword	0x267
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.string	"unsigned int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.string	"sizetype"
	.uleb128 0x8
	.byte	0x1
	.byte	0x7
	.byte	0x74
	.uaword	0x2f1
	.uleb128 0x9
	.string	"IfxCpu_Index_0"
	.sleb128 0
	.uleb128 0x9
	.string	"IfxCpu_Index_none"
	.sleb128 1
	.byte	0
	.uleb128 0x6
	.byte	0xc
	.byte	0x4
	.byte	0x1b
	.uaword	0x330
	.uleb128 0x7
	.string	"Ls0Margin"
	.byte	0x4
	.byte	0x1c
	.uaword	0x1e9
	.byte	0
	.uleb128 0x7
	.string	"Ls1Margin"
	.byte	0x4
	.byte	0x1d
	.uaword	0x1e9
	.byte	0x4
	.uleb128 0x7
	.string	"basicTest"
	.byte	0x4
	.byte	0x1e
	.uaword	0x21e
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.string	"InfineonRacer_t"
	.byte	0x4
	.byte	0x1f
	.uaword	0x2f1
	.uleb128 0xa
	.uahalf	0x400
	.byte	0x5
	.byte	0x1b
	.uaword	0x363
	.uleb128 0x7
	.string	"adcResult"
	.byte	0x5
	.byte	0x1c
	.uaword	0x363
	.byte	0
	.byte	0
	.uleb128 0xb
	.uaword	0x1f7
	.uaword	0x379
	.uleb128 0xc
	.uaword	0x2b7
	.byte	0x1
	.uleb128 0xc
	.uaword	0x2b7
	.byte	0x7f
	.byte	0
	.uleb128 0x3
	.string	"IR_LineScan_t"
	.byte	0x5
	.byte	0x1d
	.uaword	0x347
	.uleb128 0x6
	.byte	0x8
	.byte	0x6
	.byte	0x28
	.uaword	0x3bb
	.uleb128 0x7
	.string	"Motor0Vol"
	.byte	0x6
	.byte	0x29
	.uaword	0x205
	.byte	0
	.uleb128 0x7
	.string	"Motor1Vol"
	.byte	0x6
	.byte	0x2a
	.uaword	0x205
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.string	"IR_Motor_t"
	.byte	0x6
	.byte	0x2b
	.uaword	0x38e
	.uleb128 0x6
	.byte	0x4
	.byte	0x6
	.byte	0x2d
	.uaword	0x3e4
	.uleb128 0x7
	.string	"Angle"
	.byte	0x6
	.byte	0x2e
	.uaword	0x205
	.byte	0
	.byte	0
	.uleb128 0x3
	.string	"IR_Srv_t"
	.byte	0x6
	.byte	0x2f
	.uaword	0x3cd
	.uleb128 0xd
	.string	"now_status"
	.byte	0x1
	.byte	0x1
	.byte	0xf
	.uaword	0x41b
	.uleb128 0x9
	.string	"normal"
	.sleb128 0
	.uleb128 0x9
	.string	"v_limit"
	.sleb128 1
	.byte	0
	.uleb128 0x3
	.string	"status_t"
	.byte	0x1
	.byte	0x12
	.uaword	0x3f4
	.uleb128 0xe
	.byte	0x1
	.string	"InfineonRacer_init"
	.byte	0x1
	.byte	0x31
	.byte	0x1
	.uaword	.LFB713
	.uaword	.LFE713
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uaword	0x462
	.uleb128 0xf
	.uaword	.LVL0
	.uaword	0x71e
	.uleb128 0x10
	.byte	0x1
	.byte	0x54
	.byte	0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.string	"InfineonRacer_detectLane"
	.byte	0x1
	.byte	0x37
	.byte	0x1
	.uaword	.LFB714
	.uaword	.LFE714
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uaword	0x4bd
	.uleb128 0x11
	.string	"error_left"
	.byte	0x1
	.byte	0x39
	.uaword	0x175
	.uaword	.LLST0
	.uleb128 0x11
	.string	"error_right"
	.byte	0x1
	.byte	0x3a
	.uaword	0x175
	.uaword	.LLST1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.string	"InfineonRacer_control"
	.byte	0x1
	.byte	0x4f
	.byte	0x1
	.uaword	.LFB715
	.uaword	.LFE715
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uleb128 0xe
	.byte	0x1
	.string	"FindIndex"
	.byte	0x1
	.byte	0x53
	.byte	0x1
	.uaword	.LFB716
	.uaword	.LFE716
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uaword	0x59b
	.uleb128 0x11
	.string	"pixel_left_sum"
	.byte	0x1
	.byte	0x55
	.uaword	0x175
	.uaword	.LLST2
	.uleb128 0x11
	.string	"pixel_right_sum"
	.byte	0x1
	.byte	0x56
	.uaword	0x175
	.uaword	.LLST3
	.uleb128 0x11
	.string	"pixel_left"
	.byte	0x1
	.byte	0x58
	.uaword	0x19f
	.uaword	.LLST4
	.uleb128 0x11
	.string	"pixel_right"
	.byte	0x1
	.byte	0x59
	.uaword	0x19f
	.uaword	.LLST5
	.uleb128 0x11
	.string	"pixel_LeftCount"
	.byte	0x1
	.byte	0x5b
	.uaword	0x175
	.uaword	.LLST6
	.uleb128 0x11
	.string	"pixel_RightCount"
	.byte	0x1
	.byte	0x5c
	.uaword	0x175
	.uaword	.LLST7
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.string	"Find_Cross"
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.uaword	.LFB717
	.uaword	.LFE717
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uaword	0x5de
	.uleb128 0x13
	.uaword	.LVL20
	.uaword	0x73d
	.uaword	0x5cd
	.uleb128 0x10
	.byte	0x1
	.byte	0x54
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0xf
	.uaword	.LVL21
	.uaword	0x73d
	.uleb128 0x10
	.byte	0x1
	.byte	0x54
	.byte	0x2
	.byte	0x7f
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.string	"Control_Velocity"
	.byte	0x1
	.byte	0x91
	.byte	0x1
	.uaword	.LFB718
	.uaword	.LFE718
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.uleb128 0xb
	.uaword	0x28d
	.uaword	0x60f
	.uleb128 0xc
	.uaword	0x2b7
	.byte	0
	.byte	0
	.uleb128 0x14
	.string	"IfxCpu_cfg_indexMap"
	.byte	0x7
	.byte	0x90
	.uaword	0x62c
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.uaword	0x5ff
	.uleb128 0x14
	.string	"Assert_verboseLevel"
	.byte	0x8
	.byte	0x79
	.uaword	0x1f7
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.string	"IR_Ctrl"
	.byte	0x1
	.byte	0x1b
	.uaword	0x330
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	IR_Ctrl
	.uleb128 0x14
	.string	"IR_LineScan"
	.byte	0x5
	.byte	0x22
	.uaword	0x379
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.string	"IR_Motor"
	.byte	0x6
	.byte	0x3a
	.uaword	0x3bb
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.string	"IR_Srv"
	.byte	0x6
	.byte	0x3b
	.uaword	0x3e4
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.string	"status"
	.byte	0x1
	.byte	0x1e
	.uaword	0x41b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	status
	.uleb128 0x16
	.string	"status_count"
	.byte	0x1
	.byte	0x20
	.uaword	0x19f
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	status_count
	.uleb128 0x16
	.string	"index_left"
	.byte	0x1
	.byte	0x22
	.uaword	0x175
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	index_left
	.uleb128 0x16
	.string	"index_right"
	.byte	0x1
	.byte	0x23
	.uaword	0x175
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	index_right
	.uleb128 0x16
	.string	"pixel_count_cross"
	.byte	0x1
	.byte	0x25
	.uaword	0x19f
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.uaword	pixel_count_cross
	.uleb128 0x17
	.byte	0x1
	.string	"IR_setMotor0En"
	.byte	0x9
	.byte	0x45
	.byte	0x1
	.byte	0x1
	.uaword	0x73d
	.uleb128 0x18
	.uaword	0x21e
	.byte	0
	.uleb128 0x19
	.byte	0x1
	.string	"IR_setBeeperOn"
	.byte	0x6
	.byte	0x46
	.byte	0x1
	.byte	0x1
	.uleb128 0x18
	.uaword	0x21e
	.byte	0
	.byte	0
.section .debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
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
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
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
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x4
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
	.uleb128 0x9
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
.section .debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LVL1
	.uaword	.LVL2
	.uahalf	0x13
	.byte	0xf4
	.uleb128 0x175
	.byte	0x4
	.uaword	0x427e0000
	.byte	0x3
	.uaword	index_left
	.byte	0xf6
	.byte	0x4
	.uleb128 0x175
	.byte	0x1c
	.byte	0x9f
	.uaword	.LVL2
	.uaword	.LFE714
	.uahalf	0x1
	.byte	0x53
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LVL1
	.uaword	.LVL3
	.uahalf	0x13
	.byte	0x3
	.uaword	index_right
	.byte	0xf6
	.byte	0x4
	.uleb128 0x175
	.byte	0xf4
	.uleb128 0x175
	.byte	0x4
	.uaword	0x427e0000
	.byte	0x1c
	.byte	0x9f
	.uaword	.LVL3
	.uaword	.LVL4
	.uahalf	0x1
	.byte	0x52
	.uaword	.LVL4
	.uaword	.LFE714
	.uahalf	0x13
	.byte	0x3
	.uaword	index_right
	.byte	0xf6
	.byte	0x4
	.uleb128 0x175
	.byte	0xf4
	.uleb128 0x175
	.byte	0x4
	.uaword	0x427e0000
	.byte	0x1c
	.byte	0x9f
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LVL5
	.uaword	.LVL6
	.uahalf	0x6
	.byte	0x9e
	.uleb128 0x4
	.uaword	0
	.uaword	.LVL6
	.uaword	.LVL13
	.uahalf	0x1
	.byte	0x53
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LVL5
	.uaword	.LVL14
	.uahalf	0x6
	.byte	0x9e
	.uleb128 0x4
	.uaword	0
	.uaword	.LVL14
	.uaword	.LFE716
	.uahalf	0x1
	.byte	0x53
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LVL5
	.uaword	.LVL6
	.uahalf	0x2
	.byte	0x30
	.byte	0x9f
	.uaword	.LVL6
	.uaword	.LVL12
	.uahalf	0x1
	.byte	0x5f
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LVL11
	.uaword	.LVL14
	.uahalf	0x3
	.byte	0x8
	.byte	0x40
	.byte	0x9f
	.uaword	.LVL14
	.uaword	.LFE716
	.uahalf	0x1
	.byte	0x5f
	.uaword	0
	.uaword	0
.LLST6:
	.uaword	.LVL5
	.uaword	.LVL6
	.uahalf	0x6
	.byte	0x9e
	.uleb128 0x4
	.uaword	0
	.uaword	.LVL6
	.uaword	.LVL7
	.uahalf	0x1
	.byte	0x52
	.uaword	.LVL8
	.uaword	.LVL10
	.uahalf	0x1
	.byte	0x52
	.uaword	0
	.uaword	0
.LLST7:
	.uaword	.LVL5
	.uaword	.LVL14
	.uahalf	0x6
	.byte	0x9e
	.uleb128 0x4
	.uaword	0
	.uaword	.LVL14
	.uaword	.LVL15
	.uahalf	0x1
	.byte	0x52
	.uaword	.LVL16
	.uaword	.LVL18
	.uahalf	0x1
	.byte	0x52
	.uaword	.LVL19
	.uaword	.LFE716
	.uahalf	0x6
	.byte	0x9e
	.uleb128 0x4
	.uaword	0
	.uaword	0
	.uaword	0
.section .debug_aranges,"",@progbits
	.uaword	0x44
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.LFB713
	.uaword	.LFE713-.LFB713
	.uaword	.LFB714
	.uaword	.LFE714-.LFB714
	.uaword	.LFB715
	.uaword	.LFE715-.LFB715
	.uaword	.LFB716
	.uaword	.LFE716-.LFB716
	.uaword	.LFB717
	.uaword	.LFE717-.LFB717
	.uaword	.LFB718
	.uaword	.LFE718-.LFB718
	.uaword	0
	.uaword	0
.section .debug_ranges,"",@progbits
.Ldebug_ranges0:
	.uaword	.LFB713
	.uaword	.LFE713
	.uaword	.LFB714
	.uaword	.LFE714
	.uaword	.LFB715
	.uaword	.LFE715
	.uaword	.LFB716
	.uaword	.LFE716
	.uaword	.LFB717
	.uaword	.LFE717
	.uaword	.LFB718
	.uaword	.LFE718
	.uaword	0
	.uaword	0
.section .debug_line,"",@progbits
.Ldebug_line0:
.section .debug_str,"",@progbits
	.extern	IR_setBeeperOn,STT_FUNC,0
	.extern	IR_LineScan,STT_OBJECT,1024
	.extern	IR_Srv,STT_OBJECT,4
	.extern	IR_setMotor0En,STT_FUNC,0
	.extern	IR_Motor,STT_OBJECT,8
	.ident	"GCC: (HighTec Release HDP-v4.9.1.0-infineon-1.1-fbb5ca1) 4.9.4 build on 2017-01-30"
