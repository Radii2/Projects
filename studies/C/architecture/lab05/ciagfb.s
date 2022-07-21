# Ciąg Fibonacciego, algorytm rekurencyjny, wersja 32-bitowa; kompilować: gcc -m32 fib.s
    .intel_syntax noprefix
    .global main
    .text
main:
    mov eax, [esp+8]
    mov eax, [eax+4]
    push eax
    call atoi
    add esp, 4
    # W tym momencie ATOI w rejestrze EAX zwróciło wartość typu INT odpowiadającą argumentowi wywołania programu
    push eax
    call fib
    add esp, 4
    # W tym momencie w EAX jest wynik funkcji FIB
    # Zawołaj "printf"
    push eax
    mov ebx, offset msg
    push ebx
    call printf
    add esp, 8
    # Zwróć "0" do systemu operacyjnego
    mov eax, 0
    # Powrót do biblioteki standardowej
    ret
fib:
    sub esp, 4 ;# zmienna lokalna TMP
    mov ebx, [esp+8]
    cmp ebx, 2
    ja czesc_rekurencyjna
    mov eax, 1
    add esp, 4 ;# usunięcie zmiennej TMP ze stosu
    ret
czesc_rekurencyjna:
    dec ebx
    push ebx
    call fib
    add esp, 4
    # Przechowujemy pośredni wynik FIB(n-1) w TMP
    mov [esp], eax
    mov ebx, [esp+8]
    dec ebx
    dec ebx
    push ebx
    call fib
    add esp, 4
    # W tym momencie EAX zawiera FIB(n-2), TMP zawiera FIB(n-1)
    add eax, [esp]
    add esp, 4 ;# usunięcie zmiennej TMP ze stosu
    ret
    .data
msg:    .asciz "FIB(n)=%i\n"
# // Odpowiednik w języku C:
# int main() {
#    printf("Hello, world\n");
#    return 0;
# }
