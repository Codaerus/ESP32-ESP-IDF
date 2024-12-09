#include <esp_wifi.h> // Proporciona funciones para configurar WiFi
#include <nvs_flash.h> // Proporciona funciones de gestión en la memoria
#include <esp_system.h>
#include <esp_netif.h> // Necesario para configurar la IP estática
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// MODO STA: IP Estática
#define WIFI_SSID "MOVISTAR_78A8"
#define WIFI_PASS "NS2ajtQJ7TtDt9m"

// Configuración de IP estática
#define STATIC_IP "192.168.1.108"
#define GATEWAY_IP "192.168.1.1"
#define NETMASK_IP "255.255.255.0"

void wifi_init_sta(void) {
    esp_netif_init(); // Inicializa la interfaz de red del ESP32
    esp_event_loop_create_default(); // Crea el bucle de eventos para manejar conexión WiFi, desconexión, etc.

    esp_netif_t *ret  = esp_netif_create_default_wifi_sta(); // Configura la interfaz como "station mode"
    esp_netif_dhcpc_stop(ret);// DHCP Stop
    //Configuración de la IP estática

    esp_netif_ip_info_t ip_info;
    ip4addr_aton(STATIC_IP,&ip_info.ip);
    ip4addr_aton(NETMASK_IP,&ip_info.netmask);
    ip4addr_aton(GATEWAY_IP,&ip_info.gw);
    //Asignamos la configuración de la red estática
    esp_netif_set_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"),&ip_info);
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

void app_main() {
    // Inicializa la memoria NVS (No-Volatile Storage)
    esp_err_t ret = nvs_flash_init();
    if (ret != ESP_OK) {
        return;  // Si no se puede inicializar, retorna
    }

    wifi_init_sta();  // Inicializa y conecta el WiFi en modo STA con IP estática
}
