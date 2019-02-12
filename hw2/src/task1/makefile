.PHONY: clean all

all: setup stack exploit call_shellcode

clean:
	rm stack exploit call_shellcode

setup:
	sudo sysctl -w kernel.randomize_va_space=0

exploit: exploit.c
	# No special flags for the exploit, this will produce the badfile
	# that contains assembly that will replace the stack pointer
	# with the memory address of our buffer and load it with our
	# assembly code that will call /bin/sh
	gcc -o exploit exploit.c

stack: stack.c
	sudo gcc -o stack -fno-stack-protector -z execstack stack.c
	sudo chmod 4755 stack      # Add the exec bit to the executable 

call_shellcode: call_shellcode.c
	sudo gcc -o call_shellcode -fno-stack-protector -z execstack call_shellcode.c
