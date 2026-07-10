# 8086 Assembly: How Printing Works (16-bit DOS)

In 16-bit 8086 Assembly, you do not talk directly to the monitor or screen. Instead, you make a standardized request to the operating system (typically **MS-DOS** or an emulator like EMU8086/DOSBox). 

Think of the operating system as a giant customer service desk with hundreds of specialized departments. To get anything displayed on the screen, you must strictly follow a three-step protocol:
1. **Choose the department:** Put a specific function number in the `AH` register.
2. **Hand over the paperwork:** Put your data, payload, or arguments in registers like `DL` or `DX`.
3. **Press the service call button:** Trigger the interrupt instruction `INT 21h`.

---

## Why do we move things to the `AH` register?

The `AX` (Accumulator) register is a 16-bit register split into two independent 8-bit halves:
* **`AH`** (Accumulator High byte)
* **`AL`** (Accumulator Low byte)

By architectural convention, the DOS operating system interrupt handler (`INT 21h`) is hardcoded to look **exclusively at the `AH` register** to determine exactly what action or service you are requesting. 

* **`AH = 01h`** -> DOS knows you want to *read* a character from the keyboard.
* **`AH = 02h`** -> DOS knows you want to *print* a single character to the screen.
* **`AH = 09h`** -> DOS knows you want to *print* an entire string of text.

> ⚠️ **Critical Risk:** If you forget to load the correct function number into `AH`, the CPU will still execute the interrupt (`INT 21h`), but DOS will perform whatever random, unpredictable operation happens to match the leftover junk value in `AH`—frequently causing program crashes or memory corruption.

---

## Syntax for Printing

There are two primary sub-services used to output data to the terminal screen:

### 1. Printing a Single Character (Function `02h`)
To output one standalone character, tell DOS your intent via `AH = 02h`, drop the character's ASCII value into the 8-bit `DL` data register, and invoke the execution switch.

```assembly
mov ah, 02h     ; Step 1: Select the "Print Character" department
mov dl, 'A'     ; Step 2: Provide payload data (ASCII 'A' / 41h)
int 21h         ; Step 3: Execute the DOS system interrupt
```

---

### 2. Printing a String of Text (Function `09h`)
To output a string of text, tell DOS your intent via `AH = 09h`, drop the memory address of the string into the 16-bit `DX` data register, and invoke an execution switch. The string must be terminated with a **dollar sign (`$`)** to signal the end of the text.

```assembly
mov ah, 09h     ; Step 1: Select the "Print String" department
mov dx, offset myString ; Step 2: Provide payload data (address of the string)
int 21h         ; Step 3: Execute the DOS system interrupt  
```

---

### 3. Taking Input from the User (Function `01h`)

To read a single character from the keyboard, tell DOS your intent via `AH = 01h` and trigger the execution switch. DOS will pause, wait for a keypress, echo that character to the screen, and save its ASCII value directly into the 8-bit `AL` register.

```assembly
mov ah, 01h     ; Step 1: Select the "Read Character with Echo" department
int 21h         ; Step 2: Execute the DOS system interrupt (waits for keypress)
; After int 21h executes, the ASCII value of the pressed key is now sitting in AL.

; Optional next step: Move it somewhere safe before AL gets overwritten
mov dl, al      ; Move the inputted character into DL (e.g., if you want to print it next)
```

---

### 4. Basic Variables and Memory Allocation

In 8086 assembly, you can define variables and allocate memory in the data segment. Here's a simple example of how to declare a string variable and use it for printing:

