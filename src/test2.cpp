#include "stdio.h"

#define LED 27

void setup() {
  // Set pin mode
  pinMode(LED,OUTPUT);
}

void loop() {
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
}