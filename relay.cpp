#include "relay.h"

Relay::Relay(){}

void Relay::init(int pin){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Relay::activate(){
  digitalWrite(pin, LOW);
}

void Relay::deactivate(){
  digitalWrite(pin, HIGH);
}
