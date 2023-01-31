;******************************************************************************
;* TI ARM C/C++ Codegen                                        PC v16.9.6.LTS *
;* Date/Time created: Wed Sep 07 13:07:35 2022                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=off --code_state=16 --diag_wrap=off --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=3 --unaligned_access=on 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TI ARM C/C++ Codegen PC v16.9.6.LTS Copyright (c) 1996-2017 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("D:\CE2007\Lab1ref_InputOutput\Debug")

;*****************************************************************************
;* FUNCTION SYNONYMS                                                         *
;*****************************************************************************
	.symalias NMI_Handler, Default_Handler
	.weak	NMI_Handler
	.symalias HardFault_Handler, Default_Handler
	.weak	HardFault_Handler
	.symalias MemManage_Handler, Default_Handler
	.weak	MemManage_Handler
	.symalias BusFault_Handler, Default_Handler
	.weak	BusFault_Handler
	.symalias UsageFault_Handler, Default_Handler
	.weak	UsageFault_Handler
	.symalias SVC_Handler, Default_Handler
	.weak	SVC_Handler
	.symalias DebugMon_Handler, Default_Handler
	.weak	DebugMon_Handler
	.symalias PendSV_Handler, Default_Handler
	.weak	PendSV_Handler
	.symalias SysTick_Handler, Default_Handler
	.weak	SysTick_Handler
	.symalias PSS_IRQHandler, Default_Handler
	.weak	PSS_IRQHandler
	.symalias CS_IRQHandler, Default_Handler
	.weak	CS_IRQHandler
	.symalias PCM_IRQHandler, Default_Handler
	.weak	PCM_IRQHandler
	.symalias WDT_A_IRQHandler, Default_Handler
	.weak	WDT_A_IRQHandler
	.symalias FPU_IRQHandler, Default_Handler
	.weak	FPU_IRQHandler
	.symalias FLCTL_IRQHandler, Default_Handler
	.weak	FLCTL_IRQHandler
	.symalias COMP_E0_IRQHandler, Default_Handler
	.weak	COMP_E0_IRQHandler
	.symalias COMP_E1_IRQHandler, Default_Handler
	.weak	COMP_E1_IRQHandler
	.symalias TA0_0_IRQHandler, Default_Handler
	.weak	TA0_0_IRQHandler
	.symalias TA0_N_IRQHandler, Default_Handler
	.weak	TA0_N_IRQHandler
	.symalias TA1_0_IRQHandler, Default_Handler
	.weak	TA1_0_IRQHandler
	.symalias TA1_N_IRQHandler, Default_Handler
	.weak	TA1_N_IRQHandler
	.symalias TA2_0_IRQHandler, Default_Handler
	.weak	TA2_0_IRQHandler
	.symalias TA2_N_IRQHandler, Default_Handler
	.weak	TA2_N_IRQHandler
	.symalias TA3_0_IRQHandler, Default_Handler
	.weak	TA3_0_IRQHandler
	.symalias TA3_N_IRQHandler, Default_Handler
	.weak	TA3_N_IRQHandler
	.symalias EUSCIA0_IRQHandler, Default_Handler
	.weak	EUSCIA0_IRQHandler
	.symalias EUSCIA1_IRQHandler, Default_Handler
	.weak	EUSCIA1_IRQHandler
	.symalias EUSCIA2_IRQHandler, Default_Handler
	.weak	EUSCIA2_IRQHandler
	.symalias EUSCIA3_IRQHandler, Default_Handler
	.weak	EUSCIA3_IRQHandler
	.symalias EUSCIB0_IRQHandler, Default_Handler
	.weak	EUSCIB0_IRQHandler
	.symalias EUSCIB1_IRQHandler, Default_Handler
	.weak	EUSCIB1_IRQHandler
	.symalias EUSCIB2_IRQHandler, Default_Handler
	.weak	EUSCIB2_IRQHandler
	.symalias EUSCIB3_IRQHandler, Default_Handler
	.weak	EUSCIB3_IRQHandler
	.symalias ADC14_IRQHandler, Default_Handler
	.weak	ADC14_IRQHandler
	.symalias T32_INT1_IRQHandler, Default_Handler
	.weak	T32_INT1_IRQHandler
	.symalias T32_INT2_IRQHandler, Default_Handler
	.weak	T32_INT2_IRQHandler
	.symalias T32_INTC_IRQHandler, Default_Handler
	.weak	T32_INTC_IRQHandler
	.symalias AES256_IRQHandler, Default_Handler
	.weak	AES256_IRQHandler
	.symalias RTC_C_IRQHandler, Default_Handler
	.weak	RTC_C_IRQHandler
	.symalias DMA_ERR_IRQHandler, Default_Handler
	.weak	DMA_ERR_IRQHandler
	.symalias DMA_INT3_IRQHandler, Default_Handler
	.weak	DMA_INT3_IRQHandler
	.symalias DMA_INT2_IRQHandler, Default_Handler
	.weak	DMA_INT2_IRQHandler
	.symalias DMA_INT1_IRQHandler, Default_Handler
	.weak	DMA_INT1_IRQHandler
	.symalias DMA_INT0_IRQHandler, Default_Handler
	.weak	DMA_INT0_IRQHandler
	.symalias PORT1_IRQHandler, Default_Handler
	.weak	PORT1_IRQHandler
	.symalias PORT2_IRQHandler, Default_Handler
	.weak	PORT2_IRQHandler
	.symalias PORT3_IRQHandler, Default_Handler
	.weak	PORT3_IRQHandler
	.symalias PORT4_IRQHandler, Default_Handler
	.weak	PORT4_IRQHandler
	.symalias PORT5_IRQHandler, Default_Handler
	.weak	PORT5_IRQHandler
	.symalias PORT6_IRQHandler, Default_Handler
	.weak	PORT6_IRQHandler

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("SystemInit")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("SystemInit")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$1, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$1, DW_AT_decl_column(0x0d)
	.dwendtag $C$DW$1

