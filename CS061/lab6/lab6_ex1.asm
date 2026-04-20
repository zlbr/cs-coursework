;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 5, ex 1
; Lab section: 21
; TA: <omitted>
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
LEA R1, STORAGE_ARR

; call SUB_GET_STRING_3200
LD R5, SUB_GET_STRING_3200
JSRR R5

LEA R0, STORAGE_ARR
PUTS

; your code goes here
halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
SUB_GET_STRING_3200 .FILL x3200
STORAGE_ARR .BLKW #100
.end

;----------------------------------------------------------------------------
; Subroutine: SUB_GET_STRING
; Parameter (R1): The starting address of the character array
; Postcondition: The subroutine has prompted the user to input a string,
    ; terminated by the [ENTER] key (the 'sentinel"), and has stored
    ; the received characters in an array of characters starting at (R1).
    ; the array is NULL-terminated' the sentinel character is NOT stored.
; Return Value (R5): The number of non-sentinel chars read from the user.
    ; R1 contains the starting address of the array unchanged
;----------------------------------------------------------------------------

.ORIG x3200

; backup R1 and R7
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0

; prompt the user
LEA R0, ADD_TEXT_PROMPT
PUTS

; zero R5 (number of entered characyers)

READ_WHILE
    ; get input and show it to the user
    GETC
    OUT
    
    ; sentinel character handling
    ADD R0, R0, #-10 ; #10 = newline
    BRz END_READ_WHILE
    ADD R0, R0, #10
        
    ; store the value & increment counters
    STR R0, R1, #0
    ADD R1, R1, #1
    ADD R5, R5, #1
    BR READ_WHILE
END_READ_WHILE

; store null character at the end of the array
AND R0, R0, #0
STR R0, R1, #0

; restore R1 to original state
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1


RET

ADD_TEXT_PROMPT .STRINGZ "Enter text followed by [ENTER]: "

.END