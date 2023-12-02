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
		//  vTaskDelay(0.01 / portTICK_PERIOD_MS);

		ivar_delay_u(10);
		gpio_set_level(clockPin, 1);


		// delayMicroseconds(10);
		//  vTaskDelay(0.01 / portTICK_PERIOD_MS); //might be too long :(
		ivar_delay_u(10);
		gpio_set_level(clockPin, 0);
	}
}

void ivar_lib::ivar_delay_u(uint64_t number_of_microseconds) {
	uint64_t microseconds = esp_timer_get_time();
	if (0 != number_of_microseconds) {
		while (((uint64_t)esp_timer_get_time() - microseconds) <= number_of_microseconds) {
			// Wait
		}
	}
}