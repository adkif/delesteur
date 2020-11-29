#include "delesteur.h"

Delesteur::Delesteur(){}

void Delesteur::checkLines(){
  for(int i=0; i < 3; i++){
    float current = lines[i].getCurrent();
    if(current > lines[i].getLimit()){
      lines[i].block();
    }
  }
}

bool Delesteur::unlock(String password){
  bool lock = true;
  if(password == PASSWORD){
    for(int i=0; i < 3; i++){
      lines[i].unblock();
    }
    lock = false;
  }
  return lock;
}

void Delesteur::unlockBySms(){
  for(int i=0; i < 3; i++){
      lines[i].unblock();
  }
}

float Delesteur::power(){
  return voltage() * current();
}

float Delesteur::voltage(){
  return voltmeter.getVoltage();
}

float Delesteur::current(){
  float current = 0;
  for(int i=0; i < 3; i++){
    current += lines[i].getCurrent();
  }
  return current;
}

void Delesteur::drawText(String text, uint16_t color,byte textSize, byte xPos, byte yPos){
  tft.setCursor(xPos, yPos);
  tft.setTextSize(textSize);
  tft.setTextColor(color, ST7735_BLACK);
  tft.setTextWrap(true);
  tft.print(text);
}

void Delesteur::menu(){
  drawText("Power", ST7735_WHITE,1, 5 , 0 );
  drawText(String(power())+"W", ST7735_WHITE,2, 5 , 10 );
  drawText("Voltage", ST7735_WHITE,1, 5 , 30 );
  drawText(String(voltage())+"V", ST7735_WHITE,2, 5 , 40 );
  drawText("Current", ST7735_WHITE,1, 5 , 60 );
  drawText(String(current())+"A", ST7735_WHITE,2, 5 , 70 );
  tft.drawFastHLine(0, 90, tft.width(),ST7735_WHITE);
  drawText(String(lines[0].getTag())+"["+String(lines[0].getLimit())+"A]:"+String(lines[0].getCurrent())+"A", ST7735_WHITE, 1, 5 , 95 );
  drawText(String(lines[1].getTag())+"["+String(lines[1].getLimit())+"A]:"+String(lines[1].getCurrent())+"A", ST7735_WHITE, 1, 5 , 115);
  drawText(String(lines[2].getTag())+"["+String(lines[2].getLimit())+"A]:"+String(lines[2].getCurrent())+"A", ST7735_WHITE, 1, 5 , 135);
  state();
}

void Delesteur::error(){
  drawText("Password Error", ST7735_RED, 1, 5 , 65);
  drawText("Try again", ST7735_WHITE, 1, 5 , 85);
}

void Delesteur::state(){
  if(lines[0].isBlocked){
    drawText("err", ST7735_RED, 1,  110 , 95);
    drawText("(#)->", ST7735_YELLOW, 1, 90 , 150);
  }else{
    drawText("Ok", ST7735_GREEN, 1, 110 , 95);
  }
  if(lines[1].isBlocked){
    drawText("err", ST7735_RED, 1, 110 , 115);
    drawText("(#)->", ST7735_YELLOW, 1, 90 , 150);
  }else{
    drawText("Ok", ST7735_GREEN, 1, 110 , 115);
  }
  if(lines[2].isBlocked){
    drawText("err", ST7735_RED, 1, 110 , 135);
    drawText("(#)->", ST7735_YELLOW, 1, 90 , 150);
  }else{
    drawText("Ok", ST7735_GREEN, 1, 110 , 135);
  }
}

bool Delesteur::isBlocked(){
  bool locked = false;
  for(int i = 0; i < 3; i++){
    if(lines[i].isBlocked){
      locked = true;
      break;
    }
  }
  return locked;
}

void Delesteur::initLcd(){
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
}

void Delesteur::recover(){
  showLockedView();
  drawText("Password:", ST7735_RED,1, 5, 130);
  drawText("(#)->", ST7735_YELLOW, 1, 97 , 150);
}

void Delesteur::showLockedView() {
  //draw lock
  uint16_t color = 0xE945;
  uint8_t lockSize = 56;
  uint8_t lockX = (tft.width() - lockSize) / 2;
  uint8_t lockY = 30;
  tft.fillRoundRect(lockX + lockSize / 5, lockY - 48 / 2, 3 * lockSize / 5, 16 + 48 / 2, 16, color);
  tft.fillRoundRect(lockX + lockSize / 5 + 8, lockY - 48 / 2 + 8, 3 * lockSize / 5 - 8 * 2, 40, 16, ST7735_BLACK);
  tft.fillRoundRect(lockX, lockY, lockSize, 48, 10, color);
  tft.fillCircle(lockX + lockSize / 2, lockY + 48 / 2, 8, ST7735_BLACK);
  //draw text
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  int pos = getTextCenterPos(strlen("Unload line(s) below:"), 1);
  int initHeight = 80;
  tft.setCursor(pos, initHeight);
  tft.setTextSize(1);
  tft.println("Unload line(s) below:");
  for(int i=0; i < 3; i++){
    if(lines[i].isBlocked){
      pos = getTextCenterPos(lines[i].getTag().length(), 1);
      initHeight+=7*1 + 3;
      tft.setCursor(pos, initHeight);
      tft.println(lines[i].getTag());
    }
  }
}

void Delesteur::showUnlockedView() {
  tft.fillScreen(ST7735_BLACK);
  //draw lock
  uint16_t color = 0x5667;
  uint8_t lockSize = 70;
  uint8_t lockX = (tft.width() - lockSize) / 2;
  uint8_t lockY = 38;
  tft.fillRoundRect(lockX + lockSize / 5, lockY - 60 / 2, 3 * lockSize / 5, 20 + 60 / 2, 20, color);
  tft.fillRoundRect(lockX + lockSize / 5 + 8, lockY - 60 / 2 + 8, 3 * lockSize / 5 - 8 * 2, 40, 20, ST7735_BLACK);
  tft.fillRoundRect(lockX, lockY, lockSize, 60, 10, color);
  tft.fillRect(lockX, lockY - 10, lockSize / 2, 10, ST7735_BLACK);
  uint8_t x0 = lockX + 15; uint8_t y0 = lockY + 29;
  uint8_t x1 = lockX + 20; uint8_t y1 = lockY + 24;
  uint8_t x2 = lockX + 31; uint8_t y2 = lockY + 34;
  uint8_t x3 = lockX + 31; uint8_t y3 = lockY + 45;
  uint8_t x4 = lockX + 56; uint8_t y4 = lockY + 20;
  uint8_t x5 = lockX + 51; uint8_t y5 = lockY + 15;
  tft.fillTriangle(x0, y0, x1, y1, x2, y2, ST7735_BLACK);
  tft.fillTriangle(x0, y0, x2, y2, x3, y3, ST7735_BLACK);
  tft.fillTriangle(x2, y2, x3, y3, x4, y4, ST7735_BLACK);
  tft.fillTriangle(x2, y2, x4, y4, x5, y5, ST7735_BLACK);
  //draw text
  int pos = getTextCenterPos(strlen("Unblock"), 1);
  tft.setCursor(pos, 105);
  tft.setTextSize(1);
  tft.println("Unblock");
}

int Delesteur::getTextCenterPos(int length, int block){
  return (tft.width() - (5*length*block + (length -1)*block))/2;
}

void Delesteur::clearScreen(){
  tft.fillScreen(ST7735_BLACK);
}

String Delesteur::getNumber(){
  return this->NUMBER;
}
