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
    mov eax, [esp+4]
    cmp eax, 2
    ja czesc_rekurencyjna
    mov eax, 1
    ret
czesc_rekurencyjna:
    dec eax
    push eax
    call fib
    add esp, 4
    # Przechowujemy pośredni wynik FIB(n-1) w TMP
    push eax
    mov eax, [esp+8]
    dec eax
    dec eax
    push eax
    call fib
    add esp, 4
    # W tym momencie EAX zawiera FIB(n-2), TMP zawiera FIB(n-1)
    pop ebx
    add eax, ebx
    ret
    .data
msg:    .asciz "FIB(n)=%i\n"
