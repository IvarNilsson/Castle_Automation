/*
  rfid_ardinio_alarm
  main
  ©Ivar Nilsson
  card: Arduino (UNO), I will probebly change this to the ESP32
*/

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];

// Set your masterKey (important!)
String MasterTag = "635D62A7"; // Set your masterKey (important!)
// Set your masterKey (important!)

String tagID = "";

const byte maxKeys = 6; // max number of allowed RFIDs (set to a high number if you dont want a limit)
int nrKeys;
String keyList[maxKeys];

int count = 0;

int buzzer = 8;

boolean validRFID;
boolean notAdded;
boolean locked = true;
boolean opend = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
  SPI.begin();
  mfrc522.PCD_Init();

  keyList[0] = MasterTag;
  nrKeys = 1;

  lcd.init();
  lcd.backlight();
  message();

  pinMode(buzzer, OUTPUT); // buzzer
  digitalWrite(buzzer, HIGH); // activated on LOW

  Serial.begin(9600);
  Serial.println("Booting RFID Reader...");
  Serial.println("");
}

void loop() {

  //Wait for new RFID
  while (getID()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    validRFID = false;
    for (int i = 0; i < maxKeys; i++) {
      if (tagID == keyList[i]) {
        lcd.print(" Welcome!");
        locked = false;
        opend = false;
        validRFID = true;
        break;
      }
    }
    if (validRFID == false) {
      lcd.print(" Wrong RFID!");
      alarm(5);
      locked = true;
      delay(500);
      message();
    }
    Serial.println(" ID : " + tagID); // Only for DEBUG
  }

  if (locked == false && addCard()) {

    while (addCard()) {
      getID();
      notAdded = true;
      for (int i = 0; i < maxKeys; i++) {
        if (tagID == keyList[i]) {
          notAdded = false;
          break;
        }
      }
      if (notAdded) {
        keyList[nrKeys] = tagID;
        nrKeys ++;
        Serial.println("Added Key with ID: " + tagID); // Only for DEBUG
      }
    }
  }

  if (light() && locked == false) {
    opend = true;
    delay(500); // small delay to avoid edgecase with fast refreshrate
  }

  if (light() == false && locked == false && opend) { // dark and have bean opend -> lock!
    opend = false;
    locked = true;
    lcd.clear();
    lcd.print(" Arming lock "); // fun but usless :)
    delay(1000);
    message();
  }

  if (light() && locked) { //open but locked -> intrution (the counter and delay is to not sound the alarm to often but not lose to much refreshrate)
    count++;
    delay(10);
  } else {
    count = 0;
  }

  if (light() && count == 50 && locked) { // open for 50 cycels -> alarm
    Serial.println("ALARM!"); // Only for DEBUG
    alarm(1);
    count = 0;
  }
}

boolean addCard() { // checks if the add card button is pressed
  if (analogRead(A2) == 1023) {
    return true;
  } else {
    return false;
  }
}

void message() { // displays the standard message
  lcd.clear();
  lcd.print(" Access Control ");
  lcd.setCursor(0, 1);
  lcd.print("Scan RFID Below");
}

void alarm(int loops) { // turns on the alarm for (loop) cycles
  for (int i = 0; i < loops; i++) {
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
  }
}

boolean light() { // checks the photoresistor lightlevel compared to the potentiometer
  if (analogRead(A0) < analogRead(A1)) {
    return true;
  } else {
    return false;
  }
}

boolean getID() { // sertches for RFID and returns true if a new card is read
  
  // Arming RFID reader
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { 
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Disarming RFID reader
  return true;
}