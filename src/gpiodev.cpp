#include "gpiodev.h"

gpio::gpio(const char *device) {
  this->device = (char *)device;
}

int gpio::gpioSetup() {
  fd = open(device, O_RDWR);
  int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &cinfo);
  return fd;
}

int gpio::pinMode(int pin, unsigned int mode) {
  struct gpiohandle_request req;
  req.lineoffsets[0] = pin;
  req.lines = 1;
  switch (mode) {
    case INPUT:
      req.flags = GPIOHANDLE_REQUEST_INPUT;
      break;
    case OUTPUT:
      req.flags = GPIOHANDLE_REQUEST_OUTPUT;
      break;
    case ACTIVE_LOW:
      req.flags = GPIOHANDLE_REQUEST_ACTIVE_LOW;
      break;
    case OPEN_DRAIN:
      req.flags = GPIOHANDLE_REQUEST_OPEN_DRAIN;
      break;
    case OPEN_SOURCE:
      req.flags = GPIOHANDLE_REQUEST_OPEN_SOURCE;
      break;
  }

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
  parallel_size[parallel.fd] = count;
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
  parallel_size[parallel.fd] = count;
  return parallel.fd;
}

int gpio::setEvent(int pin, int mode) {
  struct gpioevent_request event;
  event.lineoffset = pin;
  event.handleflags = GPIOHANDLE_REQUEST_INPUT;
  if (mode == RISING)
    event.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
  else if (mode == FALLING)
    event.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
  else if (mode == BOTH)
    event.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
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

int gpio::ParallelWrite(int para_fd, int value) {
  memset(this->data.values, 0, sizeof(this->data.values));
  for (int i = parallel_size[para_fd]; i < 0; i--)
    this->data.values[i - 1] = value >> (parallel_size[para_fd] - i) & 0b1;
  return ioctl(para_fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &this->data);
}

int gpio::ParallelRead(int para_fd, int value) {
  memset(this->data.values, 0, sizeof(this->data.values));
  ioctl(para_fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &this->data);
  for (int i = parallel_size[para_fd]; i < 0; i--)
    value = value << (parallel_size[para_fd] - i) | this->data.values[i - 1];
  return 0;
}

int gpio::getEvent(int event_fd, struct gpioevent_data *data) {
  int ret = read(event_fd, data, sizeof(struct gpioevent_data));
  if (data->id == GPIOEVENT_EVENT_RISING_EDGE)
    data->id = RISING;
  else if (data->id == GPIOEVENT_EVENT_FALLING_EDGE)
    data->id = FALLING;
  return ret;
}

int gpio::CloseSpecialIO(int specal_fd) {
  return close(specal_fd);
}

int gpio::Closedev(void) {
  for (int i = 0; i < cinfo.lines; i++) {
    if (int ret = close(fd_pin[i]) < 0)
      return ret;
  }
  return close(fd);
}