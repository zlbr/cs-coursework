;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 3, ex 1
; Lab section: 21
; TA: <omitted>
; 
;=================================================

.orig x3000

LD R5, DEC_65_PTR
LD R6, HEX_41_PTR

LDR R3, R5, #1
LDR R4, R6, #0

ADD R3, R3, #1
ADD R4, R4, #1

STR R5, R3, #0
STR R6, R4, #0

HALT

DEC_65_PTR .FILL x4000
HEX_41_PTR .FILL x4001

.end

;; Remote data
.orig x4000
NEW_DEC_65 .FILL #65
NEW_HEX_41 .FILL x41
.end