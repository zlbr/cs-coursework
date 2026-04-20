;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 4, ex 3
; Lab section: 21
; TA: <omitted>
; 
;=================================================

; =======================================================
; Main
; Test harness for SUB_FILL_ARRAY subroutine
; =======================================================
.ORIG x3000


LD R1, ARR_PTR ; R1 <- array address

LD R5, SUB_FILL_ARRAY_3200 ; R5 <- x3200
JSRR R5 ; SUB_FILL_ARRAY_3200()


LD R5, SUB_CONVERT_ARRAY_3400 ; R5 <- x3400
JSRR R5 ; SUB_CONVERT_ARRAY()

LD R5, SUB_PRINT_ARRAY_3600 ; R5 <- x3600
JSRR R5 ; SUB_PRINT_ARRAY()

HALT

; Local data

SUB_FILL_ARRAY_3200 .FILL x3200    ; SUB_FILL_ARRAY function
SUB_CONVERT_ARRAY_3400 .FILL x3400 ; SUB_FILL_ARRAY function
SUB_PRINT_ARRAY_3600 .FILL x3600   ; SUB_PRINT_ARRAY function
ARR_PTR .FILL x3100                ; ARR_PTR -> ARR

.END

;------------------------------------------------------------------------
; Array storage memory - x3100
;------------------------------------------------------------------------
.ORIG x3100
ARR .BLKW #10
.END

;------------------------------------------------------------------------
; Subroutine: SUB_FILL_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: The array has values from 0 through 9.
; Return Value (None)
;-------------------------------------------------------------------------
.orig x3200

; local data: R2: temporary address
; l           R3: counter

; initialize R0 as counter (i=10)
AND R0, R0, #0
ADD R0, R0, #10

; zero registers
AND R2, R2, #0
AND R3, R3, #0

; store R1 in R3 to keep R1 unmodified
ADD R3, R3, R1

WHILE_FILL_ELEMENTS
    ; store R2 at R3 (ARR) + n
    STR R2, R3, #0

    ADD R3, R3, #1 ; R3 += 1 (address)
    ADD R2, R2, #1 ; R2 += 1 (array value counter)
    ADD R0, R0, #-1 ; R0 -= 1 (iterator)
BRp WHILE_FILL_ELEMENTS


RET
HALT

; local data
DEC_10 .FILL #10

.end

;------------------------------------------------------------------------
; Subroutine: SUB_CONVERT_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (number) in the array should be represented as a character. E.g. 0 -> ‘0’
; Return Value (None)
;-------------------------------------------------------------------------

.orig x3400

; local data: R2: temporary address
; l           R3: counter
;             R6: temporary (DEC_48)

; initialize R0 as counter (i=10)
AND R0, R0, #0
ADD R0, R0, #10

; load DEC_48
AND R6, R6, #0
LD R6, DEC_48

; zero registers
AND R2, R2, #0
AND R3, R3, #0

; store R1 in R3 to keep R1 unmodified
ADD R3, R3, R1

WHILE_ITER_ELEMENTS
    ; store the value of arr[i] (R3) to R2
    LDR R2, R3, #0
    
    ; number to ascii = n+48
    ADD R2, R2, R6
    
    ; store R2 at R3 (ARR) + n
    STR R2, R3, #0

    ADD R3, R3, #1 ; R3 += 1 (address)
    ADD R2, R2, #1 ; R2 += 1 (array value counter)
    ADD R0, R0, #-1 ; R0 -= 1 (iterator)
BRp WHILE_ITER_ELEMENTS


RET
HALT

DEC_48 .FILL #48

.end


;------------------------------------------------------------------------
; Subroutine: SUB_PRINT_ARRAY
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (character) in the array is printed out to the console.
; Return Value (None)
;-------------------------------------------------------------------------

.orig x3600

; local data: R2: temporary address
; l           R3: counter

; initialize R2 as counter (i=10)
AND R2, R2, #0
ADD R2, R2, #10

; load DEC_48
AND R6, R6, #0

; zero registers
AND R3, R3, #0

; store R1 in R3 to keep R1 unmodified
ADD R3, R3, R1

WHILE_PRINT_ELEMENTS
    ; store the value of arr[i] (R3) to R2 then print it
    LDR R0, R3, #0
    OUT

    ADD R3, R3, #1 ; R3 += 1 (address)
    ADD R2, R2, #-1 ; R2 -= 1 (iterator)
BRp WHILE_PRINT_ELEMENTS


RET
HALT

.end
