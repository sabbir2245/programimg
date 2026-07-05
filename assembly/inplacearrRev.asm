; Problem: Reverse an array of 8 elements in-place.
.MODEL SMALL
.STACK 100H
.DATA
    ARRAY DB 1, 3, 5, 2, 9, 2, 3, 10 ; Example 1
    SIZE DW 8
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Reverse logic: Swap i-th element with (SIZE-1-i)-th element
    MOV CX, 4          ; SIZE / 2
    MOV SI, 0          ; Start index
    MOV DI, 7          ; End index (SIZE-1)

REVERSE_LOOP:
    MOV AL, ARRAY[SI]
    MOV BL, ARRAY[DI]
    MOV ARRAY[SI], BL
    MOV ARRAY[DI], AL
    INC SI
    DEC DI
    LOOP REVERSE_LOOP

    ; Output Reversed Array
    MOV CX, 8
    MOV SI, 0
PRINT_LOOP:
    MOV AL, ARRAY[SI]
    MOV AH, 0
    CALL PRINT_NUM     ; Helper to print multi-digit numbers (0-14)
    
    MOV AH, 2
    MOV DL, ' '
    INT 21H
    INC SI
    LOOP PRINT_LOOP

    MOV AH, 4CH
    INT 21H
MAIN ENDP

PRINT_NUM PROC
    ; Prints number in AX
    CMP AX, 10
    JL SINGLE_DIGIT
    MOV BL, 10
    DIV BL             ; AL = Quotient, AH = Remainder
    PUSH AX
    MOV DL, AL
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    POP AX
    MOV DL, AH
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    RET
SINGLE_DIGIT:
    MOV DL, AL
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    RET
PRINT_NUM ENDP
END MAIN