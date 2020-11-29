#include "Arduino.h"

class Relay {
  private:
    int pin;
  public:
    Relay();
    void init(int pin);
    void activate();
    void deactivate();
};
