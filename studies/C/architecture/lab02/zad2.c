#include <stdio.h>

int main(){

	int x=0xFF00FF00;
	int y;

	asm (
	".intel_syntax noprefix;"
	"mov eax, %1;"
	"mov ecx, 0;"
	"petla:"
	"shl eax;"
	"jnc skok;"
	"inc ecx;"
	"skok:"
	"sub eax, 0;"
	"jnz petla;"
	"mov %0,ecx;"
	".att_syntax prefix;"
	:"=r"(y)
	:"r"(x)
	:"eax","ecx"
	);
	printf("Wynik: %i\n", y);
	return 0;
}
