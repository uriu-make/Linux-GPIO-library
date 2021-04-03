#include <gpiodev.h>
#include <unistd.h>
#include <stdio.h>

gpio gpiochip0("/dev/gpiochip0");

void dec2bin(const int value);
int main(void) {
  gpiochip0.gpioSetup();
  int fd1 = gpiochip0.setupParallelOut(4, 20, 21, 22, 23);
  int fd2 = gpiochip0.setupParallelIn(4, 24, 25, 26, 27);

  int value = 0b1010;
  int data = 0;
  for (int i; i < 10; i++) {
    gpiochip0.ParallelWrite(fd1, value);
    data = gpiochip0.ParallelRead(fd2);
    printf("output:%d,input:%d\n", value, data);
    value = !value;
    usleep(1000000);
  }
  gpiochip0.CloseSpecialIO(fd1);
  gpiochip0.CloseSpecialIO(fd2);
  gpiochip0.Closedev();
  return 0;
}
