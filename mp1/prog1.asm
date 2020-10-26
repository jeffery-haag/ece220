; The code given to you here implements the histogram calculation that
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of
; code to print the histogram to the monitor.
;
; If you finish your program,
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


    .ORIG    x3000        ; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string
; terminated by a NUL character.  Lower case and upper case should
; be counted together, and a count also kept of all non-alphabetic
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance)
; should be stored starting at x3F00, with the non-alphabetic count
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

    LD R0,HIST_ADDR          ; point R0 to the start of the histogram
   
    ; fill the histogram with zeroes
    AND R6,R6,#0        ; put a zero into R6
    LD R1,NUM_BINS        ; initialize loop count to 27
    ADD R2,R0,#0        ; copy start of histogram into R2

    ; loop to fill histogram starts here
HFLOOP    STR R6,R2,#0        ; write a zero into histogram
    ADD R2,R2,#1        ; point to next histogram entry
    ADD R1,R1,#-1        ; decrement loop count
    BRp HFLOOP        ; continue until loop count reaches zero

    ; initialize R1, R3, R4, and R5 from memory
    LD R3,NEG_AT        ; set R3 to additive inverse of ASCII '@'
    LD R4,AT_MIN_Z        ; set R4 to difference between ASCII '@' and 'Z'
    LD R5,AT_MIN_BQ        ; set R5 to difference between ASCII '@' and '`'
    LD R1,STR_START        ; point R1 to start of string

    ; the counting loop starts here
COUNTLOOP
    LDR R2,R1,#0        ; read the next character from the string
    BRz PRINT_HIST        ; found the end of the string

    ADD R2,R2,R3        ; subtract '@' from the character
    BRp AT_LEAST_A        ; branch if > '@', i.e., >= 'A'
NON_ALPHA
    LDR R6,R0,#0        ; load the non-alpha count
    ADD R6,R6,#1        ; add one to it
    STR R6,R0,#0        ; store the new non-alpha count
    BRnzp GET_NEXT        ; branch to end of conditional structure
AT_LEAST_A
    ADD R6,R2,R4        ; compare with 'Z'
    BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA    ADD R2,R2,R0        ; point to correct histogram entry
    LDR R6,R2,#0        ; load the count
    ADD R6,R6,#1        ; add one to it
    STR R6,R2,#0        ; store the new count
    BRnzp GET_NEXT        ; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
    ADD R2,R2,R5        ; subtract '`' - '@' from the character
    BRnz NON_ALPHA        ; if <= '`', i.e., < 'a', go increment non-alpha
    ADD R6,R2,R4        ; compare with 'z'
    BRnz ALPHA        ; if <= 'z', go increment alpha count
    BRnzp NON_ALPHA        ; otherwise, go increment non-alpha

GET_NEXT
    ADD R1,R1,#1        ; point to next character in string
    BRnzp COUNTLOOP        ; go to start of counting loop



PRINT_HIST
;                                                        INTRO PARAGRAPH
; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; This histogram printing code outputs the number of times a character is used in a string. It has a 4-digit hex output, and each digit is iterated separately from the other.
; It works by decrementing by powers of 16, and incrementing the output for each digit for that specific power of 16.
; I offset the supplied histogram based on whether it should output a letter or number.
; Partner: briants2

; R0 holds output
; R1 holds current histogram location
; R2 holds data in histogram
; R3 holds current character being counted
; R4 holds down-counter from 27
; R5 holds ASCII offset / temp
; R6 is temp

; Setup
    LD  R1, HIST_ADDR    ; Initialize Registers
    LD  R4, NUM_BINS    ;    ||
    LD  R3, CHAR_USED    ;    ||

; Output sequence
NEXT    ADD R0, R3, #0        ; Output current character
    OUT
    LD  R0, SPACE        ; Space between character and histogram data
    OUT

; Find output of 4th hex character
    LDR R2, R1, #0        ; Load histogram data
    LD  R6, AND3        ; 4th character only
    AND R2, R2, R6        ;    ||
    LD  R0, OFFSET
    LD  R6, NEG4096
LOOP2    ADD R2, R6, R2        ; Decrement by 4096
    BRn DONE2
    ADD R0, R0, #1        ; Add 1 for every 4096
    BR  LOOP2
DONE2    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER3         ; If >0, go to letter printing section
    OUT            ; Print number
    BR  EXIT3        ; Go to next digit

; Letter output
LETTER3    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT            ; Output letter
EXIT3

; Find output of 3rd hex character
    LDR R2, R1, #0        ; Load histogram data
    LD  R6, AND1        ; 3rd character only
    AND R2, R2, R6        ;    ||
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
    OUT            ; Print number
    BR  EXIT2        ; Go to next digit

; Letter output
LETTER2    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT            ; Output letter
EXIT2

; Find output of 2nd hex number
    LDR R2, R1, #0        ; Load histogram data
    LD  R6, AND2        ; 2nd character only
    AND R2, R2, R6        ;    ||
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
    OUT            ; Print number
    BR  EXIT1        ; Go to next digit

; Letter output
LETTER1    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT            ; Output letter
EXIT1

; Find Output of 1st hex character
    LDR R2, R1, #0        ; Load histogram data
    AND R2, R2, x000F    ; Last character only
    LD  R5, OFFSET
    ADD R0, R2, R5        ; Offset histogram data to numbers
    LD  R6, NINE        ; Load ASCII value of '9'
    NOT R6, R6        ; Subtract that from R0
    ADD R6, R6, #1        ;    ||
    ADD R6, R6, R0        ;    ||
    BRp LETTER         ; If >0, go to letter printing section
    OUT            ; Print number
    BR  EXIT        ; Go to newline sequence

; Letter output
LETTER    ADD R0, R0, #7        ; Find Letter to output (7 is the difference between '9' and 'A')
    OUT            ; Output letter

; NEWLINE Sequence
EXIT    LD  R0, NEWLINE        ; Insert NEWLINE
    OUT
    ADD R1, R1, #1        ; Go to next character to output
    ADD R3, R3, #1        ; Load next character to be displayed
    ADD R4, R4, #-1        ; Decrement counter
    BRp NEXT        ; End if 27 lines have been output

    HALT            ; done


; the data needed by the program
NUM_BINS    .FILL #27    ; 27 loop iterations
NEG_AT        .FILL xFFC0    ; the additive inverse of ASCII '@'
AT_MIN_Z    .FILL xFFE6    ; the difference between ASCII '@' and 'Z'
AT_MIN_BQ    .FILL xFFE0    ; the difference between ASCII '@' and '`'
HIST_ADDR    .FILL x3F00     ; histogram starting address
STR_START    .FILL x4000    ; string starting address
CHAR_USED    .FILL x0040    ; ASCII value of '@'
SPACE        .FILL x0020    ; ASCII value of ' '
NEWLINE        .FILL x000A    ; ASCII value of the NEWLINE character
OFFSET        .FILL x0030    ; ASCII offset to get to numbers
NINE        .FILL x0039    ; ASCII value of '9'
NEG16        .FILL #-16    ; Negative 16
NEG256        .FILL #-256    ; Negative 256
NEG4096        .FILL #-4096    ; Negative 4096
AND1        .FILL x0F00    ; Allow only 0x00
AND2        .FILL x00F0    ; Allow only 00x0
AND3        .FILL xF000    ; Allow only x000

; for testing, you can use the lines below to include the string in this
; program...
;STR_START    .FILL STRING    ; string starting address
;STRING        .STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz!!!"



    ; the directive below tells the assembler that the program is done
    ; (so do not write any code below it!)

    .END
