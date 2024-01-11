#include <MFRC522.h>
#include <SPI.h>

#define RFID_RST 0
#define RFID_MISO 19
#define RFID_MOSI 23
#define RFID_SCK 18
#define RFID_SDA 5

MFRC522 mfrc522(RFID_SDA, RFID_RST); // Create MFRC522 instance.

#define Serial Serial

void setup() {
	Serial.begin(115200);
	delay(1000);
	Serial.println("GO!");
	SPI.begin();
	mfrc522.PCD_Init();
	Serial.println("Setup DONE!");
}
void loop() {
	// Look for new cards
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	// Select one of the cards
	if (!mfrc522.PICC_ReadCardSerial()) {
		return;
	}
	// Show UID on serial monitor
	Serial.print("UID tag :");
	String content = "";
	byte letter;
	for (byte i = 0; i < mfrc522.uid.size; i++) {
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
		content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		content.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	Serial.println();
	Serial.print("Message : ");
	content.toUpperCase();
	if (content.substring(1) == "BD 31 15 2B") // change here the UID of the card/cards that you want to give access
	{
		Serial.println("Authorized access");
		Serial.println();
		delay(3000);
	}

	else {
		Serial.println(" Access denied");
		delay(3000);
	}
}
