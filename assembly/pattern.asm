; Problem: Print pattern for input n. 
; For n=3: 
; ##1 
; #12 
; 123
.MODEL SMALL
.STACK 100H
.DATA
    N DB ?
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; taking  Input n
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV N, AL
    
    MOV AH, 2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H

    MOV CX, 1          ; Row counter i = 1
ROW_LOOP:
    PUSH CX
    
    ; Print (N-i) '#' characters
    MOV AL, N
    SUB AL, CL         ; AL = N - i
    MOV BL, AL
    CMP BL, 0
    JE PRINT_NUMBERS
HASH_LOOP:
    MOV AH, 2
    MOV DL, '#'
    INT 21H
    DEC BL
    JNZ HASH_LOOP

PRINT_NUMBERS:
    MOV BL, 1          ; Number counter j = 1
NUM_LOOP:
    MOV AH, 2
    MOV DL, BL
    ADD DL, '0'
    INT 21H
    INC BL
    CMP BL, CL
    JBE NUM_LOOP

    ; New line
    MOV AH, 2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H

    POP CX
    INC CX
    MOV AL, N
    CBW
    CMP CX, AX
    JBE ROW_LOOP

    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN