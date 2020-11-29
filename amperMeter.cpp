#include "amperMeter.h"

AmperMeter::AmperMeter(){}

float AmperMeter::getCurrent(int pin){
  return peakToPeak(pin) * 5000 / 1023 / SENSITIVITY* sqrt(2)/ 4;
}
