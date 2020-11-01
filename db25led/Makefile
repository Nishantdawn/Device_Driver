
obj-m += db25led.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cc read.c -o read
	cc write.c -o write
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm read write
