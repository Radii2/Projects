# TMP1: ebp -4 (n-1)
# TMP2: ebp -8 (n-2)
# N=3: ebp + 8

	.intel_syntax noprefix
	.global main
	.text
main:
		mov eax, 10
		push eax
		call fib
		add esp, 4
		ret
fib:
		push ebp
		mov ebp, esp
		sub esp, 8
		mov eax, [ebp+8]
		cmp eax, 3
		ja rekurencja
		mov eax, 1
		mov esp, ebp
		pop ebp
		ret
rekurencja:
		dec eax
		push eax
		call fib
		add esp, 4
		mov [ebp-4], eax
		mov eax, [ebp+8]
		dec eax
		dec eax
		push eax
		call fib
		add esp, 4
		mov [ebp-8], eax
		mov eax, [ebp+8]
		dec eax
		dec eax
		dec eax
		push eax
		call fib
		add esp, 4
		add eax, [ebp-4]
		mov ebx, [ebp-8]
		add [ebp-8], ebx
		add eax, [ebp-8]
		mov esp, ebp
		pop ebp
		ret
	.data
