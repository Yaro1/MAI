.PHONY: construct
construct:
	nasm -f elf -dOS_LINUX strlen.asm
	nasm -f elf -dOS_LINUX putstr.asm
	nasm -f elf -dOS_LINUX getstr.asm
	nasm -f elf -dOS_LINUX quit.asm
	nasm -f elf -dOS_LINUX greet.asm
	ar crs libgreet.a strlen.o getstr.o putstr.o quit.o
	ld -m elf_i386 greet.o libgreet.a -o greet
	rm *.o
