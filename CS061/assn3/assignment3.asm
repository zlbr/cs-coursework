;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Zachary Brasher
; Email: <omitted>
; 
; Assignment name: Assignment 3
; Lab section: 21
; TA: <omitted>
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
LD R3, DEC_4 ; number of bits left until space is printed
LD R4, DEC_4 ; number of spaces printed
LD R5, DEC_16 ; number of bits left to print

DO_WHILE
    ADD R1, R1, #0 ; make r1 the last modified register so the BR will run on it

    BRn PRINT_1
    BRzp PRINT_0
    
    BR END_LOOP ; the number is x0000
    
CHECK_SPACE
    ADD R3, R3, #-1
    BRp NO_SPACE

    LD R3, DEC_4 ; reset R3
    
    ADD R4, R4, #-1; decrement R4
    BRnz END_LOOP
    
    ; print a space
    LD R0, HEX_SPACE
    OUT
    
    NO_SPACE
    ADD R1, R1, R1 ; r1 = r1 * r1 / shift left by 1
    ADD R5, R5, #-1 ; r4 =- 1 decrement counter by -1
    BRzp DO_WHILE

PRINT_1
    ; set r0 to 48 then add 1 (ascii 1)
    LD R0, DEC_48
    ADD R0, R0, #1
    OUT
    
    BR CHECK_SPACE

PRINT_0
    ; set r0 to 48 (ascii 0)
    LD R0, DEC_48
    OUT
    
    BR CHECK_SPACE
    
END_LOOP

LD R0, HEX_NEWLINE
OUT

HALT
;---------------	
;Data
;---------------
Value_ptr	.FILL xCA01	; The address where value to be displayed is stored
DEC_48 .FILL #48
DEC_16 .FILL #16
DEC_4 .FILL #4
HEX_NEWLINE .FILL x0A
HEX_SPACE .FILL x20

.END

.ORIG xCA01					; Remote data
Value .FILL x0100			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------	
;END of PROGRAM
;---------------	
.END
