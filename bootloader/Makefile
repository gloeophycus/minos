all: ipl.bin

%.o: %.s
	as -o $@ $< 

ipl.bin: ipl.o
	ld -N -e _start -Ttext 0x7C00 -S --oformat binary -o $@ $<

clean:
	rm -f *.o
	rm -f *.bin
