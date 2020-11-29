#include "delesteur.h"
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define I2CADDR 0x38
#define INT 2
#define RX_GSM 12
#define TX_GSM 8

long lastTime = 0;
long rightNow = 0;
long dt = 500;
int counter = 0;
Delesteur delesteur;
String pass = "";
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// custom keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

Keypad_I2C keypad = Keypad_I2C( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );
SoftwareSerial SIM900(RX_GSM,TX_GSM);

String incomingData;
String message = "";

void setup(){
  delesteur.initLcd();
  SIM900.begin(9600);
  Serial.begin(9600);
  while( !Serial ){ /*wait*/ }
  Wire.begin();
  keypad.begin(makeKeymap(keys));
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.print("AT+CNMI=1,2,0,0,0\r");
  delay(100);
}

void loop(){
 char key = keypad.getKey();
 bool lock = true;
 String pass = "";
 rightNow = millis();
  if (key && delesteur.isBlocked()) {
    switch (key){
      case '#':
        delesteur.clearScreen();
        while(lock){
          rightNow = millis();
          char keyPressed = keypad.getKey();
           if (keyPressed) {
             switch (keyPressed){
              case '#':
                lock = delesteur.unlock(pass);
                if(!lock){
                  counter = 0;
                  delesteur.clearScreen();
                  delesteur.showUnlockedView();
                  delay(1000);
                  delesteur.clearScreen();
                }else{
                  delesteur.clearScreen();
                  delesteur.error();
                  delay(1000);
                  delesteur.clearScreen();
                }
                pass = "";
                break;
              default:
                pass += keyPressed;
                Serial.println(pass);
                break;
             }
           }else if(rightNow - lastTime >= dt){
            lastTime = rightNow;
            delesteur.checkLines();
            delesteur.recover();
           }
        }
        break;
      default:
        break;
      }  
   }
   if((rightNow - lastTime) >= dt){
    lastTime = rightNow;
    delesteur.checkLines();
    delesteur.menu();
   }
   
   if(counter == 0 && delesteur.isBlocked()){
      sendMessage("OverLoad!");
      counter++;
   }
   
   if(delesteur.isBlocked()){
    receiveMessage();
    if(incomingData.indexOf("unblock")>=0){
        delesteur.unlockBySms();
    }
   }
}

void sendMessage(String message){
  Serial.println("Sending...");
  SIM900.println("AT+CMGF=1");
  delay(100);
  SIM900.println("AT+CMGS=\""+delesteur.getNumber()+"\"");
  delay(100);
  SIM900.println(message);
  delay(100);
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  delay(100);
  Serial.println("Finish...");
}

void receiveMessage(){
  if(SIM900.available() > 0){
    incomingData = SIM900.readString();
    Serial.print(incomingData);
    delay(10);
  }
}
