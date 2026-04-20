;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 3, ex 3
; Lab section: 21
; TA: <omitted>
; 
;=================================================

; R1: number of inputs remaining
; R2: array address
; R3: counter

.orig x3000

; LDR dest ptr offset
LD R6, DEC_10
LEA R2, ARRAY

; loop to input ten characters
INPUT_TEN_CHARS
    ; get the character to R0
    GETC
    OUT
    
    STR R0, R2, #0

    ; counter
    ADD R2, R2, #1 ; increase address by 1
    ADD R6, R6, #-1
    BRp INPUT_TEN_CHARS
END_INPUT_TEN_CHARS

; newline after the input
LD R0, HEX_NEWLINE
OUT

; reset counters
LD R6, DEC_10
AND, R3, R3, #0
LEA R2, ARRAY

PRINT_CHARS
    ; print character
    AND R0, R0, #0
    LDR R0, R2, #0
    OUT
    
    ; newline
    LD R0, HEX_NEWLINE
    OUT
    
    ADD R2, R2, #1
    ADD R6, R6, #-1
    BRp PRINT_CHARS
END_PRINT_CHARS

HALT


ARRAY .BLKW 10
DEC_10 .FILL #10
HEX_NEWLINE .FILL x0A

.end
