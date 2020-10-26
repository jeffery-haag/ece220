    .ORIG x3000

;This code is a calculator that works in reverse-polish notation. It pushes numbers to a stack, and the pops the top two off whenever an operator is inputted. 
;When the equal button is hit, it pops the answer off the stack and converts it to a hex number.
;parnters: briants2, jrhaag2
	
;your code goes here

;Keyboard stuff
NXT    
    IN
	;AND R0,R0,#0
	;ADD R0,R0,#5
	
    JSR EVALUATE
    LD  R1, EQUAL1
    ADD R1, R1, R0
    BRz FIN
    BR NXT
FIN    
    HALT

EQUAL1		.FILL xFFC3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

; R0 holds output
; R1 holds current histogram location
; R2 holds data in histogram
; R3 holds current character being counted
; R4 holds down-counter from 27
; R5 holds ASCII offset / temp
; R6 is temp

;Save Registers
    ST R0, HexSaver0
    ST R2, HexSaver2
    ST R3, HexSaver3
    ST R5, HexSaver5
    ST R6, HexSaver6

; Setup
    AND R3, R3, #0
    ADD R3, R0, #0
    AND R5, R5, #0        ; Clear R5
; Find output of 4th hex character
    LD  R6, AND3        ; 4th character only
    LD  R0, OFFSET
    AND R2, R3, R6        ;    ||
    BRzp POS        ; Check if number is positive
    LD  R6, NEG4096
LOOP3    ADD R2, R6, R2        ; Decrement by 4096
    BRz DONE3
    ADD R0, R0, #1        ; Add 1 for every 4096
    BR  LOOP3
POS    LD  R6, NEG4096
LOOP2    ADD R2, R6, R2        ; Decrement by 4096
    BRn DONE2
    ADD R0, R0, #1        ; Add 1 for every 4096
    BR  LOOP2
DONE3    ADD R0, R0, #1
DONE2    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER3         ; If >0, go to letter printing section
    OUT
    ADD R5, R5, R0        ; Store number in R5
    BR  EXIT3        ; Go to next digit

; Letter output
LETTER3    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT
    ADD R5, R5, R0        ; Store number in R5
EXIT3

; Find output of 3rd hex character
    LD  R6, AND1        ; 3rd character only
    AND R2, R3, R6        ;    ||
    LD  R0, OFFSET
    LD  R6, NEG256
LOOP1    ADD R2, R6, R2        ; Decrement by 256
    BRn DONE1
    ADD R0, R0, #1        ; Increment by 1 for every 256
    BR  LOOP1
DONE1    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER2         ; If >0, go to letter printing section
    OUT
    ADD R5, R5, R0        ; Store number in R5
    BR  EXIT2        ; Go to next digit

; Letter output
LETTER2    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT
    ADD R5, R5, R0        ; Store number in R5
EXIT2

; Find output of 2nd hex number
    LD  R6, AND2        ; 2nd character only
    AND R2, R3, R6        ;    ||
    LD  R0, OFFSET
    LD  R6, NEG16
LOOP    ADD R2, R6, R2
    BRn DONE
    ADD R0, R0, #1
    BR  LOOP
DONE    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER1         ; If >0, go to letter printing section
    OUT
    ADD R5, R5, R0        ; Store number in R5
    BR  EXIT1        ; Go to next digit

; Letter output
LETTER1    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT
    ADD R5, R5, R0        ; Store number in R5
EXIT1

; Find Output of 1st hex character
    AND R2, R3, x000F    ; Last character only
    LD  R0, OFFSET
    ADD R0, R2, R0        ; Offset histogram data to numbers
    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER         ; If >0, go to letter printing section
    OUT
    ADD R5, R5, R0        ; Store number in R5
    BR  EXIT        ; Go to newline sequence

; Letter output
LETTER    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT
    ADD R5, R5, R0        ; Store number in R5
EXIT
    ADD R5, R3, #0
   

	HALT
    LD R0, HexSaver0
    LD R2, HexSaver2
    LD R3, HexSaver3
    LD R6, HexSaver6
    RET