$C$DW$2	.dwtag  DW_TAG_variable
	.dwattr $C$DW$2, DW_AT_name("__STACK_END")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("__STACK_END")
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$13)
	.dwattr $C$DW$2, DW_AT_declaration
	.dwattr $C$DW$2, DW_AT_external
	.dwattr $C$DW$2, DW_AT_decl_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$2, DW_AT_decl_line(0x28)
	.dwattr $C$DW$2, DW_AT_decl_column(0x16)

	.global	interruptVectors
	.sect	".intvecs:retain"
	.retain
	.align	4
	.elfsym	interruptVectors,SYM_SIZE(228)
interruptVectors:
	.bits	__STACK_END,32		; interruptVectors[0] @ 0
	.bits	Reset_Handler,32		; interruptVectors[1] @ 32
	.bits	NMI_Handler,32		; interruptVectors[2] @ 64
	.bits	HardFault_Handler,32		; interruptVectors[3] @ 96
	.bits	MemManage_Handler,32		; interruptVectors[4] @ 128
	.bits	BusFault_Handler,32		; interruptVectors[5] @ 160
	.bits	UsageFault_Handler,32		; interruptVectors[6] @ 192
	.bits	0,32			; interruptVectors[7] @ 224
	.bits	0,32			; interruptVectors[8] @ 256
	.bits	0,32			; interruptVectors[9] @ 288
	.bits	0,32			; interruptVectors[10] @ 320
	.bits	SVC_Handler,32		; interruptVectors[11] @ 352
	.bits	DebugMon_Handler,32		; interruptVectors[12] @ 384
	.bits	0,32			; interruptVectors[13] @ 416
	.bits	PendSV_Handler,32		; interruptVectors[14] @ 448
	.bits	SysTick_Handler,32		; interruptVectors[15] @ 480
	.bits	PSS_IRQHandler,32		; interruptVectors[16] @ 512
	.bits	CS_IRQHandler,32		; interruptVectors[17] @ 544
	.bits	PCM_IRQHandler,32		; interruptVectors[18] @ 576
	.bits	WDT_A_IRQHandler,32		; interruptVectors[19] @ 608
	.bits	FPU_IRQHandler,32		; interruptVectors[20] @ 640
	.bits	FLCTL_IRQHandler,32		; interruptVectors[21] @ 672
	.bits	COMP_E0_IRQHandler,32		; interruptVectors[22] @ 704
	.bits	COMP_E1_IRQHandler,32		; interruptVectors[23] @ 736
	.bits	TA0_0_IRQHandler,32		; interruptVectors[24] @ 768
	.bits	TA0_N_IRQHandler,32		; interruptVectors[25] @ 800
	.bits	TA1_0_IRQHandler,32		; interruptVectors[26] @ 832
	.bits	TA1_N_IRQHandler,32		; interruptVectors[27] @ 864
	.bits	TA2_0_IRQHandler,32		; interruptVectors[28] @ 896
	.bits	TA2_N_IRQHandler,32		; interruptVectors[29] @ 928
	.bits	TA3_0_IRQHandler,32		; interruptVectors[30] @ 960
	.bits	TA3_N_IRQHandler,32		; interruptVectors[31] @ 992
	.bits	EUSCIA0_IRQHandler,32		; interruptVectors[32] @ 1024
	.bits	EUSCIA1_IRQHandler,32		; interruptVectors[33] @ 1056
	.bits	EUSCIA2_IRQHandler,32		; interruptVectors[34] @ 1088
	.bits	EUSCIA3_IRQHandler,32		; interruptVectors[35] @ 1120
	.bits	EUSCIB0_IRQHandler,32		; interruptVectors[36] @ 1152
	.bits	EUSCIB1_IRQHandler,32		; interruptVectors[37] @ 1184
	.bits	EUSCIB2_IRQHandler,32		; interruptVectors[38] @ 1216
	.bits	EUSCIB3_IRQHandler,32		; interruptVectors[39] @ 1248
	.bits	ADC14_IRQHandler,32		; interruptVectors[40] @ 1280
	.bits	T32_INT1_IRQHandler,32		; interruptVectors[41] @ 1312
	.bits	T32_INT2_IRQHandler,32		; interruptVectors[42] @ 1344
	.bits	T32_INTC_IRQHandler,32		; interruptVectors[43] @ 1376
	.bits	AES256_IRQHandler,32		; interruptVectors[44] @ 1408
	.bits	RTC_C_IRQHandler,32		; interruptVectors[45] @ 1440
	.bits	DMA_ERR_IRQHandler,32		; interruptVectors[46] @ 1472
	.bits	DMA_INT3_IRQHandler,32		; interruptVectors[47] @ 1504
	.bits	DMA_INT2_IRQHandler,32		; interruptVectors[48] @ 1536
	.bits	DMA_INT1_IRQHandler,32		; interruptVectors[49] @ 1568
	.bits	DMA_INT0_IRQHandler,32		; interruptVectors[50] @ 1600
	.bits	PORT1_IRQHandler,32		; interruptVectors[51] @ 1632
	.bits	PORT2_IRQHandler,32		; interruptVectors[52] @ 1664
	.bits	PORT3_IRQHandler,32		; interruptVectors[53] @ 1696
	.bits	PORT4_IRQHandler,32		; interruptVectors[54] @ 1728
	.bits	PORT5_IRQHandler,32		; interruptVectors[55] @ 1760
	.bits	PORT6_IRQHandler,32		; interruptVectors[56] @ 1792

