;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 4, ex 1
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
; Load subroutine address in R5
LD R5, SUB_FILL_ARRAY_3200 ; R5 <- x3200
; Call subroutine (i.e. jump to address in R5)
JSRR R5
HALT

; Local data

SUB_FILL_ARRAY_3200 .FILL x3200 ; SUB_FILL_ARRAY function
ARR_PTR .FILL x3100             ; ARR_PTR -> ARR

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

DO_WHILE
    ; store R2 at R3 (ARR) + n
    STR R2, R3, #0

    ADD R3, R3, #1 ; R3 += 1 (address)
    ADD R2, R2, #1 ; R2 += 1 (array value counter)
    ADD R0, R0, #-1 ; R0 -= 1 (iterator)
BRp DO_WHILE


RET
HALT

; local data
DEC_10 .FILL #10

.end