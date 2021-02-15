#include "gpio.h"
int fd;
struct gpiochip_info cinfo;
struct gpioline_info linfo;
struct gpiohandle_request *req;
struct gpiohandle_request parallel;
struct gpiohandle_data data;

int gpioSetup(char *device) {
  int fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  req = malloc(cinfo.lines * sizeof(struct gpiohandle_request));
  return fd;
}

int pinMode(int pin, unsigned int mode) {
  req[pin].lineoffsets[0] = pin;
  req[pin].lines = 1;
  req[pin].flags = mode;
  return ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
}

int setupParallel(unsigned int count, unsigned int mode, int pin, ...) {
  va_list ap;
  double sum = 0;
  va_start(ap, count);
  parallel.flags = va_arg(ap, unsigned int);
  parallel.lines = count;
  for (int i = 0; i < count; i++) {
    parallel.lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
  return parallel.fd;
}

int digitalWrite(int pin, int value) {
  memset(data.values, 0, sizeof(data.values));
  data.values[0] = value;
  return ioctl(req[pin].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

int digitalRead(int pin) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(req[pin].fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return (int)data.values;
}

int ParallelWrite(int fd, unsigned char *value) {
  parallel.fd = fd;
  memset(data.values, 0, sizeof(data.values));
  for (int i = 0; i < sizeof(value); i++)
    data.values[i] = value[i];
  ioctl(parallel.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

unsigned char ParallelRead(int fd) {
  parallel.fd = fd;
  memset(data.values, 0, sizeof(data.values));
  ioctl(parallel.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return data.values;
}

void GPIOclose(void) {
  free(req);
}