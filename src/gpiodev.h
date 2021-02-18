#ifndef GPIODEV_H_INCLUDE
#define GPIODEV_H_INCLUDE
#include <linux/gpio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define INPUT 0
// #define INPUT_PULLUP
// #define INPUT_PULLDOWN
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define BOTH 2
#define RISING 1
#define FALLING 0

typedef struct {
  unsigned long long timestamp;
  unsigned int id;
} event;

class gpio {
 public:
  gpio(const char *device);
  int gpioSetup();
  int pinMode(int pin, unsigned int mode);
  int setupParallelOut(unsigned int count, ...);  //No. of pins. return parallel fd
  int setupParallelIn(unsigned int count, ...);   //No. of pins. return parallel fd
  int setEvent(int pin, int mode);
  int digitalWrite(int pin, int value);
  int digitalRead(int pin);
  int ParallelWrite(int para_num, unsigned char *value);
  int ParallelRead(int para_num, unsigned char *value);
  int getEvent(int event_num, event *data);
  int CloseSpecialIO(int num);
  int Closedev(void);

 private:
  int fd;
  int *fd_pin;
  char *device;
  struct gpiochip_info cinfo;
  struct gpioline_info linfo;
  struct gpiohandle_data data;
};
#endif