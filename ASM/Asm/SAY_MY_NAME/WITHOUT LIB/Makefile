.PHONY: construct
construct:
	nasm -f elf -dOS_LINUX strlen.asm
	nasm -f elf -dOS_LINUX putstr.asm
	nasm -f elf -dOS_LINUX getstr.asm
	nasm -f elf -dOS_LINUX quit.asm
	nasm -f elf -dOS_LINUX greet.asm
	ld -m elf_i386 strlen.o putstr.o getstr.o quit.o greet.o -o greet
.PHONY: clean
clean:
	rm *.o
