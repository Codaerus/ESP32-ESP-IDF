#include <stdio.h>
#include "driver/gpio.h"
#include "driver/uart.h"
#include "string.h"

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);

    uart_config_t uart_config = {
        .baud_rate = 9600
    };
    uart_driver_install(UART_NUM_0,256,256,0,NULL,0);
    uart_param_config(UART_NUM_0, &uart_config);

    uint8_t data;

    while(1){
        if(uart_read_bytes(GPIO_NUM_0,&data,1,100/portTICK_PERIOD_MS))
            {
                if(data == 'a'){
                    gpio_set_level(GPIO_NUM_2,1);
                    const char *msg = "Recibi a\n";
                    uart_write_bytes(UART_NUM_0,msg,strlen(msg));
                }
                 if(data == 'b'){
                    gpio_set_level(GPIO_NUM_2,0);
                    const char *msg = "Recibi b\n";
                    uart_write_bytes(UART_NUM_0,msg,strlen(msg));
                }
            }
    }
}
