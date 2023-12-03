#define MATRIX_DATA 4
#define MATRIX_CLOCK 17
#define MATRIX_LATCH 16

#define BUZZER 33

#define BTN_R 34
#define BTN_G 39
#define BTN_B 36
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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int i = 0;

void setup() {
	Serial.println("GO!");
	pinMode(LED_R, OUTPUT);
	pinMode(LED_Y, OUTPUT);
	pinMode(LED_G, OUTPUT);

	pinMode(BTN_R, INPUT);
	pinMode(BTN_G, INPUT);
	pinMode(BTN_B, INPUT);
	pinMode(BTN_Y, INPUT);

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

void loop() {
	display.clearDisplay();

	display.setCursor(100, 0);
	display.println(i);

	display.setCursor(0, 0);
	if (digitalRead(BTN_R) == 1) {
		display.println("RED:    ON");
		digitalWrite(LED_R, 1);
	} else {
		display.println("RED:    OFF");
		digitalWrite(LED_R, 0);
	}

	display.setCursor(0, 15);
	if (digitalRead(BTN_G) == 1) {
		display.println("GREEN:  ON");
		digitalWrite(LED_G, 1);
	} else {
		display.println("GREEN:  OFF");
		digitalWrite(LED_G, 0);
	}

	display.setCursor(0, 30);
	if (digitalRead(BTN_B) == 1) {
		display.println("BLUE:   ON");
		digitalWrite(LED_R, 1);
		digitalWrite(LED_G, 1);
		digitalWrite(LED_Y, 1);

	} else {
		display.println("BLUE:   OFF");
		digitalWrite(LED_R, 0);
		digitalWrite(LED_G, 0);
		digitalWrite(LED_Y, 0);
	}

	display.setCursor(0, 45);
	if (digitalRead(BTN_Y) == 1) {
		display.println("YELLOW: ON");
		digitalWrite(LED_Y, 1);
	} else {
		display.println("YELLOW: OFF");
		digitalWrite(LED_Y, 0);
	}

	display.display();
	delay(500);
	i++;
	if (i == 100) {
		i = 0;
	}
}