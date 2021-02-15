#ifndef GPIO_H_INCLUDE
#define GPIO_H_INCLUDE
#include <linux/gpio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int gpioSetup(char *device);
int pinMode(int pin, int mode);
int setupParallel(int No_pins, int mode, int pin, ...);  //No. of pins. return parallel fd
int digitalWrite(int pin, int value);
int digitalRead(int pin);
int ParallelWrite(int fd, char *value);
int ParallelRead(int fd);
#endif