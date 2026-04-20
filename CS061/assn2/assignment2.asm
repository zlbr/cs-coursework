;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Zachary Brasher
; Email: <omitted>
; 
; Assignment name: Assignment 2
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

;----------------------------------------------
;output prompt
;----------------------------------------------	
LEA R0, intro			; get starting address of prompt string
PUTS			    	; Invokes BIOS routine to output string



;-------------------------------
;INSERT YOUR CODE here
;--------------------------------

; R0: temporary in/out data
; R1: number 1
; R2: number 2
; R3: result

; zero registers
AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0

LD R4, NEG_48
LD R5, POS_48

; get number 1 to R1
TRAP x20
OUT
ADD R1, R0, R4

; newline
LD R0, newline
OUT

; get number 2 to R2
TRAP x20
OUT
ADD R2, R0, R4

; newline
LD R0, newline
OUT

; calculate negative of R2
NOT R2, R2 ; 1's comp
ADD R2, R2, #1 ; 2's comp

; R3 = R1 + R2
ADD R3, R1, R2

; print R1
ADD R0, R1, R5
OUT

; print " - "
LEA R0, minus
PUTS

; print R2 (2's comp)
ADD R0, R2, #-1
NOT R0, R0
ADD R0, R0, R5
OUT

; print " = "
LEA R0, equals
PUTS

;;;;;;;;;;;;;

ADD R0, R3, #0

BRzp OUTPUT

IF_NEGATIVE
    LD R0, minus_ascii
    OUT
    
    ADD R3, R3, #-1
    NOT R3, R3

OUTPUT
    ; print R3
    ADD R0, R3, R5
    OUT


; newline
LD R0, newline
OUT

HALT				; Stop execution of program
;------	
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL x0A	; newline character - use with LD followed by OUT
minus_ascii .FILL x2d
minus .STRINGZ " - "
equals .STRINGZ " = "
NEG_48 .FILL #-48
POS_48 .FILL #48
DEC_64 .FILL #64

;---------------	
;END of PROGRAM
;---------------	
.END

