; Problem: Given a positive integer n (0 < n < 65535), find the sum of its digits recursively.
; The function takes n as a parameter and returns the sum.
; No user input or console output is required.

.MODEL SMALL
.STACK 100H

.DATA
    N DW 23126          ; Example input (Expected Output: 14)
    RESULT DW 0

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Push parameter n onto stack
    PUSH N
    CALL SUM_DIGITS     ; Result will be in AX
    MOV RESULT, AX      ; Store result

    ; Terminate program
    MOV AH, 4CH
    INT 21H
MAIN ENDP

; --- Recursive Function to Sum Digits ---
SUM_DIGITS PROC
    PUSH BP
    MOV BP, SP
    
    MOV AX, [BP+4]      ; Load n into AX
    
    ; Base Case: If AX is 0, return 0
    CMP AX, 0
    JE BASE_CASE
    
    ; Recursive Step: (n % 10) + SUM_DIGITS(n / 10)
    MOV DX, 0           ; Clear DX for division
    MOV BX, 10
    DIV BX              ; AX = n/10, DX = n%10
    
    PUSH DX             ; Save remainder (digit) on stack
    PUSH AX             ; Push n/10 for next recursive call
    CALL SUM_DIGITS
    
    ; AX now contains SUM_DIGITS(n / 10)
    POP DX              ; Restore current digit
    ADD AX, DX          ; AX = digit + SUM_DIGITS(n / 10)
    JMP EXIT_FUNC

BASE_CASE:
    XOR AX, AX          ; Return 0

EXIT_FUNC:
    POP BP
    RET 2               ; Clean up stack (1 parameter = 2 bytes)
SUM_DIGITS ENDP

END MAIN