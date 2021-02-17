install:
	gcc -shared -fPIC src/gpiodev.cpp -o src/libgpiodev.so
	sudo cp src/gpiodev.h /usr/include/gpiodev.h
	sudo cp src/libgpiodev.so /usr/lib/libgpiodev.so
blink:
	gcc example/blink.cpp -o example/blink.o -lgpiodev
paralleltest:
	gcc example/paralleltest.cpp -o example/paralleltest.o -lgpiodev
all: install blink blink2 paralleltest
examples: blink paralleltest