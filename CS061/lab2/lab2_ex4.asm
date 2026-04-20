;=================================================
; Name: Zachary Brasher
; Email: <omitted>
; 
; Lab: lab 2, ex 4
; Lab section: 21
; TA: <omitted>
; 
;=================================================

.orig x3000
;; program

LD R0, HEX_97
LD R1, HEX_26

DO_WHILE
    ADD R0, R0, #1
    ADD R1, R1, #-1
    OUT
BRp DO_WHILE


HALT

;; program data
HEX_97 .FILL x61
HEX_26 .FILL x1A

.end