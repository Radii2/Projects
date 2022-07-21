#include <stdio.h>

int main(){

	int x=0xFF00FF00;
	int y;

	asm (
	".intel_syntax noprefix;"
	"mov eax, %1;"
	//"mov ecx, 0;"
	"xor ecx, ecx;"
    "petla:"
	"shl eax;"
	"jnc skok;"
	"inc ecx;"
	"skok:"
	"and eax, eax;"
    //"or eax, eax;"
	"jnz petla;"
	"mov %0,ecx;"
	".att_syntax prefix;"
	:"=r"(y)
	:"r"(x)
	:"eax","ecx"
    //porownywanie, sprawdzanie znaku
    //cmp eax,edx;
    //
    //sub eax, edx;
    //js; 
	);
	printf("Wynik: %i\n", y);
	return 0;
}
