#include <wiringDev.h>
#include <unistd.h>
gpio gpiochip0("/dev/gpiochip0");

int main(void) {
  gpiochip0.gpioSetup();
  int fd_para = gpiochip0.setupParallelOut(2, 21, 25);
  unsigned char data[] = {0, 1};
  for (int i; i < 1000; i++) {
    gpiochip0.ParallelWrite(fd_para, data);
    data[0] = !data[0];
    data[1] = !data[1];
    usleep(1000000);
  }
  gpiochip0.Close();
  return 0;
}