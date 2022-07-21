//gcc -masm=intel a.c
#include<stdio.h>

int main(){
    double x = 1.0;
    double y;

    asm (
        "finit;"
        "fld %1;"
        "fld1;"
        "fld1;"
        "fld1;"
        "mov eax, 10;"
    "petla:"
        "fmul st(3);"
        "fdiv st(2);"
        "fadd st(1),st(0);"
        "fld1;"
        "faddp st(3), st(0);"
        "dec eax;"
        "jnz petla;"
        "fxch st(1);"
        "fstp %0;"
        :"=m" (y)
        :"m" (x)
        : "eax"
    );
    printf("Wynik: %f\n", y);
    return 0;
}