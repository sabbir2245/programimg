.MODEL SMALL
.STACK 100H

.DATA
    ; Example array: 2 + 6 + 10 + 4 = 22 (1, 3, and 7 are ignored)
    MY_ARRAY DW 2, 1, 6, 3, 10, 7, 4 
    ARRAY_SIZE DW 7
    
    MSG_RESULT DB 'The sum of even numbers is: ', '$'
    RESULT DW 0

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; --- 1. Pass Parameters via Stack ---
    LEA AX, MY_ARRAY    ; Get the starting memory address of the array
    PUSH AX             ; Parameter 1: Array Offset Address -> [BP + 6]
    
    PUSH ARRAY_SIZE     ; Parameter 2: Number of elements   -> [BP + 4]

    ; --- 2. Call Function ---
    CALL SUM_EVEN       ; Result will be returned in AX
    MOV RESULT, AX      ; Save the calculated sum

    ; --- 3. Print the Result ---
    MOV AH, 9
    LEA DX, MSG_RESULT
    INT 21H

    MOV AX, RESULT
    CALL PRINT_NUM      ; Display the multi-digit decimal number

    ; Terminate Program
    MOV AH, 4CH
    INT 21H
MAIN ENDP


; --- Function: Sums Only Even Numbers in an Array ---
SUM_EVEN PROC
    PUSH BP
    MOV BP, SP
    
    ; Set up registers from stack parameters
    MOV CX, [BP+4]      ; CX = Array Size (Loop counter)
    MOV BX, [BP+6]      ; BX = Base Address pointer to the array
    
    XOR AX, AX          ; Clear AX to accumulate the sum

ARRAY_LOOP:
    MOV DX, [BX]        ; Load the current element into DX
    
    ; Check if the number is even using a bitwise TEST
    ; Even numbers always have a 0 as their lowest bit (LSB).
    TEST DX, 1          ; Performs a logical AND but doesn't change DX
    JNZ SKIP_ODD        ; If result is NOT zero (LSB is 1), it's odd -> Skip it!
    
    ADD AX, DX          ; If it's even, add it to our running total in AX

SKIP_ODD:
    ADD BX, 2           ; Move pointer to the next Word element (2 bytes)
    LOOP ARRAY_LOOP     ; Decrement CX, repeat until CX = 0

    POP BP
    RET 4               ; Clean up 2 parameters (2 words = 4 bytes)
SUM_EVEN ENDP


; --- Helper: Multi-digit Decimal Printer ---
PRINT_NUM PROC
    MOV BX, 10
    MOV CX, 0

CONVERT_LOOP:
    MOV DX, 0
    DIV BX
    PUSH DX
    INC CX
    CMP AX, 0
    JNE CONVERT_LOOP

PRINT_LOOP:
    POP DX
    ADD DL, '0'
    MOV AH, 2
    INT 21H
    LOOP PRINT_LOOP
    RET
PRINT_NUM ENDP

END MAIN