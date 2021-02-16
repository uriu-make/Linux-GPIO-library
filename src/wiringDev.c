#include "wiringDev.h"
int fd;
int *fd_pin;
struct gpiochip_info cinfo;
struct gpioline_info linfo;
struct gpiohandle_data data;

int gpioSetup(char *device) {
  fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  fd_pin = (int *)calloc(cinfo.lines, sizeof(int));
  return fd;
}

int pinMode(int pin, unsigned int mode) {
  struct gpiohandle_request req;
  req.lineoffsets[0] = pin;
  req.lines = 1;
  if (mode != INPUT)
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
  else
    req.flags = GPIOHANDLE_REQUEST_INPUT;
  req.default_values[0] = 1;
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
  fd_pin[pin] = req.fd;
}

int setupParallelOut(unsigned int count, ...) {
  struct gpiohandle_request parallel;
  va_list ap;
  va_start(ap, count);
  parallel.flags = GPIOHANDLE_REQUEST_OUTPUT;
  parallel.lines = count;
  for (int i = 0; i < count; i++) {
    parallel.lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &parallel);
  return parallel.fd;
}

int setupParallelIn(unsigned int count, ...) {
  struct gpiohandle_request parallel;
  va_list ap;
  va_start(ap, count);
  parallel.flags = GPIOHANDLE_REQUEST_INPUT;
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
  return (int)data.values[0];
}

int ParallelWrite(int fd_para, unsigned char *value) {
  memset(data.values, 0, sizeof(data.values));
  for (int i = 0; i < sizeof(value); i++)
    data.values[i] = value[i];
  return ioctl(fd_para, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

unsigned char *ParallelRead(int fd_para) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(fd_para, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return data.values;
}

void GPIOclose(void) {
  free(fd_pin);
}