```assembly
.data
myString db 'Hello, World!$' ; Define a string variable with a dollar sign terminator

a db 10 ; Define a byte variable 'a' with initial value 10
b db 20 ; Define a byte variable 'b' with initial value 20

.code
mov ah, 09h     ; Select the "Print String" department
mov dx, offset myString ; Load the address of the string
int 21h         ; Execute the DOS system interrupt

; trying to sum, sub, mult, div

mov al, a       ; Load the value of 'a' into AL
add al, b       ; Add the value of 'b' to AL (AL = a + b)

mov ah, 02h     ; Prepare to print the result
mov dl, al      ; Move the result into DL for printing
int 21h         ; Print the result character

mov al, a       ; Load the value of 'a' into AL
sub al, b       ; Subtract the value of 'b' from AL (AL = a - b)

mov ah, 02h     ; Prepare to print the result
mov dl, al      ; Move the result into DL for printing
int 21h         ; Print the result character

; now multiplication

mov al, a       ; Load the value of 'a' into AL
mov bl, b       ; Load the value of 'b' into BL
mul bl          ; Multiply AL by BL (AX = a * b)
mov ah, 02h     ; Prepare to print the result
mov dl, al      ; Move the result into DL for printing
int 21h         ; Print the result character

; now division

mov al, a       ; Load the value of 'a' into AL
mov bl, b       ; Load the value of 'b' into BL
div bl          ; Divide AL by BL (AL = a / b, AH = a % b)
mov ah, 02h     ; Prepare to print the result
mov dl, al      ; Move the result into DL for printing
int 21h         ; Print the result character
```

---

### 5. Handling Characters (Upper/Lower Case, etc.)

In ASCII, uppercase and lowercase letters differ by exactly 32 (20h):

| Character | ASCII (Hex) | Character | ASCII (Hex) |
|-----------|-------------|-----------|-------------|
| `A`       | 41h         | `a`       | 61h         |
| `B`       | 42h         | `b`       | 62h         |
| ...       | ...         | ...       | ...         |
| `Z`       | 5Ah         | `z`       | 7Ah         |

**Uppercase to lowercase:** Add 32 (20h)
```assembly
mov al, 'A'     ; AL = 41h
add al, 20h     ; AL = 61h = 'a'
mov dl, al
mov ah, 02h
int 21h         ; Prints 'a'
```

**Lowercase to uppercase:** Subtract 32 (20h)
```assembly
mov al, 'b'     ; AL = 62h
sub al, 20h     ; AL = 42h = 'B'
mov dl, al
mov ah, 02h
int 21h         ; Prints 'B'
```

**Check if a character is uppercase:**
```assembly
mov al, 'X'
cmp al, 'A'     ; Is it below 'A'?
jb  notUpper
cmp al, 'Z'     ; Is it above 'Z'?
ja  notUpper
; It is uppercase
jmp done
notUpper:
; It is not uppercase
done:
```

**Check if a character is lowercase:**
```assembly
mov al, 'x'
cmp al, 'a'     ; Is it below 'a'?
jb  notLower
cmp al, 'z'     ; Is it above 'z'?
ja  notLower
; It is lowercase
notLower:
```

