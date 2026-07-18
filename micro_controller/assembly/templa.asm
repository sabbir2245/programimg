.model small
.stack 100h
.data
    ; Define your strings here
.code
main proc
    mov ax, @data
    mov ds, ax

    ; ---------------------------
    ; WRITE YOUR PRACTICE CODE HERE
    ; ---------------------------

    mov ah, 4ch     ; Exit program
    int 21h
main endp
end main