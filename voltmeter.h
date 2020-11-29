#include "device.h"
#define VOLTAGEPIN A0 // voltage pin

class Voltmeter: public Device{
  private:
    int pin;
  public:
    Voltmeter();
    float getVoltage();
};
