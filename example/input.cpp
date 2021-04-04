#include <gpiodev.h>
#include <unistd.h>

gpio gpiochip0("/dev/gpiochip0");

int main(void) {
  gpiochip0.gpioSetup();
  gpiochip0.pinMode(21, INPUT);

  for (int i = 0; i < 10000; i++) {
    printf("%d\n", gpiochip0.digitalRead(21));
    usleep(1000);
  }
  
  gpiochip0.Closedev();
  return 0;
}