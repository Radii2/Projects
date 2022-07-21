#include <stdio.h>

int main(){

	int x=0xFF00FF00;
	int y;

	asm (
	".intel_syntax noprefix;"
	"mov eax, %1;"
	"mov ebx, 32;"
	"mov ecx, 0;"
	"petla:"
	"shl eax;"
	"jnc skok;"
	"add ecx, 1;"
	"skok:"
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
