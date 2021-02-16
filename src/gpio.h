#ifndef GPIO_H_INCLUDE
#define GPIO_H_INCLUDE
#include <linux/gpio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
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
int setupParallelOut(unsigned int count, ...);  //No. of pins. return parallel fd
int setupParallelIn(unsigned int count, ...);   //No. of pins. return parallel fd
int digitalWrite(int pin, int value);
int digitalRead(int pin);
int ParallelWrite(int paranum, unsigned char *value);
unsigned char *ParallelRead(int paranum);
void GPIOclose(void);
#ifdef __cplusplus
}
#endif
#endif