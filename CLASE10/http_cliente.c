#include <esp_wifi.h> // Proporciona funciones para configurar WiFi
#include <nvs_flash.h> // Proporciona funciones de gestión en la memoria
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"
#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
// MODO STA: IP Estática
#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"


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
/*
    SISTEMA DE LOGS:
        ESP_LOGI: Info
        ESP_LOGE: Error
        ESP_LOGW: Warnings

*/
void http_request_task(void *p){
    esp_http_client_config_t config = {
        .url = "http://192.168.1.3/dashboard/index.html",
        .method = HTTP_METHOD_GET,
        .timeout_ms = 3000,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    while(1){
        esp_err_t err =  esp_http_client_perform(client);
        if(err == ESP_OK){
            ESP_LOGI("HTTP_CLIENT","HTTP GET status = %d", esp_http_client_get_status_code(client));
        }
        else{
            ESP_LOGE("HTTP_CLIENT","HTTP GET request fallo: %s", esp_err_to_name(err));
        }
        esp_http_client_cleanup(client);
        }
}

void app_main() {
    // Inicializa la memoria NVS (No-Volatile Storage)
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK) {
        return;  // Si no se puede inicializar, retorna
    }

    wifi_init_sta();  // Inicializa y conecta el WiFi en modo STA con IP estática
    xTaskCreate(http_request_task,"http_request_task",4096,NULL,5,NULL);
}
