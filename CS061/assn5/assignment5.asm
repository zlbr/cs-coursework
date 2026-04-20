; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Zachary Brasher
; Email: <omitted>
;
; Assignment name: Assignment 5
; Lab section:
; TA:
;
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================
;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
LD R6, STACK_ADDR

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------

; variables:
; R0 = temporary storage
; R1 = array address
; R2 = number of characters
; R4 = whether or not it's a palindrome

LEA R1, USER_STRING

; prompt the user
LEA R0, USER_PROMPT
PUTS

; get a string from the user
; * put your code here
LD R5, GET_USER_STRING_3200
JSRR R5

; find size of input string
; * put your code here
LD R5, GET_STR_LEN_3300
JSRR R5

; string length is now in R0. set to R2
ADD R2, R0, #0

; call palindrome method
LD R5, IS_PALINDROME_3400
JSRR R5

; determine of stirng is a palindrome
; * put your code here

; print the result to the screen
; * put your code here
LEA R0, RESULT_STRING
PUTS

; don't print 'not' if the result is 1
ADD R4, R4, #0
BRp SKIP_NOT
PRINT_NOT
    LEA R0, NOT_STRING
    PUTS
SKIP_NOT

LEA R0, FINAL_STRING
PUTS

HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
STACK_ADDR           .FILL    xFE00

; Addresses of subroutines, other than main
GET_USER_STRING_3200 .FILL    x3200
GET_STR_LEN_3300     .FILL    x3300
IS_PALINDROME_3400   .FILL	  x3400


; Reserve memory for strings in the progrtam
USER_PROMPT          .STRINGZ "Enter a string: "
RESULT_STRING        .STRINGZ "The string is "
NOT_STRING           .STRINGZ "not "
FINAL_STRING         .STRINGZ	"a palindrome\n"

; Reserve memory for user input string
USER_STRING          .BLKW	  100

.END

;---------------------------------------------------------------------------------
; Subroutine: GET_USER_STRING
; Parameter: (R1) the array to store the characters to
; Reads a user's text entry from standard input
;---------------------------------------------------------------------------------
.ORIG x3200

ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0
ADD R6, R6, #-1 ; backup R1
STR R1, R6, #0
ADD R6, R6, #-1 ; backup R2
STR R2, R6, #0
ADD R6, R6, #-1 ; backup R3
STR R3, R6, #0

; Backup all used registers, R7 first, using proper stack discipline

AND R2, R2, #0; R2 = temp / number of chars read

; keep reading characters until there's 100 or the user enters \n
WHILE_READ_CHARS
    ; read and show the read character
    GETC
    OUT

    ; test newline
    ADD R0, R0, #-10
    BRz READ_CHARS_RESTORE ; if R0 = 10, finish reading
    ADD R0, R0, #10
    
    ; save the character to the array
    STR R0, R1, #0
    
    ; increment counters
    ADD R1, R1, #1
    ADD R2, R2, #1
    
    ; don't let >100 characters be read
    LD R0, ONE_HUNDRED
    NOT R3, R2
    ADD R3, R3, #1
    ADD R0, R0, R3 ; r0 = 100 - r2
    BRnz END_READING

    BRp WHILE_READ_CHARS
    
END_READING
    LD R0, ASCII_NEWLINE
    OUT

; Resture all used registers, R7 last, using proper stack discipline
READ_CHARS_RESTORE
    LDR R3, R6, #0 ; restore R3
    ADD R6, R6, #1
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1
    
RET

ONE_HUNDRED .FILL #100
ASCII_NEWLINE .FILL x0A

.END

;---------------------------------------------------------------------------------
; Subroutine: STRLEN
; Parameter: (R1) the array address
; Returns: (R0) the length of the string
; Determines and returns the length of a string
;---------------------------------------------------------------------------------
.ORIG x3300

; register backups
ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0
ADD R6, R6, #-1 ; backup R1
STR R1, R6, #0
ADD R6, R6, #-1 ; backup R2
STR R2, R6, #0


AND R2, R2, #0; R2 = number of chars read

WHILE_COUNT_CHARS
    LDR R0, R1, #0 ; R0 = arr[i]
    ADD R1, R1, #1 ; address++
    ADD R2, R2, #1 ; count++


    ADD R0, R0, #0
    BRnp WHILE_COUNT_CHARS ; check if the character is 0. if so, terminate loop and return

; set return value (R0)
ADD R2, R2, #-1
ADD R0, R2, #0

; Resture all used registers
STRLEN_RESTORE
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1
    
RET
.END

;---------------------------------------------------------------------------------
; Subroutine: IS_PALINDROME
; Parameter (R1): the array address
; Parameter (R2): the string's length (last character)

; Recursively checks if a string is a palindrome by checking the first and last characters
;---------------------------------------------------------------------------------
.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive alls

; register backups
ADD R6, R6, #-1 ; backup R7
STR R7, R6, #0
ADD R6, R6, #-1 ; backup R1
STR R1, R6, #0
ADD R6, R6, #-1 ; backup R2
STR R2, R6, #0
ADD R6, R6, #-1 ; backup R5
STR R5, R6, #0

 ; base case: if R2 <= 1, iteration is done
ADD R0, R2, #-1
BRnz IS_PALINDROME

; get first char
LDR R0, R1, #0

; make 2's comp
NOT R0, R0
ADD R0, R0, #1

; add the last char
ADD R5, R2, #-1
ADD R5, R1, R5
LDR R5, R5, #0 ; R5 = arr[R2]

; compare first/last chars
ADD R0, R0, R5
BRnp NOT_PALINDROME ; base case: R0 =/= R5

; recursive case. if R0 = 0, check the next set of char
ADD R1, R1, #1
ADD R2, R2, #-2

LEA R5, palindrome
JSRR R5

BR PALINDROME_RESTORE

; base cases
IS_PALINDROME
    AND R4, R4, #0
    ADD R4, R4, #1 ; return R4 = 1
    BR PALINDROME_RESTORE
 
NOT_PALINDROME
    AND R4, R4, #0 ; return R4 = 0
    BR PALINDROME_RESTORE

; Resture all used registers, R7 last, using proper stack discipline
PALINDROME_RESTORE
    LDR R5, R6, #0 ; restore R5
    ADD R6, R6, #1
    LDR R2, R6, #0 ; restore R2
    ADD R6, R6, #1
    LDR R1, R6, #0 ; restore R1
    ADD R6, R6, #1
    LDR R7, R6, #0 ; restore R7
    ADD R6, R6, #1
    
RET

.END
