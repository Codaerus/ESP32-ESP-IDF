#include <esp_wifi.h> //Proporciona funciones para configurar WiFi
#include <nvs_flash.h> //Proporciona funciones de gestion en la memoria
#include <esp_system.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//MODO STA : DHCP

#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"

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

void app_main() {
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK)
        {
            return;
        }
    wifi_init_sta(); //Llama a al función para configurar e iniciar la conexión WiFi
    
}
