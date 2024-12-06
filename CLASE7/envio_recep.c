#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/adc.h"
#include "string.h"

void app_main(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);//Configura el ancho del ADC a 12 bits
    adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);

    uart_config_t uart_config = {
            .baud_rate = 9600,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE

    };
    uart_driver_install(UART_NUM_0,1024,1024,0,NULL,0);
    uart_param_config(UART_NUM_0, &uart_config);

    char msg[30];
    uint8_t data;
    while(1){
            if(uart_read_bytes(GPIO_NUM_0,&data,1,100/portTICK_PERIOD_MS))
                {
                    if(data == 'a'){
                        gpio_set_level(GPIO_NUM_2,1);
                    }
                    if(data == 'b'){
                        gpio_set_level(GPIO_NUM_2,0);
                    }
                }
            //int pot1 = 100;
            int pot1 = adc1_get_raw(ADC1_CHANNEL_6);
            int pot2 = adc1_get_raw(ADC1_CHANNEL_4);
            snprintf(msg,30,"%d,%d\n",pot1,pot2);
            uart_write_bytes(UART_NUM_0,msg,strlen(msg));
            vTaskDelay(1000/portTICK_PERIOD_MS);
            }
}
