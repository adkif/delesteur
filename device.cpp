#include "device.h"

Device::Device(){}

float Device::peakToPeak(int pin){
  int highPeak = 0;
  int lowPeak = 1023;
  for(int count=0; count < SAMPLE; count++){
    int acsRawData = analogRead(pin);
    if(acsRawData > highPeak){
      highPeak = acsRawData;
    }
    if(acsRawData < lowPeak){
      lowPeak = acsRawData;
    }
  }
  return highPeak - lowPeak;
}
