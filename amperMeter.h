#ifndef MY_AMPERMETER_H
#define MY_AMPERMETER_H
#include "device.h"

class AmperMeter: public Device {
  public:
    AmperMeter();
    float getCurrent(int pin);
};

#endif
