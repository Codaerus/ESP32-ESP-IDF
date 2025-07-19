#include <esp_wifi.h> //Proporciona funciones para configurar WiFi
#include <nvs_flash.h> //Proporciona funciones de gestion en la memoria
#include <esp_system.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"
//MODO STA : DHCP

#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"
esp_mqtt_client_handle_t client;

void wifi_init_sta(void){
    esp_netif_init(); //Inicializa la interfaz de red del ESP32
    esp_event_loop_create_default(); //Crea el bucle de eventos para manejar conexión wifi, desconexión, etc
    esp_netif_create_default_wifi_sta(); //Configura la interfaz como "station mode"
    
    wifi_init_config_t  cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg); //Inicializa el módulo WiFi con una configuración propocionada

    wifi_config_t wifi_config = {
        .sta = {
                    .ssid = WIFI_SSID,
                    .password = WIFI_PASS,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA); //Configura el modo WiFi como estación (STA)
    esp_wifi_set_config(WIFI_IF_STA,&wifi_config); //Asocia la configuración de red con la interfaz WiFi
    esp_wifi_start(); //Inicia el módulo WiFi

    esp_wifi_connect(); //Intenta conectarse a la red configurada
}

void mqtt_publish_task(void *param){
  esp_mqtt_client_handle_t client = (esp_mqtt_client_handle_t)param;
  while(1){
    int pot1 = 120;
    int pot2 = 160;
    char msg[20];
    sprintf(msg,"%d,%d\n",pot1,pot2);
    esp_mqtt_client_publish(client,"canalx",msg,0,0,1);
    vTaskDelay(5000/portTICK_PERIOD_MS);
  }
}

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event){
  switch(event->event_id){
    case MQTT_EVENT_CONNECTED:
      esp_mqtt_client_subscribe(client,"canaly",0);
      break;
    case MQTT_EVENT_DATA:
      printf("Recibimos algo\n");
      break;
    default:
      break;
  }
  return ESP_OK;
}
void mqtt_event_handler(void* arg,esp_event_base_t event_base,int32_t event_id,void* event_data){
  esp_mqtt_event_handle_t event = event_base;
  mqtt_event_handler_cb(event);
}
void mqtt_app_start(){
  esp_mqtt_client_config_t mqtt_cfg = { 
          .broker.address.uri = "mqtt://192.168.1.15", 
          //.broker.address.port = 1883,
      };
  client = esp_mqtt_client_init(&mqtt_cfg);
  
  esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler,NULL);

  esp_mqtt_client_start(client);
  xTaskCreate(mqtt_publish_task, "mqtt_publish_task", 2048,(void*)client,1,NULL);
}

void app_main() {
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK)
        {
            return;
        }
    wifi_init_sta(); //Llama a al función para configurar e iniciar la conexión WiFi
    mqtt_app_start();
}
