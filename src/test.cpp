#include <Arduino.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main();

#define BLINK_GPIO1 GPIO_NUM_12
#define BLINK_GPIO2 GPIO_NUM_2

void task1(void *arg) {
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
    while (1) {
        printf("Turning off the LED\n");
        gpio_set_level(BLINK_GPIO1, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("Turning on the LED\n");
        gpio_set_level(BLINK_GPIO1, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

 void task2(void *arg) {
     gpio_pad_select_gpio(BLINK_GPIO2);
     gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT);
     while (1) {
         printf("Turning off the LED\n");
         gpio_set_level(BLINK_GPIO2, 0);
         vTaskDelay(2000 / portTICK_PERIOD_MS);
         printf("Turning on the LED\n");
         gpio_set_level(BLINK_GPIO2, 1);
         vTaskDelay(2000 / portTICK_PERIOD_MS);
     }
 }

void app_main(void) {
    // xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
    // xTaskCreate(task2, "task2", 4096, NULL, 9, &myTask2Handle);
    xTaskCreate(task1, "task1", 4096, NULL, 10, NULL);
    xTaskCreate(task2, "task2", 4096, NULL, 9, NULL);
}