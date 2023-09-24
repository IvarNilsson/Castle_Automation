//#include "arduino.h"
#include "pitches.h"

const int buzzerPin = 16; //for Arduino Microcontroller
//const int buzzerPin = D7; //for ESP8266 Microcontroller
//const int buzzerPin = 4; //for ESP32 Microcontroller

void beep(int note, int duration){
  tone(buzzerPin, note, duration);
  delay(duration);
}

void setup(){
  pinMode(buzzerPin, OUTPUT);
}
 
void loop() {
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);    
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);  
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);  
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GS5, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);    
  beep(NOTE_FS5, 250);
 
  delay(325);
 
  beep(NOTE_AS4, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);  
  beep(NOTE_CS5, 175);  
  beep(NOTE_C5, 125);  
  beep(NOTE_AS4, 125);  
  beep(NOTE_C5, 250);  
 
  delay(350);
}