#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "SPI.h"
#include "line.h"
#include "voltmeter.h"
#include "amperMeter.h"

#define ACSPINL1 A1 // Current pin input line 1
#define ACSPINL2 A2 // Current pin input line 2
#define ACSPINL3 A3 // Current pin input line 3

#define RELAYL1 5
#define RELAYL2 6
#define RELAYL3 7

#define TFT_CS 10
#define TFT_DC 9

class Delesteur {
  private:
    const String PASSWORD = "1A";
    const String NUMBER = "+243979049362";
    Voltmeter voltmeter;
    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC);
    Line lines[3] = {
      Line("lab", ACSPINL1, 10, RELAYL1),
      Line("Bur", ACSPINL2, 15, RELAYL2),
      Line("aud", ACSPINL3, 20, RELAYL3)
    };
    
  public:
    Delesteur();
    void checkLines();
    bool unlock(String password);
    void menu();
    void recover();
    void drawText(String text, uint16_t color,byte textSize, byte xPos, byte yPos);
    float power();
    float voltage();
    float current();
    void initLcd();
    bool isBlocked(); 
    void state();
    void showLockedView();
    void showUnlockedView();
    void clearScreen();
    void error();
    int getTextCenterPos(int length, int block);
    String getNumber();
    void unlockBySms();
};
