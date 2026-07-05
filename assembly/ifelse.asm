.model small
.stack 100h
.data
    msg1      db 0dh, 0ah, "Enter first 2-digit number: $"
    msg2      db 0dh, 0ah, "Enter second 2-digit number: $"
    msg_sum   db 0dh, 0ah, "The sum is: $"
    msg_comp1 db 0dh, 0ah, "First number is greater.$"
    msg_comp2 db 0dh, 0ah, "Second number is greater.$"
    msg_equal db 0dh, 0ah, "Both numbers are equal.$"
    msg_even  db 0dh, 0ah, "The bigger one is even.$"
    msg_odd   db 0dh, 0ah, "The bigger one is odd.$"
    
    num1      db 0
    num2      db 0
    bigger    db 0

.code
main proc
    mov ax, @data
    mov ds, ax

    ; ---- INPUT FIRST NUMBER ----
    mov ah, 09h
    lea dx, msg1
    int 21h
    
    ; Get first digit
    mov ah, 01h
    int 21h
    sub al, '0'         ; Convert ASCII to actual digit
    mov bl, 10
    mul bl              ; AL = first digit * 10 = first digit * bl ( which is 10 ) , cause Ab is 10A +b 
    mov num1, al
    
    ; Get second digit
    mov ah, 01h
    int 21h
    sub al, '0'
    add num1, al        ; num1 now holds the full 2-digit value

    ; ---- INPUT SECOND NUMBER ----
    mov ah, 09h
    lea dx, msg2
    int 21h
    
    ; Get first digit
    mov ah, 01h
    int 21h
    sub al, '0'
    mov bl, 10
    mul bl
    mov num2, al
    
    ; Get second digit
    mov ah, 01h
    int 21h
    sub al, '0'
    add num2, al        ; num2 now holds the full 2-digit value

    ; ---- PRINT THE SUM ----
    mov ah, 09h
    lea dx, msg_sum
    int 21h
    
    mov al, num1
    add al, num2        ; AL = num1 + num2
    xor ah, ah          ; Clear AH for division (AX = sum)
    call print_num      ; Print the sum (can handle up to 3 digits)

    ; ---- COMPARE THE NUMBERS ----
    mov al, num1
    cmp al, num2
    je  is_equal
    jg  first_greater

    ; If here, num2 is greater
    mov ah, 09h
    lea dx, msg_comp2
    int 21h
    mov al, num2
    mov bigger, al
    jmp check_parity

first_greater:
    mov ah, 09h
    lea dx, msg_comp1
    int 21h
    mov al, num1
    mov bigger, al
    jmp check_parity

is_equal:
    mov ah, 09h
    lea dx, msg_equal
    int 21h
    mov al, num1        ; If equal, either is the "bigger" one
    mov bigger, al

    ; ---- CHECK PARITY OF THE BIGGER ONE ----
check_parity:
    mov al, bigger
    test al, 1          ; Test the Least Significant Bit (LSB)
    jz  is_even         ; If LSB is 0, number is even

    ; If here, it's odd
    mov ah, 09h
    lea dx, msg_odd
    int 21h
    jmp exit

is_even:
    mov ah, 09h
    lea dx, msg_even
    int 21h

exit:
    mov ah, 4ch         ; DOS terminate program function
    int 21h
main endp

; -------------------------------------------------------------
; SUBROUTINE: Prints a number stored in AX (up to 3 decimal digits)
; -------------------------------------------------------------
print_num proc
    push ax
    push bx
    push cx
    push dx

    mov cx, 0           ; Digit counter
    mov bx, 10          ; Divisor

store_digits:
    xor dx, dx          ; Clear DX for division
    div bx              ; AX = quotient, DX = remainder
    push dx             ; Push remainder (digit) to stack
    inc cx              ; Increment digit count
    cmp ax, 0
    jne store_digits    ; Loop if quotient is not zero

print_loop:
    pop dx              ; Pop digit
    add dl, '0'         ; Convert to ASCII
    mov ah, 02h         ; Print character function
    int 21h
    loop print_loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_num endp

end main