**Convert any letter to uppercase (if it's lowercase):**
```assembly
mov al, 'g'
cmp al, 'a'
jb  skip
cmp al, 'z'
ja  skip
sub al, 20h     ; Convert to uppercase
skip:
mov dl, al
mov ah, 02h
int 21h         ; Prints 'G'
```

---

### 6. Handling Strings and Arrays

**Defining strings and arrays in the data segment:**

```assembly
.data
; Strings (null-terminated or $-terminated)
str1 db 'Hello$'                    ; $-terminated string
str2 db 'World', 0                  ; null-terminated string

; Arrays of bytes
arr1 db 10, 20, 30, 40, 50         ; array of 5 bytes
arr2 db 5 dup(0)                    ; array of 5 zeros
arr3 db 3 dup('A')                  ; 'A', 'A', 'A'

; Arrays of words (16-bit)
wordArr dw 100, 200, 300, 400
```

**Calculating string length (with null terminator):**
```assembly
.data
myStr db 'Hello, World!', 0

.code
mov si, offset myStr   ; SI points to start of string
xor cx, cx             ; CX = 0 (counter)

countLoop:
mov al, [si]           ; Load current character
cmp al, 0              ; Is it null terminator?
je  countDone
inc cx                 ; Increment counter
inc si                 ; Move to next character
jmp countLoop

countDone:
; CX now holds the string length (13)
```

**Copying a string:**
```assembly
.data
source db 'Hello$'
dest   db 20 dup('$')  ; destination buffer

.code
mov si, offset source  ; source pointer
mov di, offset dest    ; destination pointer

copyLoop:
mov al, [si]           ; Read from source
mov [di], al           ; Write to destination
cmp al, '$'            ; Check for terminator
je  copyDone
inc si
inc di
jmp copyLoop

copyDone:
```

**Iterating through an array of numbers:**
```assembly
.data
numbers db 10, 20, 30, 40, 50
count   equ 5          ; Equivalent to: count = 5

.code
mov si, offset numbers
mov cx, count          ; Loop counter

loopStart:
mov al, [si]           ; Get current element

; ... do something with al ...

inc si                 ; Move to next element
dec cx                 ; Decrement counter
jnz loopStart          ; Repeat if not zero
```

---

### 7. Loops

The `CX` register is the conventional loop counter. The `LOOP` instruction decrements `CX` and jumps if `CX != 0`.

**Basic loop using LOOP:**
```assembly
mov cx, 5              ; Repeat 5 times
mov dl, 'A'

printLoop:
mov ah, 02h
int 21h                ; Print current character
inc dl                 ; Next character
loop printLoop         ; Decrement CX, jump if not zero
; Prints: ABCDE
```

**Loop with the LOOP instruction (must use CX):**
```assembly
mov cx, 10
mov al, 0

sumLoop:
add al, cx             ; Add current CX value to AL
loop sumLoop
; After loop: AL = 10+9+8+...+1 = 55 (decimal)
```

**Loop using manual decrement and jump:**
```assembly
mov cx, 5
myLoop:
; ... loop body ...
dec cx
jnz myLoop             ; Jump if CX is not zero
```

**Infinite loop (use with caution):**
```assembly
forever:
; ... loop body ...
jmp forever
```

**Nested loops (save outer counter on stack):**
```assembly
mov cx, 3              ; Outer loop count

outer:
push cx                ; Save outer counter
mov cx, 4              ; Inner loop count

inner:
; ... inner loop body ...
loop inner

pop cx                 ; Restore outer counter
loop outer
```

**Looping through memory with different addressing modes:**
```assembly
.data
array db 1, 2, 3, 4, 5
len   equ 5

.code
mov si, 0              ; Index
mov cx, len

process:
mov al, array[si]      ; Access array[si]
add al, 2              ; Modify value
mov array[si], al      ; Store back
inc si
loop process
; Array is now: 3, 4, 5, 6, 7
```

---

### 8. If/Else and Other Branching

Conditional branching in 8086 uses `CMP` followed by a conditional jump instruction.

**The CMP instruction:**
```assembly
cmp al, bl             ; Compare AL with BL (sets flags as if subtracting)
; Flags affected: Zero (ZF), Carry (CF), Sign (SF), Overflow (OF)
```

**Common conditional jump instructions:**

| Instruction | Jumps When...         | Condition          |
|-------------|----------------------|--------------------|
| `JE` / `JZ` | Equal / Zero         | ZF = 1             |
| `JNE` / `JNZ`| Not Equal / Not Zero | ZF = 0             |
| `JG` / `JNLE`| Greater (signed)    | ZF=0 and SF=OF     |
| `JL` / `JNGE`| Less (signed)       | SF != OF           |
| `JGE` / `JNL`| Greater or Equal    | SF = OF            |
| `JLE` / `JNG`| Less or Equal       | ZF=1 or SF != OF   |
| `JA` / `JNBE`| Above (unsigned)    | CF=0 and ZF=0      |
| `JB` / `JNAE`| Below (unsigned)    | CF = 1             |
| `JAE` / `JNB`| Above or Equal      | CF = 0             |
| `JBE` / `JNA`| Below or Equal      | CF=1 or ZF=1       |
| `JC`         | Carry               | CF = 1             |
| `JNC`        | No Carry            | CF = 0             |

**If/else pattern:**
```assembly
mov al, 42
cmp al, 50
jge elseBranch         ; Jump to else if AL >= 50

; If branch (AL < 50)
mov dl, '<'
jmp done

elseBranch:
; Else branch (AL >= 50)
mov dl, '>='

done:
mov ah, 02h
int 21h                ; Print the character
```

**If/else if/else pattern:**
```assembly
mov al, someValue
cmp al, 10
jl  caseSmall          ; Jump if AL < 10
cmp al, 20
jg  caseLarge          ; Jump if AL > 20

; Middle case (10 <= AL <= 20)
mov dl, 'M'
jmp done

caseSmall:
mov dl, 'S'
jmp done

caseLarge:
mov dl, 'L'

done:
mov ah, 02h
int 21h
```

**Comparing characters:**
```assembly
mov ah, 01h
int 21h                ; Read a character from user (stored in AL)

cmp al, 'Y'
je  yesBranch
cmp al, 'y'
je  yesBranch
cmp al, 'N'
je  noBranch
cmp al, 'n'
je  noBranch

; Invalid input
mov dl, '?'
jmp printResult

yesBranch:
mov dl, '1'
jmp printResult

noBranch:
mov dl, '0'

printResult:
mov ah, 02h
int 21h
```

**Select/case pattern using jump table:**
```assembly
.data
jumpTable dw case0, case1, case2, case3  ; Addresses of each case

.code
mov al, 2              ; Select case 2
cbw                    ; Convert AL to 16-bit (AX)
shl ax, 1              ; Multiply by 2 (each address is 2 bytes)
mov si, ax
jmp [jumpTable + si]   ; Jump to the selected handler

case0:
; Handle case 0
jmp endCase

case1:
; Handle case 1
jmp endCase

case2:
; Handle case 2 (this one runs)
jmp endCase

case3:
; Handle case 3

endCase:
```

---

### 9. Complete Example: Combining Everything

```assembly
; A complete program that reads a character, converts case, 
; prints it back, and counts loop iterations

.model small
.stack 100h

.data
prompt  db 'Enter a letter: $'
upperMsg db 10, 13, 'Uppercase: $'
lowerMsg db 10, 13, 'Lowercase: $'
countMsg db 10, 13, 'Loop count: $'

.code
main proc
    mov ax, @data
    mov ds, ax

    ; Print prompt
    mov ah, 09h
    mov dx, offset prompt
    int 21h

    ; Read character
    mov ah, 01h
    int 21h
    mov bl, al         ; Save it in BL

    ; Check if uppercase
    cmp al, 'A'
    jb  checkLower
    cmp al, 'Z'
    ja  checkLower

    ; It's uppercase - print uppercase message and convert to lowercase
    mov ah, 09h
    mov dx, offset upperMsg
    int 21h

    mov dl, bl
    mov ah, 02h
    int 21h

    add bl, 20h        ; Convert to lowercase
    jmp printConverted

checkLower:
    cmp al, 'a'
    jb  notLetter
    cmp al, 'z'
    ja  notLetter

    ; It's lowercase - print lowercase message and convert to uppercase
    mov ah, 09h
    mov dx, offset lowerMsg
    int 21h

    mov dl, bl
    mov ah, 02h
    int 21h

    sub bl, 20h        ; Convert to uppercase

printConverted:
    mov dx, offset countMsg
    mov ah, 09h
    int 21h

    ; Print the converted character in a loop, with a counter
    mov cx, 5          ; Loop 5 times
    mov al, bl         ; Start from converted character

loopPrint:
    mov dl, al
    mov ah, 02h
    int 21h
    inc al
    loop loopPrint

    jmp done

notLetter:
    mov dl, '?'
    mov ah, 02h
    int 21h

done:
    mov ah, 4Ch        ; Exit program
    int 21h
main endp
end main
```

---

### 10. More topics will be added later
