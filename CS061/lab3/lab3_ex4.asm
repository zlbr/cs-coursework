;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 3, ex 4
; Lab section: 21
; TA: <omitted>
; 
;=================================================

; R1: number of inputs remaining
; R2: array address
; R3: counter

.orig x3000

LD R2, HEX_ARRAY

; loop to input ten characters
READ_CHARS
    ; get the character to R0
    GETC
    OUT
    
    STR R0, R2, #0

    ; while logic
    ADD R2, R2, #1 ; increase address by 1
    ADD R0, R0, #-10
    BRnp READ_CHARS ; continue if R0 =/= 10 (newline)
END_READ_CHARS



; newline after the input
LD R0, HEX_NEWLINE
OUT

; ; reset counters
AND, R3, R3, #0
LD R2, HEX_ARRAY

PRINT_CHARS
    ; print character
    AND R0, R0, #0
    LDR R0, R2, #0
    OUT
    
    ; newline
    LD R0, HEX_NEWLINE
    OUT
    
    ; get the character back into R0
    LDR R0, R2, #0
    
    ; while logic
    ADD R2, R2, #1
    ADD R0, R0, #0 ; make sure R0 is checked here
    BRnp PRINT_CHARS
END_PRINT_CHARS

HALT

HEX_NULL .FILL x0
HEX_NEWLINE .FILL x0A
HEX_ARRAY .FILL x4000

.end

.orig x4000
; HEX_ARRAY .FILL #0
.end