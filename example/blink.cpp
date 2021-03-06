#include <gpiodev.h>
#include <unistd.h>
gpio gpiochip0("/dev/gpiochip0");

int main(void) {
  gpiochip0.gpioSetup();
  gpiochip0.pinMode(21, OUTPUT);
  for (int i; i < 1000; i++) {
    gpiochip0.digitalWrite(21, LOW);
    usleep(1000000);
    gpiochip0.digitalWrite(21, HIGH);
    usleep(1000000);
  }
  gpiochip0.Closedev();
  return 0;
}