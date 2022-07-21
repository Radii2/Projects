        .intel_syntax noprefix
        .global main
        .text
main:
        mov ebx, [esp + 8]
        mov ecx, [ebx + 4]
        push ecx
        call atoi
        add esp, 4
        add eax, eax
        ret
