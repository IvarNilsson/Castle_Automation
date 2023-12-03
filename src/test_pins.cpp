#define MATRIX_DATA 4
#define MATRIX_CLOCK 17
#define MATRIX_LATCH 16

#define BUZZER 33

#define BTN_R 36
#define BTN_G 39
#define BTN_B 34
#define BTN_Y 32

#define RFID_RST 0
#define RFID_MISO 19
#define RFID_MOSI 23
#define RFID_SCK 18
#define RFID_SDA 5

// #define OLED_SCL 22 //not needed
// #define OLED_SDA 21

#define RGB_R 15 // might be wrong order :)
#define RGB_G 14 // might be wrong order :)
#define RGB_B 12 // might be wrong order :)

#define LED_R 25
#define LED_Y 27
#define LED_G 26

#define FOTO_RESISTOR 13
#define TEMP 35

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define Serial Serial

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
	Serial.println("GO!");
	// pinMode(LED_R, OUTPUT);
	// pinMode(LED_Y, OUTPUT);
	// pinMode(LED_G, OUTPUT);

	// pinMode(BTN_R, INPUT);
	// pinMode(BTN_G, INPUT);
	// pinMode(BTN_B, INPUT);
	// pinMode(BTN_Y, INPUT);

	pinMode(MATRIX_DATA, OUTPUT);
	pinMode(MATRIX_CLOCK, OUTPUT);
	pinMode(MATRIX_LATCH, OUTPUT);

	digitalWrite(MATRIX_DATA, LOW);
	digitalWrite(MATRIX_CLOCK, LOW);
	digitalWrite(MATRIX_LATCH, HIGH);

	Serial.begin(115200);

	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("SSD1306 allocation failed"));
		for (;;)
			;
	}
	delay(2000);
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 10);
	display.println("Hello, world!");
	display.display();
	Serial.println("Setup done!");
}

void loop() {}