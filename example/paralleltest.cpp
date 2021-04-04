#include <gpiodev.h>
#include <unistd.h>
#include <stdio.h>

gpio gpiochip0("/dev/gpiochip0");

int dec2bin(const int value);

int main(void) {
  gpiochip0.gpioSetup();
  int fd1 = gpiochip0.setupParallelOut(4, 20, 21, 22, 23);
  int fd2 = gpiochip0.setupParallelIn(4, 24, 25, 26, 27);

  int value = 0b1010;
  int data = 0;
  for (int i = 0; i < 10; i++) {
    gpiochip0.ParallelWrite(fd1, value);
    data = gpiochip0.ParallelRead(fd2);
    printf("output:0b%d,input:0b%d\n", dec2bin(value), dec2bin(data));
    value = ~value & 0b1111;
    usleep(1000000);
  }
  gpiochip0.CloseSpecialIO(fd1);
  gpiochip0.CloseSpecialIO(fd2);
  gpiochip0.Closedev();
  return 0;
}

int dec2bin(int value) {
  int bin = 0, length = sizeof(int);
  for (int i = 1; i <= length * 8; i++)
    bin = bin * 10 + ((((unsigned int)value >> length * 8 - i) & 0b00000001));
  return bin;
}
