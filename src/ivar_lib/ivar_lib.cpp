#include "ivar_lib.h"

ivar_lib::ivar_lib() {
	// Constructor
}

void ivar_lib::ivar_shiftOut(gpio_num_t dataPin, gpio_num_t clockPin, uint8_t val) {
	gpio_set_level(clockPin, 0);
	for (int i = 0; i < 8; i++) {
		// shift out data
		gpio_set_level(dataPin, (val & 128) != 0);
		val <<= 1;

		// delayMicroseconds(10); // find alternative
		vTaskDelay(1 / portTICK_PERIOD_MS);

		gpio_set_level(clockPin, 1);
		// delayMicroseconds(10);
		vTaskDelay(1 / portTICK_PERIOD_MS); //might be too long :(

		gpio_set_level(clockPin, 0);
	}
}
