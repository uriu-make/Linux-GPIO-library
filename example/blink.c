#include <gpio.h>
#include <stdio.h>
#include <unistd.h>
int main(void) {
  gpioSetup("/dev/gpiochip0");
  pinMode(25, OUTPUT);
  for (int i; i < 1000; i++) {
    digitalWrite(25, LOW);
    usleep(1000000);
    digitalWrite(25, HIGH);
    usleep(1000000);
  }
  GPIOclose();
  return 0;
}