#include <Arduino.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main();

#define MATRIX_DATA GPIO_NUM_4
#define MATRIX_CLOCK GPIO_NUM_17
#define MATRIX_LATCH GPIO_NUM_16

byte smileyPattern[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};
byte zeros[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

void task_Matrix(void *arg) {
	gpio_pad_select_gpio(MATRIX_DATA);
	gpio_pad_select_gpio(MATRIX_CLOCK);
	gpio_pad_select_gpio(MATRIX_LATCH);

	gpio_set_direction(MATRIX_DATA, GPIO_MODE_OUTPUT);
	gpio_set_direction(MATRIX_CLOCK, GPIO_MODE_OUTPUT);
	gpio_set_direction(MATRIX_LATCH, GPIO_MODE_OUTPUT);

	displayImage(zeros);

	while (1) {
		// Display the smiley face pattern
		displayImage(smileyPattern);
	}
}

// build this that uses the improved myshiftout
void displayImage(byte image[8]) {
	for (int i = 0; i < 8; i++) {
		gpio_set_level(MATRIX_LATCH, 0);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, 255 - image[i]);
		MYshiftOut(MATRIX_DATA, MATRIX_CLOCK, pow(2, i));
		gpio_set_level(MATRIX_LATCH, 1);
		vTaskDelay(2 / portTICK_PERIOD_MS);
	}
}

// fix this to make it simpler
void MYshiftOut(gpio_num_t dataPin, gpio_num_t clockPin, uint8_t val) {

	gpio_set_level(clockPin, LOW);
	for (int i = 0; i < 8; i++) {

		gpio_set_level(dataPin, (val & 128) != 0);
		val <<= 1;

		ivar_delay_u(10);
		gpio_set_level(clockPin, HIGH);
		ivar_delay_u(10);
		gpio_set_level(clockPin, LOW);
	}
}

void ivar_delay_u(uint64_t number_of_microseconds) {
	uint64_t microseconds = esp_timer_get_time();
	if (0 != number_of_microseconds) {
		while (((uint64_t)esp_timer_get_time() - microseconds) <= number_of_microseconds) {
			// Wait
		}
	}
}

void app_main(void) { xTaskCreate(task_Matrix, "taskMatrix", 4096, NULL, 3, NULL); }