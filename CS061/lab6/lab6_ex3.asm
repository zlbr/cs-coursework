;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 5, ex 2
; Lab section: 21
; TA: <omitted>
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE
LEA R1, STORAGE_ARR

; call SUB_GET_STRING_3200
LD R4, SUB_GET_STRING_3200
JSRR R4

LEA R1, STORAGE_ARR

; call SUB_IS_PALINDROME_3400
LD R4, SUB_IS_PALINDROME_3400
JSRR R4

LEA R0, STR_THE_STRING ; print "The string"
PUTS


LEA R0, STORAGE_ARR ; print the word
PUTS

; if R4 == 1, its a palindrome. if it's 0, its not
ADD R4, R4, #0
BRp IS_PAL
BRz IS_NOT_PAL

IS_PAL
    LEA R0, STR_IS_PALINDROME
    PUTS

    ; skip IS_NOT_PAL
    BR DONE

IS_NOT_PAL
    LEA R0, STR_IS_NOT_PALINDROME
    PUTS

DONE

; your code goes here
halt

; your local data goes here

top_stack_addr .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
SUB_GET_STRING_3200 .FILL x3200
SUB_IS_PALINDROME_3400 .FILL x3400
STORAGE_ARR .BLKW #100
STR_THE_STRING .STRINGZ "The string \""
STR_IS_PALINDROME .STRINGZ "\" IS a palindrome"
STR_IS_NOT_PALINDROME .STRINGZ "\" IS NOT a palindrome"
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

; zero R5 (number of characters)
AND R5, R5, #0

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

; restore R1 and R7
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1


RET

ADD_TEXT_PROMPT .STRINGZ "Enter text followed by [ENTER]: "

.END


;----------------------------------------------------------------------------
; Subroutine: SUB_IS_PALINDROME
; Parameter (R1): The starting address of a null-terminated string
; Parameter (R5): The number of characters in the array.
; Postcondition: The subroutine has determined whether the string at (R1)
; is a palindrome or not, and returned a flag to that effect.
; Return Value: R4 {1 if the string is a palindrome, 0 otherwise}
;----------------------------------------------------------------------------
.ORIG x3400

; backup R0, R1, R2, R3, R7
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0
ADD R6, R6, #-1
STR R0, R6, #0

; temp variables: R1: min, R2: max

; call SUB_TO_UPPER_3600
LD R4, SUB_TO_UPPER_3600
JSRR R4

; max pointer (R2 = R1 + R5 - 1)
ADD R2, R1, R5
ADD R2, R2, #-1

CHECK_CHARS
    ; end loop lodic
    NOT R0, R2
    ADD R0, R0, #1    ; R0 = 2's comp of R2
    ADD R0, R0, R1    ; R0 = -R2 + R1
    BRzp IS_PALINDROME ; its at the end

    ; compare min/max
    LDR R3, R1, #0    ; R3 = char at R1
    LDR R4, R2, #0    ; R4 = char at R2
    NOT R3, R3 ; make R3 a 2's comp
    ADD R3, R3, #1
    ADD R3, R3, R4 ; R3 = -R3 + R4
    BRnp NOT_PALINDROME

    ; increment counterts
    ADD R1, R1, #1 ; min
    ADD R2, R2, #-1 ; max
    BR CHECK_CHARS


NOT_PALINDROME
    ; r4 = 0
    AND R4, R4, #0
    BR RESTORE_BACKUPS
    
IS_PALINDROME
    ; r4 = 1
    AND R4, R4, #0
    ADD R4, R4, #1


; restore backups
RESTORE_BACKUPS
    LDR R0, R6, #0 ; restore R0
    ADD R6, R6, #1
    LDR R3, R6, #0 ; restore R3
    ADD R6, R6, #1
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1

RET

SUB_TO_UPPER_3600 .FILL x3600

.END

;----------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R1): Starting address of a null-terminated string
; Postcondition: The subroutine has converted the string to upper-case
; In-pace i.e. the upper-case string has replaced the original string
; No return value, no output, but R1 still contains the array address, unchanged
;----------------------------------------------------------------------------
.ORIG x3600

ADD R6, R6, #-1 ; backup R1
STR R1, R6, #0
ADD R6, R6, #-1 ; backup R3
STR R3, R6, #0
ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0

LD R3, BITMASK_UPPER

WHILE_CHECK_CHARS
    LDR R2, R1, #0 ; get element at R1 to R2
    ADD R2, R2, #0
    
    ; null character
    BRz RESTORE_BACKUPS_3600
    
    AND R2, R2, R3 ; apply bitmask
    STR R2, R1, #0 ; store modified value
    ADD R1, R1, #1 ; increment
    
    BR WHILE_CHECK_CHARS

RESTORE_BACKUPS_3600
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1
    LDR R3, R6, #0 ; restore R3
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1


RET

BITMASK_UPPER .FILL xDF ; mask b1101 1111

.END
