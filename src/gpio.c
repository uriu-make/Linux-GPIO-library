#include "gpio.h"
int fd;
int *fd_pin;
struct gpiochip_info cinfo;
struct gpioline_info linfo;
struct gpiohandle_request parallel;
struct gpiohandle_data data;

int gpioSetup(char *device) {
  int fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  fd_pin = (int *)calloc(cinfo.lines, sizeof(int));
  return fd;
}

int pinMode(int pin, unsigned int mode) {
  struct gpiohandle_request req;
  req.lineoffsets[0] = pin;
  req.lines = 1;
  req.flags = mode;
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
  return fd_pin[pin] = req.fd;
}

int setupParallelOut(unsigned int count, ...) {
  va_list ap;
  va_start(ap, count);
  parallel.flags = OUTPUT;
  parallel.lines = count;
  for (int i = 0; i < count; i++) {
    parallel.lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &parallel);
  return parallel.fd;
}

int setupParallelIn(unsigned int count, ...) {
  va_list ap;
  va_start(ap, count);
  parallel.flags = INPUT;
  parallel.lines = count;
  for (int i = 0; i < count; i++) {
    parallel.lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &parallel);
  return parallel.fd;
}

int digitalWrite(int pin, int value) {
  memset(data.values, 0, sizeof(data.values));
  data.values[0] = value;
  return ioctl(fd_pin[pin], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

int digitalRead(int pin) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(fd_pin[pin], GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return (int)data.values;
}

int ParallelWrite(int fd_para, unsigned char *value) {
  parallel.fd = fd;
  memset(data.values, 0, sizeof(data.values));
  for (int i = 0; i < sizeof(value); i++)
    data.values[i] = value[i];
  ioctl(fd_para, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

unsigned char *ParallelRead(int fd_para) {
  parallel.fd = fd;
  memset(data.values, 0, sizeof(data.values));
  ioctl(fd_para, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return data.values;
<<<<<<< HEAD
}

void GPIOclose(void) {
  free(fd_pin);
=======
>>>>>>> parent of 5cde802... update
}