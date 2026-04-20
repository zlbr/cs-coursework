.ORIG x3000

; --- 1. Initialization ---
LD R6, STACK_PTR    ; Set stack to xFE00
AND R0, R0, #0      
ADD R0, R0, #2      ; i = 2
AND R1, R1, #0      
ADD R1, R1, #1      ; R1 = 1

; --- 2. Call Subroutine ---
LD R7, ptr_sub
JSRR R7             ; Jump to x4000

HALT                ; R1 should be x0064 (100) here

; --- Data for Main ---
ptr_sub    .FILL x4000
STACK_PTR  .FILL xFE00

.end


;----------------------------------------------------------------------------
; Subroutine: SUB_TIMES_10
; Parameter (R1): The number to convert
; Parameter (R0) i as in 10^i
; in-place conversion: R1 = R1 * 10^R0
;----------------------------------------------------------------------------
.ORIG x4000
SUB_TIMES_10

; save registers
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

WHILE_TIMES_10
    ADD R0, R0, #0
    BRz DONE

    ADD R4, R1, R1
    ADD R1, R4, R4
    ADD R1, R1, R1
    ADD R1, R1, R4

    ADD R0, R0, #-1
    BR WHILE_TIMES_10

DONE
    LDR R7, R6, #0
    ADD R6, R6, #1
    LDR R4, R6, #0
    ADD R6, R6, #1
    LDR R0, R6, #0
    ADD R6, R6, #1

RET
.END