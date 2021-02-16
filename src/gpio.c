#include "gpio.h"
int fd;
int i = 0;
struct gpiochip_info cinfo;
struct gpioline_info linfo;
struct gpiohandle_request *req;
struct gpiohandle_request *parallel;
struct gpiohandle_data data;

int gpioSetup(char *device) {
  int fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  req = (struct gpiohandle_request *)malloc(cinfo.lines * sizeof(struct gpiohandle_request));
  return fd;
}

int pinMode(int pin, unsigned int mode) {
  req[pin].lineoffsets[0] = pin;
  req[pin].lines = 1;
  req[pin].flags = mode;
  return ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
}

int setupParallelOut(unsigned int count, ...) {
  i++;
  parallel = (struct gpiohandle_request *)malloc(i * sizeof(struct gpiohandle_request));
  va_list ap;
  va_start(ap, count);
  parallel[i - 1].flags = OUTPUT;
  parallel[i - 1].lines = count;
  for (int i = 0; i < count; i++) {
    parallel[i - 1].lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &parallel);
  return i - 1;
}

int setupParallelIn(unsigned int count, ...) {
  i++;
  parallel = (struct gpiohandle_request *)malloc(i * sizeof(struct gpiohandle_request));
  va_list ap;
  va_start(ap, count);
  parallel[i - 1].flags = INPUT;
  parallel[i - 1].lines = count;
  for (int i = 0; i < count; i++) {
    parallel[i - 1].lineoffsets[i] = va_arg(ap, int);
  }
  va_end(ap);
  ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &parallel);
  return i - 1;
}

int digitalWrite(int pin, int value) {
  memset(data.values, 0, sizeof(data.values));
  data.values[0] = value;
  return ioctl(req[pin].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

int digitalRead(int pin) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(req[pin].fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return (int)data.values[0];
}

int ParallelWrite(int paranum, unsigned char *value) {
  memset(data.values, 0, sizeof(data.values));
  for (int i = 0; i < sizeof(value); i++)
    data.values[i] = value[i];
  ioctl(parallel[paranum].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

unsigned char *ParallelRead(int paranum) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(parallel[paranum].fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return data.values;
}

void GPIOclose(void) {
  free(req);
}