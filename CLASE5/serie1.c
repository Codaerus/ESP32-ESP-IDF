#include <stdio.h>
#include <driver/gpio.h>

uint8_t data;

void app_main() {
  gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);
  while(1){
      if(scanf("%c",&data)>0){
        if(data == 'a'){
            gpio_set_level(GPIO_NUM_2,1);
            printf("Recibi a\n");
          }
        if(data == 'b'){
            gpio_set_level(GPIO_NUM_2,0);
            printf("Recibi b\n");
          }
      }

    
    }
}