; Labels for Hex converter
OFFSET		.FILL x0030
NINE		.FILL x0039
NEG16		.FILL #-16
NEG256		.FILL #-256
NEG4096		.FILL #-4096
POS4096		.FILL #4096
AND1		.FILL x0F00
AND2		.FILL x00F0
AND3		.FILL xF000

HexSaver0	.BLKW #1
HexSaver2	.BLKW #1
HexSaver3	.BLKW #1
HexSaver5	.BLKW #1
HexSaver6	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output

EVALUATE
; Save registers
	
    ST R0, EvalSave0    ;
    ST R1, EvalSave1    ;
    ST R2, EvalSave2    ;
    ST R3, EvalSave3    ;
    ST R4, EvalSave4    ;
    ST R5, EvalSave5    ;
    ST R6, EvalSave6    ;
    ST R7, EvalSave7    ;

;Find which character was inputted
     LD  R1, MULT
     ADD R1, R1, R0
     BRz MUL1	    ; *
     LD  R1, PLUS2
     ADD R1, R1, R0
     BRz PLUS1	    ; +
     LD  R1, MINUS
     ADD R1, R1, R0
     BRz MIN1	    ; - 
     LD  R1, DIVIS
     ADD R1, R1, R0
     BRz DIV1	    ; /
     LD  R1, PWR
     ADD R1, R1, R0
     BRz EXP1	    ; ^
     LD  R1, EQUAL
     ADD R1, R1, R0
     BRz EVAL1    	; =
     LD  R1, NEGZERO
     ADD R1, R1, R0
     BRzp NXT1		 ;
     JSR ERROR       ; Give error if not acceptable char
NXT1 LD  R1, NEGNINE
     ADD R1, R1, R0
     BRnz NXT2
     JSR ERROR       ; Give error if not acceptable char
     LD  R1, NEGSPACE
     ADD R1, R1, R0
     BRz  RET1		 ; Ignore space
NXT2 LD  R4, NEGZERO
	 ADD R0, R0, R4
     JSR PUSH        ; Push #
     BR RET1	    ; Get next character
   
; Go to operator subroutine
MUL1	JSR MUL
		BR RET1
PLUS1	JSR PLUS
		BR RET1
MIN1	JSR MIN
		BR RET1
DIV1	JSR DIV
		BR RET1
EXP1	JSR EXP
		BR RET1

;End when '=' is pressed
EVAL1   JSR POP
        ADD R3, R0, #0
    	JSR PRINT_HEX
        ;LD R0, THING
		HALT

RET1
;Reload registers
    LD R1, EvalSave1    ;
    LD R2, EvalSave2    ;
    LD R3, EvalSave3   
    LD R4, EvalSave4    ;
;   LD R5, EvalSave5    
    LD R6, EvalSave6    ;
    LD R7, EvalSave7    ;
    RET

; Labels for keyboard input
MULT		.FILL #-42
PLUS2		.FILL #-43
MINUS		.FILL xFFD3
DIVIS		.FILL #-47
EQUAL		.FILL #-61
PWR		    .FILL #-94
NEGNINE		.FILL #-57
NEGZERO		.FILL #-48
NEGSPACE	.FILL #-32
THING		.FILL #61

EvalSave0	.BLKW #1
EvalSave1	.BLKW #1
EvalSave2	.BLKW #1
EvalSave3	.BLKW #1
EvalSave4	.BLKW #1
EvalSave5	.BLKW #1
EvalSave6	.BLKW #1
EvalSave7	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;Addition subroutine

PLUS	
	ST R3, PlusSaveR3
	ST R4, PlusSaveR4
	ST R7, PlusSaveR7

	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R3,R3,R0
	
	ADD R0,R3,R4

	
	JSR PUSH
	LD R7, PlusSaveR7
	RET
MIN	;r3-r4
	ST R3, MinSaveR3
	ST R4, MinSaveR4
	ST R7, MinSaveR7
	
	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R3,R3,R0

	NOT R4,R4
	ADD R4,R4,#1
	ADD R0,R4,R3
	LD R4,MINSAVER3
	JSR PUSH
	LD R7, MinSaveR7
	
	RET

