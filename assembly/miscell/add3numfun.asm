.MODEL SMALL
.STACK 100H

.DATA
    MSG_INPUT  DB 'Enter a single-digit number: ', '$'
    MSG_RESULT DB 0DH, 0AH, 'The sum is: ', '$'
    
    NUM1 DW 0
    NUM2 DW 0
    NUM3 DW 0
    RESULT DW 0

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; --- 1. Get First Number ---
    MOV AH, 9
    LEA DX, MSG_INPUT
    INT 21H
    
    MOV AH, 1           ; DOS input character function
    INT 21H
    SUB AL, '0'         ; Convert ASCII character to raw numeric digit
    MOV AH, 0           ; Clear AH to safely store 16-bit word
    MOV NUM1, AX        ; Store it
    
    ; Print a newline for clean formatting
    CALL PRINT_NEWLINE

    ; --- 2. Get Second Number ---
    MOV AH, 9
    LEA DX, MSG_INPUT
    INT 21H
    
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV AH, 0
    MOV NUM2, AX
    
    CALL PRINT_NEWLINE

    ; --- 3. Get Third Number ---
    MOV AH, 9
    LEA DX, MSG_INPUT
    INT 21H
    
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV AH, 0
    MOV NUM3, AX

    ; --- 4. Pass Parameters via Stack & Call Function ---
    PUSH NUM1           ; First parameter  -> [BP + 8]
    PUSH NUM2           ; Second parameter -> [BP + 6]
    PUSH NUM3           ; Third parameter  -> [BP + 4]
    
    CALL SUM_THREE      ; Result returns in AX
    MOV RESULT, AX      ; Save result

    ; --- 5. Print the Result ---
    MOV AH, 9
    LEA DX, MSG_RESULT
    INT 21H

    MOV AX, RESULT
    CALL PRINT_NUM      ; Call helper to handle multidigit display (e.g. 9+9+9 = 27)

    ; Terminate Program
    MOV AH, 4CH
    INT 21H
MAIN ENDP


; --- Function: Adds Three Numbers Passed via Stack ---
SUM_THREE PROC
    PUSH BP             ; Save old BP
    MOV BP, SP          ; Establish stack frame anchor
    
    ; Grab parameters using offsets relative to BP
    MOV AX, [BP+8]      ; Fetch NUM1
    ADD AX, [BP+6]      ; Add NUM2
    ADD AX, [BP+4]      ; Add NUM3
    
    POP BP              ; Restore old BP
    RET 6               ; Clean up 3 parameters (3 words = 6 bytes)
SUM_THREE ENDP


; --- Helper: Print Newline ---
PRINT_NEWLINE PROC
    MOV AH, 2
    MOV DL, 0DH         ; Carriage Return
    INT 21H
    MOV DL, 0AH         ; Line Feed
    INT 21H
    RET
PRINT_NEWLINE ENDP


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