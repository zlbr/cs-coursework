;=================================================
; Name: 
; Email: 
; 
; Lab: lab 8, ex 2
; Lab section: 
; TA: 
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

; read a character
GETC
; OUT

; r2 = char
ADD R2, R0, #0

LD R5, PARITY_CHECK_3600
JSRR R5

LEA R0, MSG_NUMBER_OF
PUTS

; print the char
ADD R0, R2, #0
OUT

LEA R0, MSG_IS
PUTS

; print number of occurences
LD R0, ASCII_0 ; R0 = '0'
ADD R0, R0, R3 ; R0 = '0' + n

; print r0
OUT

; Test harness
;-------------------------------------------------

HALT

PARITY_CHECK_3600 .FILL x3600

MSG_NUMBER_OF .STRINGZ "The number of 1's in '"
MSG_IS .STRINGZ "' is: "
ASCII_0 .FILL #48

; Test harness local data
;-------------------------------------------------
top_stack_addr .fill xFE00

.end

;=================================================
; Subroutine: PARITY_CHECK_3600
; Parameter: (R2) the entered character
; Postcondition:
; Return Value (R3): 
;=================================================

.orig x3600

; Backup registers

ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0
ADD R6, R6, #-1 ; backup R4
STR R4, R6, #0
ADD R6, R6, #-1 ; backup R2
STR R2, R6, #0

; R3 = 0
AND R3, R3, #0

; r4 = loop counter
LD R4, DEC_16

; Code
WHILE_DO
    ; shift r2 left: b0001 -> b0010
    ADD R2, R2, R2
    
    ; msb is 1 = negative
    BRzp IS_ZERO
    
    ; if the number is 1, add 1 to the counter
    ADD R3, R3, #1
    
    IS_ZERO

    ADD R4, R4, #-1
    BRp WHILE_DO

; Restore registers
RESTORE_3600
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R4, R6, #0 ; restore R4
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1

RET

BITMASK .FILL x8000 ; b1000 0000 0000 0000
DEC_16 .FILL #16

.end