;Multiplication subroutine
MUL	
	ST R3, MulSaveR3
	ST R4, MulSaveR4
	ST R7, MulSaveR7
	
	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R4,R4,R0
	BRz ZER
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R3,R3,R0
	BRz ZER

	AND R0,R0,#0
	
MULOOP	ADD R0,R3,R0
	ADD R4,R4,#-1
	BRp MULOOP
	JSR PUSH
	LD R4,MulSaveR4
	LD R7, MulSaveR7
	RET	
ZER AND R0,R0,#0
	JSR PUSH
	LD R7,MulSaveR7
	RET

;Division subroutine
DIV	;this is r3/r4
	ST R3, DivSaveR3
	ST R7, DivSaveR7one
	

	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R4,R4,R0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R3,R3,R0
	BRz ZE
	ST R4, DivSaveR4
	AND R0,R0,#0
divlop2	ST R0,DivSaveR0
	;ST R7,DivSaveR7

	AND R0,R0,#0
	ADD R0,R3,R0
	JSR PUSH
	AND R0,R0,#0
	ADD R0,R0,R4
	JSR PUSH
	
	ST R7,DivSaveR7
	JSR MIN
	JSR POP
	LD R4, DivSaveR4
	LD R7,DivSaveR7
	ADD R0,R0,#0
	BRzp divloop
	BRn END
divloop AND R3,R3,#0
	ADD R3,R0,R3
	LD R0, DivSaveR0
	ADD R0,R0,#1
	BRzp divlop2
END	LD R0, DivSaveR0
	JSR PUSH
	LD R7, DivSaveR7one
	RET
ZE	AND R0,R0,#0
	LD R7, DivSaveR7one
	JSR PUSH
	RET

; Exponent subroutine
EXP	;this is r3^r4 into r0
	ST R3, ExpSaveR3
	ST R4, ExpSaveR4
	ST R7, ExpSaveR7one

	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R4,R4,R0
	BRz ONER
	JSR POP
	ADD R5,R5,#0
	BRp ERROR
	ADD R3,R3,R0
	
	AND R0,R0,#0
	ADD R0,R0,R4 ;RO HAS R4
	ADD R0,R0,#-1
	AND R4,R4,#0
	ADD R4,R3,#0  ;R4 AND R3 BOTH HABE NUMBER STORESD IN R3

EXPloop	ST R0,ExpSaveR0
	ST R7,ExpSaveR7

	AND R0,R0,#0
	ADD R0,R3,R0
	JSR PUSH
	AND R0,R0,#0
	ADD R0,R0,R4
	JSR PUSH
	
	ST R7,ExpSaveR7
	JSR MUL

	LD R7,ExpSaveR7
	AND R3,R3,#0
	ADD R3,R0,#0
	LD R0,ExpSaveR0
	ADD R0,R0,#-1
	BRp EXPloop
	
	AND R0,R0,#0
	ADD R0,R0,R3
	JSR PUSH
	LD R7, ExpSaveR7one
	RET
ONER	AND R0,R0,#0
	ADD R0,R0,#1
	JSR PUSH
	LD R7, ExpSaveR7one
	RET
	
; Push to stack
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
; Pop from stack
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R4
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET
; Error message for bad characters
ERROR 
;	AND R0,R0,0
	BRnzp ENDING

;Output error message
ENDING LEA R0, ERRMSG
       PUTS
		HALT

; Memory locations
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
PlusSaveR3	.BLKW #1
PlusSaveR4      .BLKW #1
PlusSaveR7      .BLKW #1
MinSaveR3       .BLKW #1
MinSaveR4       .BLKW #1
MinSaveR7       .BLKW #1
MulSaveR3       .BLKW #1
MulSaveR4       .BLKW #1
MulSaveR7       .BLKW #1
DivSaveR3       .BLKW #1
DivSaveR4       .BLKW #1
DivSaveR0       .BLKW #1
DivSaveR7	.BLKW #1
DivSaveR7one 	.BLKW #1
ExpSaveR3	.BLKW #1
ExpSaveR4	.BLKW #1
ExpSaveR0	.BLKW #1
ExpSaveR7 	.BLKW #1
ExpSaveR7one	.BLKW #1

; Error message
ERRMSG		.STRINGZ "Invalid Expression"

.END
