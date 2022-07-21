#include<stdio.h>

int main(){
	char x[] = "Abcdexyz";

	asm (
		".intel_syntax noprefix;"
		"mov rbx, %0;"
		"petla:"
			"mov al, [rbx];"
			"cmp al, 0;"
			"jz odwrocenie;"
			"inc rbx;"
			"jmp petla;"
		"odwrocenie:"
			"dec rbx;"
			"mov rdx, %0;"
		"zamien:"
			"cmp rdx, rbx;"
			"jae koniec;"
			"mov al, [rbx];"
			"mov cl, [rdx];"
			"mov [rbx],cl;"
			"mov [rdx],al;"
			"dec rbx;"
			"inc rdx;"
			"jmp zamien;"
		"koniec:"
		".att_syntax prefix;"
		:
		:"r" (x)
		:"rbx", "rdx", "cl", "al"
	);
	printf("%s\n", x);
	return 0;
}
