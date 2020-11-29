#ifndef MY_DEVICE_H
#define MY_DEVICE_H

#include "Arduino.h"
#define SENSITIVITY 66 // Sensitivity acs712-30A
#define OFFSET 2500 // Offset computing for acs712-30A
#define MAXVOLTAGE 360 // maximal voltage
#define SAMPLE 300

class Device {
  public:
    Device();
    float peakToPeak(int pin);
};

#endif
