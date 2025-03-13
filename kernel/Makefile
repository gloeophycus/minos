all: entrypoint.bin main.bin

temp/%.o: source/%.s
	as -o $@ $< 

temp/%.o: source/%.c
	gcc -std=c99 -fno-pic -O2 -Wall -Wextra -Werror -I../library/include -c -o $@ $<

entrypoint.bin: temp/entrypoint.o
	ld -N -e _start -Ttext 0xC200 -S --oformat binary -o $@ $<

main.bin: temp/main.o temp/assembly_functions.o temp/queue.o temp/fonts.o temp/graphics.o temp/descriptors.o temp/interrupts.o temp/memory.o
	ld -T kernel.ld --oformat binary -o $@ $^ ../library/libc.a

clean:
	rm -f temp/*.*
	rm -f *.bin
