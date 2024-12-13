#include <esp_wifi.h> // Proporciona funciones para configurar WiFi
#include <nvs_flash.h> // Proporciona funciones de gestión en la memoria
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"

// MODO STA: IP Estática
#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"
char msg[20];
esp_mqtt_client_handle_t client;

void wifi_init_sta(void) {
    esp_netif_init(); // Inicializa la interfaz de red del ESP32
    esp_event_loop_create_default(); // Crea el bucle de eventos para manejar conexión WiFi, desconexión, etc.

    esp_netif_create_default_wifi_sta(); // Configura la interfaz como "station mode"

    // Configuración del WiFi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg); // Inicializa el módulo WiFi


    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    
    esp_wifi_set_mode(WIFI_MODE_STA); // Establece el modo STA
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config); // Credenciales de conexión
    esp_wifi_start(); // Inicia el módulo WiFi
    esp_wifi_connect(); // Intenta conectarse a la red configurada
}

void mqtt_publish_task(void *param){
    esp_mqtt_client_handle_t client = (esp_mqtt_client_handle_t)param;
    while(1){
        int pot1 = 100;
        int pot2 = 200;
        snprintf(msg,20,"%d,%d",pot1,pot2);
        esp_mqtt_client_publish(client,"canalx",msg,0,1,0);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event){
    switch(event->event_id)
        {
            case MQTT_EVENT_CONNECTED:
                esp_mqtt_client_subscribe(client,"canaly",0);
                break;
            case MQTT_EVENT_DATA:
                //printf("Recibimos algo\n");
                printf("DATO: %.*s\r\n",event->data_len,event->data);
                break;
            default:
                break;
        }

    return ESP_OK;
}

void mqtt_event_handler(void *arg,esp_event_base_t event_base,int32_t event_id,void* event_data){
    esp_mqtt_event_handle_t event = event_data;
    //esp_mqtt_client_handle_t client = (esp_mqtt_client_handle_t)arg;
    mqtt_event_handler_cb(event);
}

void mqtt_app_start(void){
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://192.168.1.6", 
    };

    client =  esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client,MQTT_EVENT_ANY,mqtt_event_handler,NULL);//(void* )client
    /*
        Se utiliza para registrar un manejador de eventos para el cliente MQTT, eso permite llamar una función cada vez que ocurre un
        evento MQTT, como la conexión al broker, recepción de mensajes, la publicación, etc
            .esp_mqtt_client_handle_t client: Representa el cliente mqtt
            .esp_mqtt_event_id_t event: Es el identificador del evento
            .esp_event_handler_t event_handler: Es la función que se invoca cuando ocurra el evento.
                Esta representada por un puntero a función
                    (*esp_event_handler_t)(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data);
                        Parametros:
                            void* event_handler_arg: Es un puntero opcional que se usa para pasar argumentos
                            esp_event_base_t event_base:
                            int32_t event_id: Identificador de evento
                            void* event_dat: Contiene información del evento
    */
    esp_mqtt_client_start(client);
    xTaskCreate(mqtt_publish_task, "mqtt_publish_task", 2048,(void* )client,5,NULL);
}

void app_main() {
    // Inicializa la memoria NVS (No-Volatile Storage)
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK) {
        return;  // Si no se puede inicializar, retorna
    }

    wifi_init_sta();  // Inicializa y conecta el WiFi en modo STA con IP estática
    mqtt_app_start();
}
