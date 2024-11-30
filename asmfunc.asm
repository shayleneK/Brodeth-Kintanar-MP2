section .text
bits 64
default rel
global kernel_asm

kernel_asm:
    mov rax, rcx            ; Load n (number of elements) into rax
    mov rsi, rdx            ; Pointer to X
    mov rdx, r8             ; Pointer to Y
    mov rcx, r9             ; Pointer to Z
    movsd xmm4, xmm0        ; Load A (in xmm0) into xmm4

loop_start:
    cmp rax, 0              ; Check if n == 0
    je loop_end             ; If no more elements, exit loop

    movsd xmm1, [rsi]       ; Load X[i] into xmm1
    movsd xmm2, [rdx]       ; Load Y[i] into xmm2
    mulsd xmm1, xmm4        ; Compute X[i] * A
    addsd xmm1, xmm2        ; Compute (X[i] * A) + Y[i]
    movsd [rcx], xmm1       ; Store result into Z[i]

    add rsi, 8              ; Increment X pointer (sizeof(double) = 8 bytes)
    add rdx, 8              ; Increment Y pointer
    add rcx, 8              ; Increment Z pointer

    dec rax                 ; Decrement n
    jmp loop_start          ; Repeat loop

loop_end:
    ret

