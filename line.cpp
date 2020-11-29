#include "line.h"

Line::Line(String tag, int pinCommand, int limit, int pinPower){
  this->pin = pinCommand;
  this->tag = tag;
  this->limit = limit;
  this->isBlocked = false;
  relay.init(pinPower);
}
void Line::unblock(){
  if(isBlocked){
    isBlocked = false;
    relay.activate();
  }
}
void Line::block(){
  if(!isBlocked){
    isBlocked = true;
    relay.deactivate();
  }
}

int Line::getPin(){
  return pin;
}

int Line::getLimit(){
  return limit;
}

String Line::getTag(){
  return tag;
}

float Line::getCurrent(){
  return amperMeter.getCurrent(pin);
}
