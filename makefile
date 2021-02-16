install:
	gcc -shared -fPIC src/wiringDev.cpp -o src/libwiringDev.so
	sudo cp src/wiringDev.h /usr/include/wiringDev.h
	sudo cp src/libwiringDev.so /usr/lib/libwiringDev.so
blink:
	gcc example/blink.c -o example/blink.o -lwiringDev
blink2:
	gcc example/blink2.c -o example/blink2.o -lwiringDev