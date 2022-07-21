#include <stdio.h>

int main(){

        int x=2021;
        int y;

        asm (
        ".intel_syntax noprefix;"
        "mov eax, %1;"
        "mov ebx, 20;"
        "mov ecx, 0;"
        "petla:"
        "add ecx, eax;"
	"sub ebx, 1;"
        "jnz petla;"
        "mov %0,ecx;"
        ".att_syntax prefix;"
        :"=r"(y)
        :"r"(x)
        :"eax","ebx","ecx"
        );
        printf("Wynik: %i\n", y);
        return 0;
}

