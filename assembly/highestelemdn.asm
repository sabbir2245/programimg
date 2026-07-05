; Problem: Find the second highest element in an array of 10 elements.
.MODEL SMALL
.STACK 100H
.DATA
    ARRAY DB 1, 3, 10, 12, 4, 6, 2, 9, 7, 11
    MAX1 DB 0
    MAX2 DB 0
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    MOV SI, 0
    MOV CX, 10

FIND_LOOP:
    MOV AL, ARRAY[SI]
    CMP AL, MAX1
    JG NEW_MAX1
    CMP AL, MAX2
    JG NEW_MAX2
    JMP NEXT_ITER

NEW_MAX1:
    MOV BL, MAX1
    MOV MAX2, BL    ; Old Max1 becomes Max2
    MOV MAX1, AL    ; New Max1
    JMP NEXT_ITER

NEW_MAX2:
    MOV MAX2, AL

NEXT_ITER:
    INC SI
    LOOP FIND_LOOP

    ; Print MAX2
    MOV AL, MAX2
    MOV AH, 0
    CALL PRINT_NUM ; Using multi-digit print from C2 logic

    MOV AH, 4CH
    INT 21H
MAIN ENDP

PRINT_NUM PROC
    CMP AX, 10
    JL S_DIGIT
    MOV BL, 10
    DIV BL
    MOV BH, AH
    MOV DL, AL
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    MOV DL, BH
    ADD DL, '0'
    INT 21H
    RET
S_DIGIT:
    MOV DL, AL
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    RET
PRINT_NUM ENDP
END MAIN