%include "syscall.inc"
global quit
section .text
quit: syscall 1, 0
