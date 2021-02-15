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

#define INPUT GPIOHANDLE_REQUEST_INPUT
// #define INPUT_PULLUP
// #define INPUT_PULLDOWN
#define OUTPUT GPIOHANDLE_REQUEST_OUTPUT
#define HIGH 1
#define LOW 0

#ifdef __cplusplus
extern "C" {
#endif
int gpioSetup(char *device);
int pinMode(int pin, unsigned int mode);
int setupParallel(unsigned int count, unsigned int mode, int pin, ...);  //No. of pins. return parallel fd
int digitalWrite(int pin, int value);
int digitalRead(int pin);
int ParallelWrite(int fd, unsigned char *value);
unsigned char ParallelRead(int fd);
#ifdef __cplusplus
}
#endif
#endif