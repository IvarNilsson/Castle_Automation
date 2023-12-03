#include <Arduino.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ivar_lib.h"

extern "C" void app_main();

#define MATRIX_DATA GPIO_NUM_4
#define MATRIX_CLOCK GPIO_NUM_17
#define MATRIX_LATCH GPIO_NUM_16

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

#define RGB_R 15 // might be wrong order :)
#define RGB_G 14 // might be wrong order :)
#define RGB_B 12 // might be wrong order :)

#define LED_R GPIO_NUM_25
#define LED_Y GPIO_NUM_26
#define LED_G GPIO_NUM_27

#define FOTO_RESISTOR 13
#define TEMP_SENSOR 35

ivar_lib ivar;

void task_LED_R(void *arg) {
	gpio_pad_select_gpio(LED_R);
	gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
	while (1) {
		printf("Turning off the LED\n");
		gpio_set_level(LED_R, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		printf("Turning on the LED\n");
		gpio_set_level(LED_R, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task_LED_Y(void *arg) {
	gpio_pad_select_gpio(LED_Y);
	gpio_set_direction(LED_Y, GPIO_MODE_OUTPUT);
	while (1) {
		printf("Turning off the LED\n");
		gpio_set_level(LED_Y, 0);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		printf("Turning on the LED\n");
		gpio_set_level(LED_Y, 1);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void task_LED_G(void *arg) {
	gpio_pad_select_gpio(LED_G);
	gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
	while (1) {
		printf("Turning off the LED\n");
		gpio_set_level(LED_G, 0);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		printf("Turning on the LED\n");
		gpio_set_level(LED_G, 1);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void task_Matrix(void *arg) {
	const byte smileyPattern[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};

	gpio_pad_select_gpio(MATRIX_DATA);
	gpio_pad_select_gpio(MATRIX_CLOCK);
	gpio_pad_select_gpio(MATRIX_LATCH);

	gpio_set_direction(MATRIX_DATA, GPIO_MODE_OUTPUT);
	gpio_set_direction(MATRIX_CLOCK, GPIO_MODE_OUTPUT);
	gpio_set_direction(MATRIX_LATCH, GPIO_MODE_OUTPUT);

	// Initialize shift registers and set them to zero
	gpio_set_level(MATRIX_LATCH, 0);
	// fix this to use my improved algorithm
	// shiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, 0);
	// shiftOut(MATRIX_DATA, MATRIX_CLOCK, MSBFIRST, 0);
	gpio_set_level(MATRIX_LATCH, 1);

	while (1) {
		// Display the smiley face pattern
		for (int i = 0; i < 8; i++) {
			gpio_set_level(MATRIX_LATCH, 0);
			ivar.ivar_shiftOut(MATRIX_DATA, MATRIX_CLOCK, 255 - smileyPattern[i]);
			ivar.ivar_shiftOut(MATRIX_DATA, MATRIX_CLOCK, pow(2, i));
			gpio_set_level(MATRIX_LATCH, 1);

			// test this delay I think 60hz should be fine
			vTaskDelay(1 / portTICK_PERIOD_MS);
		}
	}
}

void app_main(void) {
	// xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
	// xTaskCreate(task2, "task2", 4096, NULL, 9, &myTask2Handle);
	xTaskCreate(task_LED_R, "task_LED_R", 4096, NULL, 10, NULL);
	// xTaskCreate(task_LED_Y, "task_LED_Y", 4096, NULL, 9, NULL);
	// xTaskCreate(task_LED_G, "task_LED_G", 4096, NULL, 1, NULL);
	xTaskCreate(task_Matrix, "taskMatrix", 4096, NULL, 3, NULL);
}