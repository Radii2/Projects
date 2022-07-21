#include <stdio.h>

int main(){

	int x=2021;
	int y;


	asm (
	".intel_syntax noprefix;"
	"mov eax,%1;"
	"add eax,eax; "
	"mov %0,eax;"
	".att_syntax prefix;"
	:"=r"(y)
	:"r"(x)
	:"eax"
	);
	printf("Wynik: %i\n", y);
	return 0;
}
