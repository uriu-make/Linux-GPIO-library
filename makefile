install:
	gcc -shared -fPIC src/wiringDev.cpp -o src/libwiringDev.so
	sudo cp src/wiringDev.h /usr/include/wiringDev.h
	sudo cp src/libwiringDev.so /usr/lib/libwiringDev.so
blink:
	gcc example/blink.cpp -o example/blink.o -lwiringDev
blink2:
	gcc example/blink2.cpp -o example/blink2.o -lwiringDev
paralleltest:
	gcc example/paralleltest.cpp -o example/paralleltest.o -lwiringDev
all: install blink blink2 paralleltest