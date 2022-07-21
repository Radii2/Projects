# Ciąg Fibonacciego, algorytm rekurencyjny, wersja 32-bitowa; kompilować: gcc -m32 fib.s
    .intel_syntax noprefix
    .global main
    .text
main:
    mov eax, 10
    push eax
    call fib
    add esp, 4
    ret
fib:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov eax, [ebp+8]
    cmp eax, 2
    ja czesc_rekurencyjna
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
czesc_rekurencyjna:
    dec eax
    push eax
    call fib
    add esp, 4
    mov [ebp-4], eax
    mov eax, [ebp+8]
    dec eax
    dec eax
    push eax
    call fib
    add esp, 4
    add eax, [ebp-4]
    mov esp, ebp
    pop ebp
    ret
    .data
msg:    .asciz "FIB(n)=%i\n"
