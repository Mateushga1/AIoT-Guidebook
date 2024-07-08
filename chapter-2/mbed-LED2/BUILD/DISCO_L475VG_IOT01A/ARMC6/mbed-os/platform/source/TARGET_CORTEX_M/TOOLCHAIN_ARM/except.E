# 1 ".\\mbed-os\\platform\\source\\TARGET_CORTEX_M\\TOOLCHAIN_ARM\\except.S"
# 1 "<built-in>" 1
# 395 "<built-in>"
# 1 "./BUILD/DISCO_L475VG_IOT01A/ARMC6\\mbed_config.h" 1
# 396 "<built-in>" 2
# 1 ".\\mbed-os\\platform\\source\\TARGET_CORTEX_M\\TOOLCHAIN_ARM\\except.S" 2
;
# 30 ".\\mbed-os\\platform\\source\\TARGET_CORTEX_M\\TOOLCHAIN_ARM\\except.S"
FAULT_TYPE_HARD_FAULT EQU 0x10
FAULT_TYPE_MEMMANAGE_FAULT EQU 0x20
FAULT_TYPE_BUS_FAULT EQU 0x30
FAULT_TYPE_USAGE_FAULT EQU 0x40

        PRESERVE8
        THUMB

        AREA |.text|, CODE, READONLY

HardFault_Handler PROC

        EXPORT HardFault_Handler
        MOVS R3,#FAULT_TYPE_HARD_FAULT
        B Fault_Handler
        ENDP

MemManage_Handler PROC

        EXPORT MemManage_Handler
        MOVS R3,#FAULT_TYPE_MEMMANAGE_FAULT
        B Fault_Handler
        ENDP

BusFault_Handler PROC

        EXPORT BusFault_Handler
        MOVS R3,#FAULT_TYPE_BUS_FAULT
        B Fault_Handler
        ENDP

UsageFault_Handler PROC

        EXPORT UsageFault_Handler
        MOVS R3,#FAULT_TYPE_USAGE_FAULT
        ; Fall into Fault_Handler
        ENDP

Fault_Handler PROC

        EXPORT Fault_Handler




        IMPORT |Image$$RW_m_crash_data$$ZI$$Base|
        IMPORT mbed_fault_handler

        MOV R12,R3
        PUSH {R4-R7}
        ADD R6,SP,#16
        MOV R5,LR
        LSRS R0,R5,#3 ; Check EXC_RETURN for bit 2
        BCC Fault_Handler_Continue
        MRS R6,PSP

Fault_Handler_Continue
        LDR R7,=|Image$$RW_m_crash_data$$ZI$$Base|
        LDMIA R6!,{R0-R3}
        STMIA R7!,{R0-R3} ; Capture R0..R3
        POP {R0-R3}
        STMIA R7!,{R0-R3} ; Capture R4..R7
        MOV R0,R8
        MOV R1,R9
        MOV R2,R10
        MOV R3,R11
        STMIA R7!,{R0-R3} ; Capture R8..R11
        LDMIA R6!,{R0,R2-R4} ; Load R12,LR,PC,xPSR
        ; Adjust stack pointer to its original value
        MOVS R1,R6
        LSRS R6,R4,#10 ; Check for if STK was aligned by checking bit-9 in xPSR value
        BCC Fault_Handler_Continue1
        ADDS R1,#0x4

Fault_Handler_Continue1
        LSRS R6,R5,#5 ; Check EXC_RETURN bit-4 to see if FP context was saved
        BCS Fault_Handler_Continue2
        ADDS R1,#0x48 ; 16 FP regs + FPCSR + 1 Reserved
Fault_Handler_Continue2
        STMIA R7!,{R0-R4} ; Capture R12,SP,LR,PC,xPSR
        MRS R0,PSP
        MOV R1,SP
        MRS R6,CONTROL
        STMIA R7!,{R0,R1,R5,R6} ; Capture PSP,MSP,EXC_RETURN,CONTROL
        MOV R0,R12
        LDR R1,=|Image$$RW_m_crash_data$$ZI$$Base|
        BL mbed_fault_handler ; mbed_fault_handler does not return



        ENDP
        ALIGN


        END
