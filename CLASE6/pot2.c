#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_adc/adc_oneshot.h>

void app_main() {
    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t init = {
        .unit_id = ADC_UNIT_1
    };
    adc_oneshot_new_unit(&init,&adc);
    adc_oneshot_chan_cfg_t cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12  //0-4095
    };
    adc_oneshot_config_channel(adc,ADC_CHANNEL_6,&cfg); //GPIO34 
    adc_oneshot_config_channel(adc,ADC_CHANNEL_4,&cfg); //GPIO32
    uint16_t pot1, pot2;
    while(1){
        adc_oneshot_read(adc,ADC_CHANNEL_6,&pot1); //GPIO34 
        adc_oneshot_read(adc,ADC_CHANNEL_4,&pot2); //GPIO32
        printf("%u,%u\n",pot1,pot2);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
