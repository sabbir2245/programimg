; Problem: Find n-th Fibonacci number recursively.
; Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
.MODEL SMALL
.STACK 100H
.DATA
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Input n
    MOV AH, 1
    INT 21H
    SUB AL, '0'
    MOV AH, 0
    
    PUSH AX
    CALL FIB
    ADD SP, 2 ; Clean stack

    ; Result is in AX
    MOV DX, AX
    ADD DL, '0'
    MOV AH, 2
    INT 21H

    MOV AH, 4CH
    INT 21H
MAIN ENDP

FIB PROC
    PUSH BP
    MOV BP, SP
    MOV AX, [BP+4] ; Get n

    CMP AX, 1
    JBE FIB_BASE   ; If n <= 1, return n

    ; Call Fib(n-1)
    DEC AX
    PUSH AX
    CALL FIB
    PUSH AX        ; Save result of Fib(n-1)

    ; Call Fib(n-2)
    MOV AX, [BP+4]
    SUB AX, 2
    PUSH AX
    CALL FIB
    
    POP BX         ; Get Fib(n-1)
    ADD AX, BX     ; AX = Fib(n-1) + Fib(n-2)
    JMP FIB_EXIT

FIB_BASE:
    ; AX already contains n (0 or 1)
FIB_EXIT:
    POP BP
    RET 2
FIB ENDP
END MAIN