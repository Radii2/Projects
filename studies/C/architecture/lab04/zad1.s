        .intel_syntax noprefix
        .global main
        .text
main:
        mov ebx, [esp + 4]
        dec ebx
        mov eax, ebx
        ret