$C$DW$3	.dwtag  DW_TAG_variable
	.dwattr $C$DW$3, DW_AT_name("interruptVectors")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("interruptVectors")
	.dwattr $C$DW$3, DW_AT_location[DW_OP_addr interruptVectors]
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_decl_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$3, DW_AT_decl_line(0x70)
	.dwattr $C$DW$3, DW_AT_decl_column(0x0f)

;	C:\ti\ccsv7\tools\compiler\ti-cgt-arm_16.9.6.LTS\bin\armacpia.exe -@C:\\Users\\gong0060\\AppData\\Local\\Temp\\{4E16DEF9-1273-4C10-9671-408F5D1097AC} 
	.sect	".text"
	.clink
	.thumbfunc Reset_Handler
	.thumb
	.weak	Reset_Handler

$C$DW$4	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$4, DW_AT_name("Reset_Handler")
	.dwattr $C$DW$4, DW_AT_low_pc(Reset_Handler)
	.dwattr $C$DW$4, DW_AT_high_pc(0x00)
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("Reset_Handler")
	.dwattr $C$DW$4, DW_AT_external
	.dwattr $C$DW$4, DW_AT_TI_begin_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$4, DW_AT_TI_begin_line(0xb5)
	.dwattr $C$DW$4, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$4, DW_AT_decl_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$4, DW_AT_decl_line(0xb5)
	.dwattr $C$DW$4, DW_AT_decl_column(0x06)
	.dwattr $C$DW$4, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 182,column 1,is_stmt,address Reset_Handler,isa 1

	.dwfde $C$DW$CIE, Reset_Handler

