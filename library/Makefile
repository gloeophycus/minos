all: libc.a

libc.a: $(patsubst source/%.c, temp/%.o, $(wildcard source/*.c))
	ar rcs libc.a $^

temp/%.o: source/%.c
	gcc -std=c99 -fno-pic -fno-builtin -O2 -Wall -Wextra -Werror -I./include -c -o $@ $<

clean:
	rm -f temp/*.*
	rm -f libc.a