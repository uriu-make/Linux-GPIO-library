#include <gpiodev.h>
#include <unistd.h>
#include <stdio.h>

gpio gpiochip0("/dev/gpiochip0");
int main(void) {
  gpiochip0.gpioSetup();
  int fd1 = gpiochip0.setupParallelOut(4, 20, 21, 22, 23);
  int fd2 = gpiochip0.setupParallelIn(4, 24, 25, 26, 27);

  unsigned char value[4] = {1, 0, 1, 0};
  unsigned char data[4] = {0};
  for (int i; i < 10; i++) {
    gpiochip0.ParallelWrite(fd1, value);
    gpiochip0.ParallelRead(fd2, data);
    printf("output:%d,%d,%d,%d input:%d,%d,%d,%d\n", value[0], value[1], value[2], value[3], data[0], data[1], data[2], data[3]);
    for (int i = 0; i < 4; i++)
      value[i] = !value[i];
    usleep(1000000);
  }
  gpiochip0.Close();
  return 0;
}