#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "mqtt_client.h"
#include <driver/ledc.h> //PWM
#include <driver/adc.h> //ADC

#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"
esp_mqtt_client_handle_t client;

char msg[20];
void wifi_init_sta(void){
    esp_netif_init(); //Inicializa la interfaz de red de la ESP32
    esp_event_loop_create_default();//Crea el bucle de evento

    esp_netif_create_default_wifi_sta(); //Configura la interfaz como "station mode"

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg); //Inicializa el módulo wifi con una configuracion predeterminada

    wifi_config_t wifi_config = {
        .sta = {
                .ssid = WIFI_SSID,
                .password = WIFI_PASS,
        }
    };

    esp_wifi_set_mode(WIFI_MODE_STA);//configura en modo STA
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();//Inicia el módulo wifi
    esp_wifi_connect();
}

void mqtt_publish_task(void *param){
   
    esp_mqtt_client_start(client);
    while(1){  
        int pot1 = adc1_get_raw(ADC1_CHANNEL_6);
        int pot2 = adc1_get_raw(ADC1_CHANNEL_4);
        snprintf(msg,20,"%d,%d",pot1,pot2);
        esp_mqtt_client_publish(client,"canalx",msg,0,1,0);
        vTaskDelay(500/portTICK_PERIOD_MS);


    }
}

void mqtt_event_handler(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data){
    esp_mqtt_event_handle_t event =  event_data;
    switch(event->event_id)
        {
            case MQTT_EVENT_CONNECTED:
                esp_mqtt_client_subscribe(client,"canaly",1);
                break;
            case MQTT_EVENT_DATA:{
                //printf("Recibimos algo\n");
                printf("DATO: %.*s\r\n",event->data_len, event->data);
                char data[10];
                snprintf(data,event->data_len,"%.*s",event->data_len,event->data);
                int duty = atoi(data);
                if(duty>0 && duty<=255){
                    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,duty);
                    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);                    
                }
                else{
                    printf("El valor PWM esta fuera del rango: %s",data);
                }
                break;
            }
            default:
                break;
        }
}

void mqtt_app_start(){
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://192.168.1.2",
    };
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, MQTT_EVENT_ANY,mqtt_event_handler,NULL);


    xTaskCreate(mqtt_publish_task,"mqtt_publish_task",2048,NULL,1,NULL);
}

void configure_pwm(){
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 500,
        .duty_resolution = LEDC_TIMER_8_BIT
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = 2, //GPIO2
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0, //CANAL0 del PWM
        .duty = 0,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&channel_conf);
}

void configure_adc(){
    adc1_config_width(ADC_WIDTH_BIT_12);//Configura el ancho del ADC a 12 bits
    adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);    
}

void app_main(void)
{
    esp_err_t ret  = nvs_flash_init();
    if (ret != ESP_OK){
        return;
    }
    wifi_init_sta();
    mqtt_app_start();
    configure_pwm();
    configure_adc();
}