;*****************************************************************************
;* FUNCTION NAME: Reset_Handler                                              *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Regs Used         : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
Reset_Handler:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	save_reg_to_mem, 3, -8
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 183,column 5,is_stmt,isa 1
$C$DW$5	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$5, DW_AT_low_pc(0x00)
	.dwattr $C$DW$5, DW_AT_name("SystemInit")
	.dwattr $C$DW$5, DW_AT_TI_call

        BL        SystemInit            ; [DPU_3_PIPE] |183| 
        ; CALL OCCURS {SystemInit }      ; [] |183| 
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 186,column 5,is_stmt,isa 1
    .global _c_int00
    b.w     _c_int00
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 188,column 1,is_stmt,isa 1
$C$DW$6	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$6, DW_AT_low_pc(0x00)
	.dwattr $C$DW$6, DW_AT_TI_return

        POP       {A4, PC}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
	.dwcfi	restore_reg, 3
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$4, DW_AT_TI_end_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$4, DW_AT_TI_end_line(0xbc)
	.dwattr $C$DW$4, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$4

	.sect	".text"
	.clink
	.thumbfunc Default_Handler
	.thumb
	.weak	Default_Handler

$C$DW$7	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$7, DW_AT_name("Default_Handler")
	.dwattr $C$DW$7, DW_AT_low_pc(Default_Handler)
	.dwattr $C$DW$7, DW_AT_high_pc(0x00)
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("Default_Handler")
	.dwattr $C$DW$7, DW_AT_external
	.dwattr $C$DW$7, DW_AT_TI_begin_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$7, DW_AT_TI_begin_line(0xc2)
	.dwattr $C$DW$7, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$7, DW_AT_decl_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$7, DW_AT_decl_line(0xc2)
	.dwattr $C$DW$7, DW_AT_decl_column(0x06)
	.dwattr $C$DW$7, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 195,column 1,is_stmt,address Default_Handler,isa 1

	.dwfde $C$DW$CIE, Default_Handler

;*****************************************************************************
;* FUNCTION NAME: Default_Handler                                            *
;*                                                                           *
;*   Regs Modified     :                                                     *
;*   Regs Used         : LR                                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
Default_Handler:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwpsn	file "../startup_msp432p401r_ccs.c",line 201,column 8,is_stmt,isa 1
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L1||
;*
;*   Loop source line                : 201
;*   Loop closing brace source line  : 203
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L1||:    
        B         ||$C$L1||             ; [DPU_3_PIPE] |201| 
        ; BRANCH OCCURS {||$C$L1||}      ; [] |201| 
;* --------------------------------------------------------------------------*
	.dwattr $C$DW$7, DW_AT_TI_end_file("../startup_msp432p401r_ccs.c")
	.dwattr $C$DW$7, DW_AT_TI_end_line(0xce)
	.dwattr $C$DW$7, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$7

;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	SystemInit
	.global	__STACK_END

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_LPM_INFO(1)
	.battr "TI", Tag_File, 1, Tag_PORTS_INIT_INFO("012345678901ABCDEFGHIJ00000000000000000000000000000000000000000000")
	.battr "aeabi", Tag_File, 1, Tag_ABI_PCS_wchar_t(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_rounding(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_denormal(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_exceptions(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_number_model(1)
	.battr "aeabi", Tag_File, 1, Tag_ABI_enum_size(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_optimization_goals(5)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_optimization_goals(0)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_VFP_args(3)
	.battr "TI", Tag_File, 1, Tag_FP_interface(1)

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************
$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")


$C$DW$T$19	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$19, DW_AT_language(DW_LANG_C)
	.dwendtag $C$DW$T$19

$C$DW$T$20	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$20, DW_AT_address_class(0x20)

$C$DW$T$21	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)


$C$DW$T$22	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$T$22, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$22, DW_AT_byte_size(0xe4)
$C$DW$8	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$8, DW_AT_upper_bound(0x38)

	.dwendtag $C$DW$T$22

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)

$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)

$C$DW$T$23	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$23, DW_AT_name("int8_t")
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$23, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$23, DW_AT_decl_line(0x2a)
	.dwattr $C$DW$T$23, DW_AT_decl_column(0x1d)

$C$DW$T$24	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$24, DW_AT_name("int_least8_t")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$24, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$24, DW_AT_decl_line(0x37)
	.dwattr $C$DW$T$24, DW_AT_decl_column(0x17)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$25	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$25, DW_AT_name("uint8_t")
	.dwattr $C$DW$T$25, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$25, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$25, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$25, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$T$25, DW_AT_decl_column(0x1c)

$C$DW$T$26	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$26, DW_AT_name("uint_least8_t")
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$26, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$26, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$26, DW_AT_decl_line(0x38)
	.dwattr $C$DW$T$26, DW_AT_decl_column(0x16)

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)

$C$DW$T$27	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$27, DW_AT_name("int16_t")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$8)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$27, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$27, DW_AT_decl_line(0x2c)
	.dwattr $C$DW$T$27, DW_AT_decl_column(0x1d)

