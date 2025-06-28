#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/uart.h"
#include "string.h"

void app_main(void)
{   //ACONFIGURACIÓN ADC
    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t init = { .unit_id = ADC_UNIT_1 }; //inicia ADC1
    adc_oneshot_new_unit(&init, &adc);

    adc_oneshot_chan_cfg_t cfg = { .bitwidth = ADC_BITWIDTH_12, .atten = ADC_ATTEN_DB_11 };
    adc_oneshot_config_channel(adc, ADC_CHANNEL_6, &cfg);
    adc_oneshot_config_channel(adc, ADC_CHANNEL_7, &cfg);
    int val1=0,val2=0;
    //CONFIGURACIÓN UART
    uart_config_t uart_config = {
      .baud_rate = 9600,
      .data_bits = UART_DATA_8_BITS,
    };
    uart_driver_install(UART_NUM_0,1024,1024,0,NULL,0);
    uart_param_config(UART_NUM_0,&uart_config);
    char msg[30];
    while (1) {
        adc_oneshot_read(adc, ADC_CHANNEL_6, &val1); // GPIO34
        adc_oneshot_read(adc, ADC_CHANNEL_7, &val2); // GPIO35
        snprintf(msg,30,"%d,%d",val1,val2);
        uart_write_bytes(UART_NUM_0,msg,strlen(msg));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
