.PHONY: construct
construct:
	nasm -f elf prog.asm
	ld -m elf_i386 prog.o  -o prog
.PHONY: clean
clean:
	rm *.o
