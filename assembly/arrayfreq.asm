; Problem: Count occurrences of a digit in a user-input array.
.MODEL SMALL
.STACK 100H
.DATA
    ARRAY DB 10 DUP(?)
    SIZE DB ?
    SEARCH DB ?
    COUNT DB 0
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Input Size
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV SIZE, AL
    
    ; Space separator
    MOV AH, 2
    MOV DL, ' '
    INT 21H

    ; Input Array Elements
    XOR CX, CX
    MOV CL, SIZE
    MOV SI, 0
INPUT_LOOP:
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV ARRAY[SI], AL
    INC SI
    ; Space
    MOV AH, 2
    MOV DL, ' '
    INT 21H
    LOOP INPUT_LOOP

    ; Input Search Value
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV SEARCH, AL

    ; Count Occurrences
    MOV CL, SIZE
    MOV SI, 0
    MOV BL, SEARCH
CHECK_LOOP:
    CMP ARRAY[SI], BL
    JNE NEXT
    INC COUNT
NEXT:
    INC SI
    LOOP CHECK_LOOP

    ; New line and Output
    MOV AH, 2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H
    
    MOV DL, COUNT
    ADD DL, '0'
    INT 21H

    MOV AH, 4CH
    INT 21H
MAIN ENDP
END MAIN