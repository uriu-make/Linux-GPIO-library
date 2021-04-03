# Reference
```
  gpio::gpio(const char *device);
```
Open char device.
```
  int gpio::gpioSetup();
```
Check the number of GPIOs in /dev/gpiochipN and get ready to use them.
```
  int gpio::pinMode(int pin, unsigned int mode);
```
Setup GPIO mode INPUT/OUTPUT. 
**pin** : GPIO pin number (BCM)\
**mode** : INPUT or OUTPUT
```
  int gpio::setupParallelOut(unsigned int count, ...);
```
Create groups for simultaneous output of multiple pins.\
**count** : Number of GPIO pins to be used\
**return** : File descriptor
```
  int gpio::setupParallelIn(unsigned int count, ...);
```
Create groups for simultaneous input of multiple pins.\
**count** : Number of GPIO pins to be used\
**return** : File descriptor
```
  int gpio::setEvent(int pin, int mode);
```
**pin** : GPIO pin number (BCM)\
**mode** : Setting the state to be detected
- **RISING** : GPIO changes from LOW to HIGH
- **FALLING** : GPIO changes from HIGH to LOW
- **BOTH** : Either RISING or FALLING has occurred
```
  int gpio::digitalWrite(int pin, int value);
```
Output from specified pins\
**pin** : GPIO pin number (BCM)\
**value** : HIGH or LOW
```
  int gpio::digitalRead(int pin);
```
Returns the status of the specified pin\
**pin** : GPIO pin number (BCM)\
**return** : HIGH or LOW
```
  int gpio::ParallelWrite(int para_fd, int value);
```
Multiple pins output simultaneously. The first pin specified in setupParallelOut() is MSB and the last pin specified is LSB\
**para_fd** : Return value obtained by setupParallelOut()\
**value** : Output of each pin
```
  int gpio::ParallelRead(int para_fd);
```
Multiple pin simultaneous input. The first pin specified in setupParallelOut() is MSB and the last pin specified is LSB\
**para_fd** : Return value obtained by setupParallelOut()\
**return** : State of each pin
```
  int gpio::getEvent(int event_fd, struct gpioevent_data *data);
```
Detects a change in the state of a GPIO pin and returns the time (ns) at which the event occurred and the type of change.\
**event_fd** : Return value obtained by setEvent()\
**data** : A structure that stores the time and type of event occurrence.
- **timestamp** : best estimate of time of event occurrence, in nanoseconds
- **id** : event identifier
```
  int gpio::CloseSpecialIO(int special_fd);
```
Close Parallel I/O and event\
**special_fd** : Each file descriptor.
```
  int gpio::Closedev(void);
```
Close /dev/gpiochipN.