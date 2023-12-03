#include <Arduino.h>

#include "pitches.h"

#define MATRIX_DATA 4
#define MATRIX_CLOCK 16
#define MATRIX_LATCH 17

#define BUZZER 33

#define BTN_R 34
#define BTN_G 39
#define BTN_B 36
#define BTN_Y 32

// #define RFID_RST 0
// #define RFID_MISO 19
// #define RFID_MOSI 23
// #define RFID_SCK 18
// #define RFID_SDA 5

#define OLED_SCL 22 // not needed
#define OLED_SDA 21

#define RGB_R 15 // might be wrong order :)
#define RGB_G 14 // might be wrong order :)
#define RGB_B 12 // might be wrong order :)

#define LED_R 25
#define LED_Y 27
#define LED_G 26

// #define FOTO_RESISTOR 13
// #define TEMP 35

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define Serial Serial

byte smileyPattern[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};

byte letter_A[8] = {B00001100, B00011110, B00110011, B00110011, B00111111, B00110011, B00110011, B00000000}; // A
byte letter_I[8] = {B00011110, B00001100, B00001100, B00001100, B00001100, B00001100, B00011110, B00000000}; // I
byte letter_R[8] = {B00011111, B00110011, B00110011, B00011110, B00011011, B00110011, B00110011, B00000000}; // R
byte letter_V[8] = {B00110011, B00110011, B00110011, B00110011, B00110011, B00011110, B00001100, B00000000}; // V

// byte image[8];

int mode = 0;

void setup() {
	Serial.println("GO!");
	pinMode(LED_R, OUTPUT);
	pinMode(LED_Y, OUTPUT);
	pinMode(LED_G, OUTPUT);

	pinMode(BTN_R, INPUT);
	pinMode(BTN_G, INPUT);
	pinMode(BTN_B, INPUT);
	pinMode(BTN_Y, INPUT);

	pinMode(BUZZER, OUTPUT);

	Serial.begin(115200);

	pinMode(MATRIX_DATA, OUTPUT);
	pinMode(MATRIX_CLOCK, OUTPUT);
	pinMode(MATRIX_LATCH, OUTPUT);

	// Initialize shift registers and set them to zero
	digitalWrite(MATRIX_LATCH, LOW);
	// fix this to use my improved algorithm
	MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, 0);
	MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, 0);
	digitalWrite(MATRIX_LATCH, HIGH);

	delay(2000);

	Serial.println("Setup done!");
}

void loop() {
	if (digitalRead(BTN_Y) == 1) {
		digitalWrite(LED_R, 0);
		digitalWrite(LED_Y, 1);
		if (mode == 2) {
			mode = 0;
		} else {
			mode++;
		}
		delay(1000);
		digitalWrite(LED_Y, 0);
	}

	if (mode == 0) {
		displayImage(smileyPattern);
	} else if (mode == 1) {
		playStarWars();
	} else if (mode == 2) {
		for (int i = 0; i < 200; i++) {
			displayImage(letter_I);
		}
		for (int i = 0; i < 200; i++) {
			displayImage(letter_V);
		}
		for (int i = 0; i < 200; i++) {
			displayImage(letter_A);
		}
		for (int i = 0; i < 200; i++) {
			displayImage(letter_R);
		}
		for (int i = 0; i < 200; i++) {
			displayImage(smileyPattern);
		}
	}
}

// build this that uses the improved myshiftout
void displayImage(byte image[8]) {
	// Display the smiley face pattern
	for (int i = 0; i < 8; i++) {
		digitalWrite(MATRIX_LATCH, LOW);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, 255 - image[i]);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, pow(2, i));
		digitalWrite(MATRIX_LATCH, HIGH);
		delay(1); // test this delay I think 100hz should be fine
	}
}

// fix this to make it simpler
void MYshiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val) {
	digitalWrite(clockPin, LOW);
	for (int i = 0; i < 8; i++) {
		digitalWrite(dataPin, (val & 128) != 0);
		val <<= 1;
		delayMicroseconds(10);
		digitalWrite(clockPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(clockPin, LOW);
	}
}

void beep(int note, int duration) {
	tone(BUZZER, note, duration);
	delay(duration);
}

void playStarWars() {
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