kernel.bin: main.o boot.o
	ld -m elf_i386 -T linker.ld -o kernel.bin boot.o main.o

boot.o: boot.s
	as -o boot.o boot.s -32

main.o: main.c multiboot.h
	gcc -m32 -Wall -fno-builtin -nostdlib -nostdinc -o main.o -c  main.c # -m32 Потрібно тільки на 64 бітних системах
