#include <wiringDev.h>

gpio gpiochip0("/dev/gpiochip0");
int main(void) {
  gpiochip0.gpioSetup();
  int fd1 = gpiochip0.setupParallelOut(4, 20, 21, 22, 23);
  printf("%d", fd1);
  unsigned char data[] = {1, 1, 1, 1};
  for (int i; i < 10000000; i++) {
    gpiochip0.ParallelWrite(fd1, data);
    for (int i = 0; i < 4; i++)
      data[i] = !data[i];
    // usleep(1000000);
  }
  gpiochip0.Close();
  return 0;
}