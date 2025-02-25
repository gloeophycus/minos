all: entrypoint.bin main.bin

temp/%.o: source/%.s
	as -o $@ $< 

temp/%.o: source/%.c
	gcc -std=c99 -fno-pic -O2 -c -o $@ $<

entrypoint.bin: temp/entrypoint.o
	ld -N -e _start -Ttext 0xC200 -S --oformat binary -o $@ $<

main.bin: temp/main.o temp/assembly_functions.o
	ld -T kernel.ld --oformat binary -o $@ $^

clean:
	rm -f temp/*.*
	rm -f *.bin
