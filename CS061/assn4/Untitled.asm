.ORIG x3000

START_PROG
    ; 1. Display the prompt [cite: 5, 39]
    LEA R0, PROMPT
    PUTS

    ; 2. Initialize registers 
    AND R5, R5, #0      ; Rx (The result register) [cite: 6]
    AND R4, R4, #0      ; Sign flag (0 for +, 1 for -) 
    AND R3, R3, #0      ; Digit counter [cite: 34]
    AND R2, R2, #0      ; Valid digit flag (ensures at least one digit is entered)

    ; 3. Read the initial character [cite: 10]
    GETC
    OUT

    ; Check if initial character is a newline (x0A) [cite: 16]
    ADD R1, R0, #-10
    BRz EXIT_PROG

    ; Check if initial character is '+' (x2B) [cite: 13]
    LD R1, PLUS_ASCII
    ADD R1, R0, R1
    BRz IS_PLUS

    ; Check if initial character is '-' (x2D) [cite: 11]
    LD R1, MINUS_ASCII
    ADD R1, R0, R1
    BRz IS_MINUS

    ; Check if initial character is a numeric digit [cite: 14]
    BRnzp VALIDATE_DIGIT

IS_MINUS
    ADD R4, R4, #1      ; Set negative flag 
    BRnzp NEXT_CHAR

IS_PLUS
    BRnzp NEXT_CHAR

    ; 4. Main Input Loop [cite: 18, 19]
GET_INPUT
    GETC
    OUT

    ; Check for newline to terminate [cite: 26]
    ADD R1, R0, #-10
    BRz CHECK_VALID_ENTRY

VALIDATE_DIGIT
    ; Check if < '0' (x30) [cite: 32, 118]
    LD R1, ZERO_ASCII
    ADD R1, R0, R1
    BRn ERROR_BLOCK

    ; Check if > '9' (x39) [cite: 32, 118]
    LD R1, NINE_ASCII
    ADD R1, R0, R1
    BRp ERROR_BLOCK

    ; Digit is valid: Convert ASCII to binary [cite: 23]
    LD R1, ZERO_ASCII
    ADD R0, R0, R1      ; R0 now holds numeric value 0-9
    ADD R2, R2, #1      ; Mark that we have at least one digit [cite: 116]

    ; Multiply Rx by 10 (Rx = Rx * 10) 
    ; Use addition: Rx*10 = (Rx*8) + (Rx*2)
    ADD R1, R5, #0      ; R1 = Rx
    ADD R5, R5, R5      ; Rx = 2x
    ADD R6, R5, #0      ; R6 = 2x
    ADD R5, R5, R5      ; Rx = 4x
    ADD R5, R5, R5      ; Rx = 8x
    ADD R5, R5, R6      ; Rx = 8x + 2x = 10x

    ; Add current digit to Rx
    ADD R5, R5, R0
    
    ; Increment counter and check if 5 digits reached [cite: 34]
    ADD R3, R3, #1
    ADD R1, R3, #-5
    BRz AUTO_NEWLINE    ; If 5 digits, stop and issue newline [cite: 121]

NEXT_CHAR
    BRnzp GET_INPUT

CHECK_VALID_ENTRY
    ; Error if ENTER was pressed but no digits were entered (only a sign) [cite: 116]
    ADD R2, R2, #0
    BRz ERROR_BLOCK
    BRnzp APPLY_SIGN

AUTO_NEWLINE
    LD R0, NEWLINE_CHAR
    OUT
    BRnzp APPLY_SIGN

ERROR_BLOCK
    LD R0, NEWLINE_CHAR
    OUT
    LEA R0, ERROR_MSG   ; "ERROR! invalid input\n" [cite: 42, 113]
    PUTS
    BRnzp START_PROG    ; Restart program [cite: 33, 113]

APPLY_SIGN
    ; If negative flag is set, take 2's complement of Rx 
    ADD R4, R4, #0
    BRz EXIT_PROG
    NOT R5, R5
    ADD R5, R5, #1

EXIT_PROG
    HALT

; --- Data / Constants ---
PROMPT      .STRINGZ "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"
ERROR_MSG   .STRINGZ "ERROR! invalid input\n"
PLUS_ASCII  .FILL #-43  ; x2B
MINUS_ASCII .FILL #-45  ; x2D
ZERO_ASCII  .FILL #-48  ; x30
NINE_ASCII  .FILL #-57  ; x39
NEWLINE_CHAR .FILL x0A

.END