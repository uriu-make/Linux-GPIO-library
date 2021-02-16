#include <gpio.h>
#include <stdio.h>
#include <unistd.h>
int main(void) {
  gpioSetup("/dev/gpiochip0");
  pinMode(25, OUTPUT);
  usleep(60 * 1000 * 1000);
  GPIOclose();
  return 0;
}