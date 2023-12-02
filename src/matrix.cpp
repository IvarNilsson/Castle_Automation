// 4 16 17  4 17 16   17 16 4    17 4 16    16 4 17   16 17 4
// något    hoppar      inget      inget     inget      inget
#include <Arduino.h>

#define MATRIX_DATA 4
#define MATRIX_CLOCK 16 // Corrected latch and clock pins
#define MATRIX_LATCH 17 // Corrected latch and clock pins

byte smileyPattern[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};

void setup() {
	pinMode(MATRIX_DATA, OUTPUT);
	pinMode(MATRIX_CLOCK, OUTPUT);
	pinMode(MATRIX_LATCH, OUTPUT);

	// Initialize shift registers and set them to zero
	digitalWrite(MATRIX_LATCH, LOW);
	// fix this to use my improved algorithm
	shiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, 0);
	shiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, 0);
	digitalWrite(MATRIX_LATCH, HIGH);
}

void loop() {
	// Display the smiley face pattern
	displayImage(smileyPattern);
}

// build this that uses the improved myshiftout
void displayImage(byte image[8]) {
	for (int i = 0; i < 8; i++) {
		digitalWrite(MATRIX_LATCH, LOW);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, 255 - image[i]);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, pow(2, i));
		digitalWrite(MATRIX_LATCH, HIGH);
		delay(2);
	}
}

// fix this to make it simpler
void MYshiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
	digitalWrite(clockPin, LOW);
	for (int i = 0; i < 8; i++) {
		if (bitOrder == LSBFIRST) {
			digitalWrite(dataPin, val & 1);
			val >>= 1;
		} else {
			digitalWrite(dataPin, (val & 128) != 0);
			val <<= 1;
		}

		delayMicroseconds(10);
		digitalWrite(clockPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(clockPin, LOW);
	}
}
