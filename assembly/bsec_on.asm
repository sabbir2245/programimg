.model small
.stack 100h
.data
    prompt db 'Enter n: $', 0
    newline db 0dh, 0ah, '$'
    n dw 0


;Enter n: 6
;1
;*2
;1*3
;*2*4
;1*3*5
;*2*4*6

.code
main proc
    mov ax, @data
    mov ds, ax

    ; Print prompt
    mov ah, 09h
    lea dx, prompt
    int 21h

    ; Read single digit character for 'n'
    mov ah, 01h
    int 21h
    sub al, '0'         ; Convert ASCII to integer
    mov ah, 0
    mov n, ax           ; Save n

    ; Print a newline after input
    mov ah, 09h
    lea dx, newline
    int 21h

    ; Initialize outer loop counter i = 1
    mov cx, 1

outer_loop:
    mov ax, n
    cmp cx, ax          ; Loop condition: if i > n, exit
    jg exit_program

    ; Initialize inner loop counter j = 1
    mov bx, 1

inner_loop:
    cmp bx, cx          ; Loop condition: if j > i, finish row
    jg row_done

    ; ---- Parity Logic Check ----
    ; We check if (i % 2) == (j % 2).
    ; A quick trick: if (i + j) is even, their parities are the same!
    mov ax, cx
    add ax, bx          ; AX = i + j
    test ax, 1          ; Check the LSB (Lowest Significant Bit)
    jz print_digit      ; If LSB is 0, sum is even -> print digit j

print_star:
    mov ah, 02h
    mov dl, '*'
    int 21h
    jmp next_col

print_digit:
    mov ah, 02h
    mov dx, bx          ; Copy column index j
    add dl, '0'         ; Convert to ASCII character
    int 21h

next_col:
    inc bx              ; j++
    jmp inner_loop

row_done:
    ; Print newline at the end of the row
    mov ah, 09h
    lea dx, newline
    int 21h

    inc cx              ; i++
    jmp outer_loop

exit_program:
    mov ah, 4ch         ; Terminate program
    int 21h
main endp
end main