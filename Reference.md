# Reference
```
  gpio::gpio(const char *device);
```
```
  int gpio::gpioSetup();
```
```
  int gpio::pinMode(int pin, unsigned int mode);
```
```
  int gpio::setupParallelOut(unsigned int count, ...);
```
```
  int gpio::setupParallelIn(unsigned int count, ...);
```
```
  int gpio::setEvent(int pin, int mode);
```
```
  int gpio::digitalWrite(int pin, int value);
```
```
  int gpio::digitalRead(int pin);
```
```
  int gpio::ParallelWrite(int para_num, unsigned char *value);
```
```
  int gpio::ParallelRead(int para_num, unsigned char *value);
```
```
  int gpio::getEvent(int event_num, struct gpioevent_data *data);
```
```
  int gpio::CloseSpecialIO(int num);
```
```
  int gpio::Closedev(void);
```