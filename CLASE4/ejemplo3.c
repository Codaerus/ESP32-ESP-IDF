#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void app_main() {
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT);
    gpio_pullup_en(GPIO_NUM_2);

    while(1){
      int button_state = gpio_get_level(GPIO_NUM_2);
      if (button_state == 0){
        printf("Pulsador presionado\n");
      }
      vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
