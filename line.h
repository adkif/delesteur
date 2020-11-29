#include "Arduino.h"
#include "AmperMeter.h"
#include "relay.h"

class Line {
  private:
    String tag;
    int pin;
    int limit;
    float current;
    AmperMeter amperMeter;
    Relay relay;
  public:
    Line(String tag, int pinCommand, int limit, int pinPower);
    bool isBlocked;
    void unblock();
    void block();
    int getPin();
    int getLimit();
    String getTag();
    float getCurrent();
};
