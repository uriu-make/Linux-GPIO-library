#include "gpio.h"

int gpioSetup(char *device){}
int pinMode(int pin, int mode){}
int setupParallel(int num, int mode, int pin, ...){}
int digitalWrite(int pin, int value){}
int digitalRead(int pin){}
int ParallelWrite(int fd, char *value){}
int ParallelRead(int fd){}