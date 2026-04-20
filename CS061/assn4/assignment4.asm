;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Zachary Brasher
; Email: <omitted>
; 
; Assignment name: Assignment 4
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

; 
BR END_INVALID_CHARACTER_ERR
INVALID_CHARACTER_ERR
    LD R0, ASCII_NEWLINE_CHAR
    OUT

    LD R0, errorMessagePtr
    PUTS
END_INVALID_CHARACTER_ERR

; output intro prompt
LD R0, introPromptPtr
PUTS

; Set up flags, counters, accumulators as needed
AND R2, R2, #0 ; R2 = is_negative flag
LEA R3, ARRAY ; R3 = array ptr
AND R4, R4, #0 ; final result/binary representation of the number
AND R5, R5, #0 ; count of numbers read
LD R6, STACK

; Get first character, test for '\n', '+', '-', digit/non-digit
GETC
OUT

; check if the first character is '\n'. if so, just exit
CHECK_NEWLINE
    ADD R1, R0, #-10
    BRz END

; check if the first char is a minus
CHECK_NEGATIVE
    LD R1, ASCII_MINUS
    ADD R1, R1, R0 ; ascii minus
    BRz IS_NEGATIVE

; check for plus
; ADD R1, R0, #-43 ; ascii plus
CHECK_POSITIVE
    LD R1, ASCII_PLUS
    ADD R1, R1, R0
    BRz IS_POSITIVE
    
BR LOAD_INT

; helper to read then proceed to LOAD_INT
READ_THEN_LOAD
    GETC
    OUT

LOAD_INT
    ; check for a newline (end of the number)
    ADD R1, R0, #-10
    BRz DONE_READING

    ; bounds checking
    LD R1, ASCII_0
    ADD R1, R1, R0 ; R1 = R0 - ascii 0
    
    BRn INVALID_CHARACTER_ERR ; err: R1 < 0
    ADD R1, R1, #-9
    BRp INVALID_CHARACTER_ERR ; err: R1 > 9

    LD R1, ASCII_0 ; ascii -> decimal
    ADD R1, R1, R0
    
    ; R4 = R4 * 10
    ADD R4, R4, R4 ; R4 = R4 * 2
    ADD R0, R4, #0 ; R0 = R4 * 2
    ADD R4, R4, R4 ; R4 = R4 * 4
    ADD R4, R4, R4 ; R4 = R4 * 8
    ADD R4, R4, R0 ; R4 = (R4 * 8) + (R4 * 2)
    
    ; add the value
    ADD R4, R4, R1

    STR R1, R3, #0 ; array[0] = decimal value with n * 10^i
    ADD R3, R3, #1 ; increment the array pointer
    ADD R5, R5, #1 ; increment the counter
    
    BR IS_POSITIVE ; assume positive if only an int is entered

IS_NEGATIVE
    ADD R2, R2, #1 ; is_negative = true

IS_POSITIVE
    ; R2 is already 0

; loop back to LOAD_INT if R4 < 5 and enter wasn't pressed
ADD R1, R5, #-5
BRn READ_THEN_LOAD

DONE_READING

; is it < '0'? if so, it is not a digit	- o/p error message, start over

; is it > '9'? if so, it is not a digit	- o/p error message, start over
				
; if none of the above, first character is first numeric digit - convert it to number & store in target register!
					
; Now get remaining digits from user in a loop (max 5), testing each to see if it is a digit, and build up number in accumulator
MAKE_2COMP
    ADD R2, R2, #0
    BRz END ; if r2 == 0, it's positive. no need for 2c
    
    ; R4 = -R4
    NOT R4, R4
    ADD R4, R4, #1

; remember to end with a newline!

					
END

HALT

;---------------	
; Program Data
;---------------

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200
debugMessagePtr .STRINGZ "got here"
SUB_SHIFT_NUMBER_B400 .FILL xB400

ARRAY .BLKW #5
STACK .FILL xFE00

ASCII_MINUS .FILL #-45
ASCII_PLUS .FILL #-43
ASCII_NEWLINE_CHAR .FILL #10
ASCII_0 .FILL #-48
ASCII_9 .FILL #-57

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

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.



