OUT = kernel.bin

kernel.bin: main.o boot.o asm_func.o
	ld -m elf_i386 -T linker.ld -o $(OUT) boot.o asm_func.o main.o

boot.o: boot.s
	as -o boot.o boot.s -32

asm_func.o: asm_func.c asm.h
	gcc -m32 -c asm_func.c
main.o: main.c multiboot.h
	gcc -m32 -Wall -fno-builtin -nostdlib -nostdinc -o main.o -c  main.c # -m32 Потрібно тільки на 64 бітних системах
