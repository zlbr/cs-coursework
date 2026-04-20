;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Zachary Brasher
; Email: <omitted>
; 
; Assignment name: Lab 8, ex 1
; Lab section: 21
; TA: <omitted>
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================

.ORIG x3000		
;-------------
;Instructions
;-------------

LD R6, STACK

LD R5, LOAD_FILL_VALUE_3200
JSRR R5

ADD R2, R2, #1

LD R5, OUTPUT_AS_DECIMAL_3400
JSRR R5

					
END

HALT

;---------------	
; Program Data
;---------------

LOAD_FILL_VALUE_3200 .FILL x3200
OUTPUT_AS_DECIMAL_3400 .FILL x3400

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200
debugMessagePtr .STRINGZ "got here"
SUB_SHIFT_NUMBER_B400 .FILL xB400

ARRAY .BLKW #5
STACK .FILL xFE00

ASCII_PLUS .FILL #-43
ASCII_NEWLINE_CHAR .FILL #10

.END

;------------
; Remote data
;------------
.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

.END					
					
.ORIG xB200	 ; error message
.STRINGZ	 "ERROR: invalid input\n"


;---------------
; END of PROGRAM
;---------------
.END

; ----------------------------
; LOAD_FILL_VALUE_3200
; Returns (R2): hardcoded decimal value
; Loads the hardcoded value into R2
; ----------------------------

.ORIG x3200

LD R2, FILL_VAL

RET

FILL_VAL .FILL #-20
.END

; ----------------------------
; OUTPUT_AS_DECIMAL_3400
; Parameter (R2) the value to print
; ----------------------------
.ORIG x3400

ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0
ADD R6, R6, #-1 ; backup R3
STR R3, R6, #0
ADD R6, R6, #-1 ; backup R2
STR R2, R6, #0
ADD R6, R6, #-1 ; backup r1
STR R1, R6, #0
ADD R6, R6, #-1 ; backup R0
STR R0, R6, #0

    ; 1. Check if negative
ADD R2, R2, #0
BRzp IS_POSITIVE

IS_NEGATIVE
    ; print minus
    LD R0, ASCII_MINUS
    OUT

    ; 2's comp
    NOT R2, R2
    ADD R2, R2, #1

IS_POSITIVE

    LEA R3, POWERS_10 ; r3 = [10000,1000,100,10,0]

LOOP_PLACES
    LDR R1, R3, #0 ; load increment
    BRz ONES
    
    AND R0, R0, #0 ; r0 = n = counter for this place

SUB_LOOP
    NOT R1, R1 
    ADD R1, R1, #1 ; r1 = -r1
    ADD R2, R2, R1 ; r2 = r2 - r1
    BRn DONE_SUB ; if r2 < 0, too many subtractions
    ADD R0, R0, #1 ; n++
    LDR R1, R3, #0
    BR SUB_LOOP

DONE_SUB
    LDR R1, R3, #0
    ADD R2, R2, R1
    
    LD R1, ASCII_0
    ADD R0, R0, R1
    OUT
    
    ADD R3, R3, #1 ; 10^N, N--
    BR LOOP_PLACES

ONES
    LD R1, ASCII_0 ; 1s place
    ADD R0, R2, R1
    OUT

RESTORE_3400
    LDR R0, R6, #0 ; restore R0
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R3, R6, #0 ; restore R3
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1
RET

ASCII_0 .FILL #48
POWERS_10        .FILL #10000
                 .FILL #1000
                 .FILL #100
                 .FILL #10
                 .FILL #0
                 
ASCII_MINUS .FILL #45

.end