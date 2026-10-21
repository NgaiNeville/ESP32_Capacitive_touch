/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
//#define BLINK_GPIO CONFIG_BLINK_GPIO
#define LED_PIN1 GPIO_NUM_2
#define LED_PIN2 GPIO_NUM_42
#define BUTTON_GPIO GPIO_NUM_21

static uint8_t s_led_state = 0;


static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    //gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    //ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    //gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    //gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}



void app_main(void)
{

    ESP_LOGI(TAG, "Example configured to toggle GPIO LED!");
    gpio_config_t button_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&button_conf);

    gpio_config_t led_conf = {
        .pin_bit_mask = (1ULL <<LED_PIN1) | (1ULL << LED_PIN2),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_conf);

    gpio_set_level(LED_PIN1,0);
    gpio_set_level(LED_PIN2,1);

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        //blink_led();
        /* Toggle the LED state */
        int button_level = gpio_get_level(BUTTON_GPIO);

        if (button_level ==0) {
            gpio_set_level(LED_PIN1,1);
            gpio_set_level(LED_PIN2,0);

        }
        else {
            gpio_set_level(LED_PIN1,0);
            gpio_set_level(LED_PIN2,1);
        }


        //gpio_set_level(LED_PINS, 1);
        //s_led_state = !s_led_state;
        vTaskDelay(pdMS_TO_TICKS(50));//(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
        
    }

    /* Configure the peripheral according to the LED type */
    //configure_led();

    //while (1) {
      //  ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
        //blink_led();
        /* Toggle the LED state */
       // s_led_state = !s_led_state;
       //vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
   // }
}
