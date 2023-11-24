#ifndef ivar_lib_h
#define ivar_lib_h

#include <Arduino.h>

class ivar_lib {
public:
  ivar_lib();
  void ivar_shiftOut(gpio_num_t dataPin, gpio_num_t clockPin, uint8_t val);

private:
  const char *wifiSSID;
  const char *wifiPassword;
};

#endif