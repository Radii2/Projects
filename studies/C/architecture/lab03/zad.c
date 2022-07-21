#include <stdio.h>

int main(){
	char x[] = "Abc";
	
	asm (
		".intel_syntax noprefix;"
		"mov rbx, %0;"
		"xor al, al;"
		"petla:"
			"mov al, [rbx];"
			"cmp al, 0;"
			"jz koniec;"
			"inc al;"
			"mov [rbx], al;"
			"inc rbx;"
			"jmp petla;"
		"koniec:"
		".att_syntax prefix;"
		:
		:"r" (x)
		:"rbx", "al"
	);
	printf("Wynik: %s\n", x);
	return 0;
}
