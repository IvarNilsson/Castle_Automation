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

#define RGB_R GPIO_NUM_15 // might be wrong order :)
#define RGB_G GPIO_NUM_14 // might be wrong order :)
#define RGB_B GPIO_NUM_12 // might be wrong order :)

#define LED_R GPIO_NUM_25
#define LED_Y GPIO_NUM_26
#define LED_G GPIO_NUM_27

#define FOTO_RESISTOR 13
#define TEMP_SENSOR 35

#define Serial Serial

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#include <Arduino.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main();

void task1(void *arg) {
	gpio_pad_select_gpio(LED_R);
	gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
	while (1) {
		// printf("Turning off the LED\n");
		gpio_set_level(LED_R, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		// printf("Turning on the LED\n");
		gpio_set_level(LED_R, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task2(void *arg) {
	gpio_pad_select_gpio(LED_Y);
	gpio_set_direction(LED_Y, GPIO_MODE_OUTPUT);
	while (1) {
		gpio_set_level(LED_Y, 0);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
		gpio_set_level(LED_Y, 1);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void task3(void *arg) {
	gpio_pad_select_gpio(LED_G);
	gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
	while (1) {
		gpio_set_level(LED_G, 0);
		vTaskDelay(4000 / portTICK_PERIOD_MS);
		gpio_set_level(LED_G, 1);
		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}

void task4(void *arg) {
	gpio_pad_select_gpio(RGB_R);
	gpio_pad_select_gpio(RGB_G);
	gpio_pad_select_gpio(RGB_B);
	gpio_set_direction(RGB_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(RGB_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(RGB_R, GPIO_MODE_OUTPUT);

	while (1) {
		gpio_set_level(RGB_R, 0);
		gpio_set_level(RGB_G, 0);
		gpio_set_level(RGB_B, 0);

		vTaskDelay(4000 / portTICK_PERIOD_MS);

		gpio_set_level(RGB_R, 1);
		gpio_set_level(RGB_G, 1);
		gpio_set_level(RGB_B, 1);

		vTaskDelay(4000 / portTICK_PERIOD_MS);
	}
}

void app_main(void) {
	// xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
	// xTaskCreate(task2, "task2", 4096, NULL, 9, &myTask2Handle);
	xTaskCreate(task1, "task1", 4096, NULL, 10, NULL);
	xTaskCreate(task2, "task2", 4096, NULL, 9, NULL);
	xTaskCreate(task3, "task3", 4096, NULL, 8, NULL);
	xTaskCreate(task4, "task4", 4096, NULL, 7, NULL);
}