$C$DW$T$28	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$28, DW_AT_name("int_least16_t")
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$28, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$28, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$28, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$T$28, DW_AT_decl_column(0x17)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)

$C$DW$T$29	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$29, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$29, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$29, DW_AT_decl_line(0x2d)
	.dwattr $C$DW$T$29, DW_AT_decl_column(0x1c)

$C$DW$T$30	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$30, DW_AT_name("uint_least16_t")
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$30, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$30, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$30, DW_AT_decl_line(0x3b)
	.dwattr $C$DW$T$30, DW_AT_decl_column(0x16)

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)

$C$DW$T$31	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$31, DW_AT_name("int32_t")
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$31, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$31, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$31, DW_AT_decl_line(0x2e)
	.dwattr $C$DW$T$31, DW_AT_decl_column(0x1d)

$C$DW$T$32	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$32, DW_AT_name("int_fast16_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x47)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x17)

$C$DW$T$33	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$33, DW_AT_name("int_fast32_t")
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$33, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$33, DW_AT_decl_line(0x4a)
	.dwattr $C$DW$T$33, DW_AT_decl_column(0x17)

$C$DW$T$34	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$34, DW_AT_name("int_fast8_t")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$34, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$34, DW_AT_decl_line(0x45)
	.dwattr $C$DW$T$34, DW_AT_decl_column(0x17)

$C$DW$T$35	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$35, DW_AT_name("int_least32_t")
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$35, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$35, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$35, DW_AT_decl_line(0x3c)
	.dwattr $C$DW$T$35, DW_AT_decl_column(0x17)

$C$DW$T$36	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$36, DW_AT_name("intptr_t")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$36, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$36, DW_AT_decl_line(0x52)
	.dwattr $C$DW$T$36, DW_AT_decl_column(0x1a)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)

$C$DW$T$37	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$37, DW_AT_name("uint32_t")
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$37, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$37, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$T$37, DW_AT_decl_column(0x1c)

$C$DW$T$38	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$38, DW_AT_name("uint_fast16_t")
	.dwattr $C$DW$T$38, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$38, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$38, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$38, DW_AT_decl_line(0x48)
	.dwattr $C$DW$T$38, DW_AT_decl_column(0x16)

$C$DW$T$39	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$39, DW_AT_name("uint_fast32_t")
	.dwattr $C$DW$T$39, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$39, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$39, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$39, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$T$39, DW_AT_decl_column(0x16)

$C$DW$T$40	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$40, DW_AT_name("uint_fast8_t")
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$40, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$40, DW_AT_decl_line(0x46)
	.dwattr $C$DW$T$40, DW_AT_decl_column(0x16)

$C$DW$T$41	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$41, DW_AT_name("uint_least32_t")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$41, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$41, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$T$41, DW_AT_decl_column(0x16)

$C$DW$T$42	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$42, DW_AT_name("uintptr_t")
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$42, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$42, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$42, DW_AT_decl_line(0x53)
	.dwattr $C$DW$T$42, DW_AT_decl_column(0x1a)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x04)

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x04)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)

$C$DW$T$44	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$44, DW_AT_name("int64_t")
	.dwattr $C$DW$T$44, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$44, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$44, DW_AT_decl_line(0x32)
	.dwattr $C$DW$T$44, DW_AT_decl_column(0x21)

