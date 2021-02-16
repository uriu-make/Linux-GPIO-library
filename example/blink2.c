#include <gpio.h>
#include <stdio.h>
#include <unistd.h>
int main(void) {
  gpioSetup("/dev/gpiochip0");
  int fd = setupParallelOut(2, 21, 25);
  printf("%d", fd);
  unsigned char data[] = {0, 1};
  for (int i; i < 1000; i++) {
    ParallelWrite(fd, data);
    data[0] = !data[0];
    data[1] = !data[1];
    usleep(1000000);
  }
  GPIOclose();
  return 0;
}