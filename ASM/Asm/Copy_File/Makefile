.PHONY: construct
construct:
	nasm -f elf -d OS_LINUX -d COPY prog.asm
	ld -m elf_i386 prog.o  -o prog
.PHONY: clean
clean:
	rm *.o
