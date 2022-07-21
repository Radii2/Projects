#include <stdio.h>

int main(){

        int x=30448;
        int y;

        asm (
        	".intel_syntax noprefix;"
        	"mov eax, %1;"
        	"mov ebx, 16;"
        	"xor ecx, ecx;"
		"xor edx, edx;"
        "petla:"
		"cmp ebx, 0;"
		"je wynik;"
		"dec ebx;"
        	"shr eax, 1;"
		"jnc sprawdzanie;"
		"inc ecx;"
		"jmp petla;"
	"sprawdzanie:"
		"cmp edx, ecx;"
		"jl zamiana;"
		"xor ecx, ecx;"
		"jmp petla;"
	"zamiana:"
		"xor edx, edx;"
		"mov edx, ecx;"
		"xor ecx, ecx;"
		"jmp petla;"
	"wynik:"
        	"mov %0, edx;"
        	".att_syntax prefix;"
        	:"=r"(y)
        	:"r"(x)
        	:"eax","ebx","ecx","edx"
        );
        printf("Liczba: %i\nNajwieksza ilosc jedynek: %i\n", x,y);
        return 0;
}

