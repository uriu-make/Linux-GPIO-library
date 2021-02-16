install:
	gcc -shared -fPIC src/gpio.c -o src/libgpio.so
	sudo cp src/gpio.h /usr/include/gpio.h
	sudo cp src/libgpio.so /usr/lib/libgpio.so
blink:
	gcc example/blink.c -o example/blink.o -lgpio