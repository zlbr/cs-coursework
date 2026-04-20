;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 3, ex 2
; Lab section: 21
; TA: <omitted>
; 
;=================================================


; R1: number of inputs remaining
; R2: array address

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

HALT


ARRAY .BLKW 10
DEC_10 .FILL #10

.end
