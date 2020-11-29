#include "voltmeter.h"

Voltmeter::Voltmeter(){
  this->pin = VOLTAGEPIN;
}

float Voltmeter::getVoltage(){
  return peakToPeak(pin)/ 1023 * MAXVOLTAGE * sqrt(2)/ 2;
}