$C$DW$T$45	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$45, DW_AT_name("int_fast64_t")
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$T$45, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$45, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$45, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$45, DW_AT_decl_column(0x17)

$C$DW$T$46	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$46, DW_AT_name("int_least64_t")
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$46, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$46, DW_AT_decl_line(0x40)
	.dwattr $C$DW$T$46, DW_AT_decl_column(0x17)

$C$DW$T$47	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$47, DW_AT_name("intmax_t")
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$47, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$47, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$47, DW_AT_decl_line(0x56)
	.dwattr $C$DW$T$47, DW_AT_decl_column(0x20)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)

$C$DW$T$48	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$48, DW_AT_name("uint64_t")
	.dwattr $C$DW$T$48, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$48, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$48, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$48, DW_AT_decl_line(0x33)
	.dwattr $C$DW$T$48, DW_AT_decl_column(0x20)

$C$DW$T$49	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$49, DW_AT_name("uint_fast64_t")
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$48)
	.dwattr $C$DW$T$49, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$49, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$49, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$49, DW_AT_decl_column(0x16)

$C$DW$T$50	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$50, DW_AT_name("uint_least64_t")
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$48)
	.dwattr $C$DW$T$50, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$50, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$50, DW_AT_decl_line(0x41)
	.dwattr $C$DW$T$50, DW_AT_decl_column(0x16)

$C$DW$T$51	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$51, DW_AT_name("uintmax_t")
	.dwattr $C$DW$T$51, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$51, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$51, DW_AT_decl_file("C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include/stdint.h")
	.dwattr $C$DW$T$51, DW_AT_decl_line(0x57)
	.dwattr $C$DW$T$51, DW_AT_decl_column(0x20)

$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x04)

$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x08)

$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x08)

	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 14
	.dwcfi	cfa_register, 13
	.dwcfi	cfa_offset, 0
	.dwcfi	same_value, 4
	.dwcfi	same_value, 5
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	same_value, 80
	.dwcfi	same_value, 81
	.dwcfi	same_value, 82
	.dwcfi	same_value, 83
	.dwcfi	same_value, 84
	.dwcfi	same_value, 85
	.dwcfi	same_value, 86
	.dwcfi	same_value, 87
	.dwcfi	same_value, 88
	.dwcfi	same_value, 89
	.dwcfi	same_value, 90
	.dwcfi	same_value, 91
	.dwcfi	same_value, 92
	.dwcfi	same_value, 93
	.dwcfi	same_value, 94
	.dwcfi	same_value, 95
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$9	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$9, DW_AT_name("A1")
	.dwattr $C$DW$9, DW_AT_location[DW_OP_reg0]

$C$DW$10	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$10, DW_AT_name("A2")
	.dwattr $C$DW$10, DW_AT_location[DW_OP_reg1]

$C$DW$11	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$11, DW_AT_name("A3")
	.dwattr $C$DW$11, DW_AT_location[DW_OP_reg2]

$C$DW$12	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$12, DW_AT_name("A4")
	.dwattr $C$DW$12, DW_AT_location[DW_OP_reg3]

$C$DW$13	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$13, DW_AT_name("V1")
	.dwattr $C$DW$13, DW_AT_location[DW_OP_reg4]

$C$DW$14	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$14, DW_AT_name("V2")
	.dwattr $C$DW$14, DW_AT_location[DW_OP_reg5]

$C$DW$15	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$15, DW_AT_name("V3")
	.dwattr $C$DW$15, DW_AT_location[DW_OP_reg6]

$C$DW$16	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$16, DW_AT_name("V4")
	.dwattr $C$DW$16, DW_AT_location[DW_OP_reg7]

$C$DW$17	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$17, DW_AT_name("V5")
	.dwattr $C$DW$17, DW_AT_location[DW_OP_reg8]

$C$DW$18	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$18, DW_AT_name("V6")
	.dwattr $C$DW$18, DW_AT_location[DW_OP_reg9]

$C$DW$19	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$19, DW_AT_name("V7")
	.dwattr $C$DW$19, DW_AT_location[DW_OP_reg10]

$C$DW$20	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$20, DW_AT_name("V8")
	.dwattr $C$DW$20, DW_AT_location[DW_OP_reg11]

