.PHONY: construct
construct:
	nasm -f elf -dOS_LINUX prog.asm
	ld -m elf_i386 prog.o  -o prog
.PHONY: clean
clean:
	rm *.o
