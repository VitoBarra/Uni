file :=esa2
port := 30030

.PHONY: deb


% : %.exe
	arm-linux-gnueabihf-gcc -o $@ $@.s -static -ggdb3

deb:
	arm-linux-gnueabihf-gcc -o $(file) $(file).s -static -ggdb3
	qemu-arm -g $(port) $(file) &.
	gdb-multiarch -q --nh -ex "set architecture arm" -ex "file $(file)" -ex "target remote localhost:$(port)"

