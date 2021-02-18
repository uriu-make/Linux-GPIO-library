#include <gpiodev.h>
#include <stdio.h>
#include <unistd.h>
gpio gpiochip0("/dev/gpiochip0");

void check_event(int event_num);

int main(void) {
  gpiochip0.gpioSetup();
  gpiochip0.pinMode(25, OUTPUT);
  gpiochip0.digitalWrite(25, LOW);
  int event0 = gpiochip0.setEvent(21, BOTH);
  usleep(1000);
  gpiochip0.digitalWrite(25, HIGH);
  check_event(event0);
  usleep(10000);
  gpiochip0.digitalWrite(25, LOW);
  check_event(event0);
  gpiochip0.CloseSpecialIO(event0);
  gpiochip0.Closedev();
  return 0;
}

void check_event(int event_num) {
  struct gpioevent_data data;
  gpiochip0.getEvent(event_num, &data);
  if (data.id == RISING) {
    char s[] = {"Rising"};
    printf("Event:%s,Timestamp:%lluns\n", s, data.timestamp);
  } else if (data.id == FALLING) {
    char s[] = {"Falling"};
    printf("Event:%s,Timestamp:%lluns\n", s, data.timestamp);
  }
}