$C$DW$21	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$21, DW_AT_name("V9")
	.dwattr $C$DW$21, DW_AT_location[DW_OP_reg12]

$C$DW$22	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$22, DW_AT_name("SP")
	.dwattr $C$DW$22, DW_AT_location[DW_OP_reg13]

$C$DW$23	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$23, DW_AT_name("LR")
	.dwattr $C$DW$23, DW_AT_location[DW_OP_reg14]

$C$DW$24	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$24, DW_AT_name("PC")
	.dwattr $C$DW$24, DW_AT_location[DW_OP_reg15]

$C$DW$25	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$25, DW_AT_name("SR")
	.dwattr $C$DW$25, DW_AT_location[DW_OP_reg17]

$C$DW$26	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$26, DW_AT_name("AP")
	.dwattr $C$DW$26, DW_AT_location[DW_OP_reg7]

$C$DW$27	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$27, DW_AT_name("D0")
	.dwattr $C$DW$27, DW_AT_location[DW_OP_regx 0x40]

$C$DW$28	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$28, DW_AT_name("D0_hi")
	.dwattr $C$DW$28, DW_AT_location[DW_OP_regx 0x41]

$C$DW$29	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$29, DW_AT_name("D1")
	.dwattr $C$DW$29, DW_AT_location[DW_OP_regx 0x42]

$C$DW$30	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$30, DW_AT_name("D1_hi")
	.dwattr $C$DW$30, DW_AT_location[DW_OP_regx 0x43]

$C$DW$31	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$31, DW_AT_name("D2")
	.dwattr $C$DW$31, DW_AT_location[DW_OP_regx 0x44]

$C$DW$32	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$32, DW_AT_name("D2_hi")
	.dwattr $C$DW$32, DW_AT_location[DW_OP_regx 0x45]

$C$DW$33	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$33, DW_AT_name("D3")
	.dwattr $C$DW$33, DW_AT_location[DW_OP_regx 0x46]

$C$DW$34	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$34, DW_AT_name("D3_hi")
	.dwattr $C$DW$34, DW_AT_location[DW_OP_regx 0x47]

$C$DW$35	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$35, DW_AT_name("D4")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_regx 0x48]

$C$DW$36	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$36, DW_AT_name("D4_hi")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_regx 0x49]

$C$DW$37	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$37, DW_AT_name("D5")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$38	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$38, DW_AT_name("D5_hi")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_regx 0x4b]

$C$DW$39	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$39, DW_AT_name("D6")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$40	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$40, DW_AT_name("D6_hi")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$41	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$41, DW_AT_name("D7")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_regx 0x4e]

$C$DW$42	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$42, DW_AT_name("D7_hi")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_regx 0x4f]

$C$DW$43	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$43, DW_AT_name("D8")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_regx 0x50]

$C$DW$44	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$44, DW_AT_name("D8_hi")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_regx 0x51]

$C$DW$45	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$45, DW_AT_name("D9")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_regx 0x52]

$C$DW$46	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$46, DW_AT_name("D9_hi")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_regx 0x53]

$C$DW$47	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$47, DW_AT_name("D10")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_regx 0x54]

$C$DW$48	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$48, DW_AT_name("D10_hi")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_regx 0x55]

$C$DW$49	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$49, DW_AT_name("D11")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_regx 0x56]

$C$DW$50	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$50, DW_AT_name("D11_hi")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_regx 0x57]

$C$DW$51	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$51, DW_AT_name("D12")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_regx 0x58]

$C$DW$52	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$52, DW_AT_name("D12_hi")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_regx 0x59]

$C$DW$53	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$53, DW_AT_name("D13")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_regx 0x5a]

$C$DW$54	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$54, DW_AT_name("D13_hi")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_regx 0x5b]

$C$DW$55	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$55, DW_AT_name("D14")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_regx 0x5c]

$C$DW$56	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$56, DW_AT_name("D14_hi")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_regx 0x5d]

$C$DW$57	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$57, DW_AT_name("D15")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_regx 0x5e]

$C$DW$58	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$58, DW_AT_name("D15_hi")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_regx 0x5f]

$C$DW$59	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$59, DW_AT_name("FPEXC")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg18]

$C$DW$60	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$60, DW_AT_name("FPSCR")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_reg19]

	.dwendtag $C$DW$CU

