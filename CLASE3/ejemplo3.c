#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
  /*
    gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL<<GPIO_NUM_2),
      .mode = GPIO_MODE_OUTPUT
    };
  */
    gpio_config(&(gpio_config_t){
      .pin_bit_mask = (1ULL<<GPIO_NUM_2),
      .mode = GPIO_MODE_OUTPUT
    });

    while(1){
      gpio_set_level(GPIO_NUM_2, 1);
      vTaskDelay(500/portTICK_PERIOD_MS);
      gpio_set_level(GPIO_NUM_2, 0);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

//(struct_type){.m1=v1,m2=v2,...}
