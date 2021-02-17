#include "gpiodev.h"

gpio::gpio(const char *device) {
  this->device = (char *)device;
}
int gpio::gpioSetup() {
  fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  fd_pin = (int *)calloc(cinfo.lines, sizeof(int));
  return fd;
}

int gpio::pinMode(int pin, unsigned int mode) {
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
  return fd_pin[pin];
}

int gpio::setupParallelOut(unsigned int count, ...) {
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

int gpio::setupParallelIn(unsigned int count, ...) {
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

int gpio::setEvent(int pin, int mode) {
  struct gpioevent_request event;
  event.lineoffset = pin;
  if (mode == RISING)
    event.eventflags = GPIOEVENT_EVENT_RISING_EDGE;
  else if (mode == FALLING)
    event.eventflags = GPIOEVENT_EVENT_FALLING_EDGE;
  ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &event);
  return event.fd;
}

int gpio::digitalWrite(int pin, int value) {
  memset(data.values, 0, sizeof(data.values));
  data.values[0] = value;
  return ioctl(fd_pin[pin], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

int gpio::digitalRead(int pin) {
  memset(data.values, 0, sizeof(data.values));
  ioctl(fd_pin[pin], GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
  return (int)data.values[0];
}

int gpio::ParallelWrite(int para_num, unsigned char *value) {
  memset(this->data.values, 0, sizeof(this->data.values));
  for (int i = 0; i < sizeof(value); i++)
    this->data.values[i] = value[i];
  return ioctl(para_num, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &this->data);
}

int gpio::ParallelRead(int para_num, unsigned char *data) {
  memset(this->data.values, 0, sizeof(this->data.values));
  ioctl(para_num, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &this->data);
  for (int i = 0; i < sizeof(data); i++)
    data[i] = this->data.values[i];
  return 0;
}

int gpio::CloseSpecialIO(int num) {
  return close(num);
}

int gpio::Closedev(void) {
  for (int i = 0; i < cinfo.lines; i++) {
    if (int ret = close(fd_pin[i]) < 0)
      return ret;
  }
  free(fd_pin);
  return close(fd);
}