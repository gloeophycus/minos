ifndef DOCKER
all rebuild bootloader_ library_ kernel_ disk.img clean:
	docker run -it --rm -v "$(CURDIR):/src" -w /src -e DOCKER=1 dev make $@
else
all: disk.img

rebuild: clean all

bootloader_:
	make -C bootloader

library_:
	make -C library

kernel_:
	make -C kernel

disk.img: bootloader_ library_ kernel_
	cp bootloader/ipl.bin $@
	dd if=/dev/zero bs=1 count=$$((0x4200 - 0x200)) 2>/dev/null >> $@
	cat kernel/entrypoint.bin >> $@
	cat kernel/main.bin >> $@
	truncate -s $$((0x168000)) $@

clean:
	make -C bootloader clean
	make -C kernel clean
	make -C library clean
	rm -rf disk.img
endif

run: disk.img
	cp disk.img /mnt/c/os
	cmd.exe /c "cd /d C:/Program Files (x86)/qemu && qemu-x86_64.bat"