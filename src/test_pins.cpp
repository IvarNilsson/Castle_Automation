#define MATRIX_DATA 4
#define MATRIX_CLOCK 17
#define MATRIX_LATCH 16

#define BUZZER 33

#define BUTTN_R 36
#define BUTTN_G 39
#define BUTTN_B 34
#define BUTTN_Y 32

#define RFID_RST 0
#define RFID_MISO 19
#define RFID_MOSI 23
#define RFID_SCK 18
#define RFID_SDA 5

#define OLED_SCL 22
#define OLED_SDA 21

#define RGB_R 15  // might be wrong order :)
#define RGB_G 14  // might be wrong order :)
#define RGB_B 12  // might be wrong order :)

#define LED_R 25
#define LED_Y 26
#define LED_G 27

#define FOTO_RESISTOR 13
#define TEMP 35

#include <Arduino.h>

void setup() { pinMode(LED_R, OUTPUT); }

void loop() {
    delay(500);
    digitalWrite(LED_R, HIGH);
    delay(500);
    digitalWrite(LED_R, LOW);
}