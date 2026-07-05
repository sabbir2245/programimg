.model small 
.stack 100h 
.data 

a db " hello world $ " 

.code 

main proc 

    mov ax , @data
    mov ds ,ax 


    mov ah , 09h
    mov dx , a 
    int 21h 

    mov ah , 4ch
    int 21h 

main endp
end main
